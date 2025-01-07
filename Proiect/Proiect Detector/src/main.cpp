#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Constante pentru LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int mq7Pin = A0;
const int buzzerPin = 7;
const int ledPin = 6;

const int coThreshold = 100; // prag CO, atat am vazut din mai multe teste ca este un nivel okay

volatile bool toggleBuzzerLed = false; // control ON/OFF pentru buzzer și LED care lucreaza concomitent
volatile bool state = false;           // stare LED și buzzer
volatile int alertLevel = 0;           // nivel avertizare: 0 = Safe, 1 = Warning, 2 = Danger High

void setup() {
  lcd.begin(16, 2); // initializare LCD
  lcd.print("CO Monitor Init"); // mesaj de inițializare
  delay(2000); // care ramane afisat 2 secunde
  lcd.clear(); 

  pinMode(mq7Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); //initializare serial pentru a vedea si in terminal 
  Serial.println("CO Monitor Initialized.");

  // Configurare TIMER1
  cli(); // dezactivare intreruperi
  TCCR1A = 0; 
  TCCR1B = 0; 

  OCR1A = 1562; 
  TCCR1B |= (1 << WGM12); // Mod CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A); // activare intreruperi la comparatie
  sei(); // activare intreruperi
}

void loop() {
  //se citeste nivelul de CO
  int coLevel = analogRead(mq7Pin);

  // afisare pe LCD
  lcd.setCursor(0, 0); // primul rând
  lcd.print("CO Level: "); //cu mesajul permanent care arata nivelul de CO
  lcd.print(coLevel);
  lcd.print("   "); 

  // afisare si in terminal
  Serial.print("CO Level: ");
  Serial.println(coLevel);

  // incadrarea nivelurilor de avertizare
  if (coLevel > coThreshold * 2) { 
    lcd.setCursor(0, 1);
    lcd.print("   DANGER HIGH   ");  //mesaj pentru cel mai mare nivel de risc
    Serial.println("Alert: DANGER HIGH!");
    alertLevel = 2; 
    toggleBuzzerLed = true;  //toggle pentru activarea buzzer-ului si a led-ului
  } else if (coLevel > coThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("    WARNING!     "); //mesahj pentru nivel mediu
    Serial.println("Alert: WARNING!");
    alertLevel = 1; 
    toggleBuzzerLed = true; 
  } else {
    lcd.setCursor(0, 1);
    lcd.print(" SAFE for now    "); // esti safe
    Serial.println("Status: SAFE for now.");
    alertLevel = 0; 
    toggleBuzzerLed = false; // daca esti safe, se dezactiveaza buzzer-ul si led-ul
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}

// functia de intrerupere pentru timer 1
ISR(TIMER1_COMPA_vect) {
  static int counter = 0; // Contor pentru frecvență redusă

  if (toggleBuzzerLed) {
    if (alertLevel == 2) { 
      // Pericol mare: LED și buzzer la frecvență normală
      state = !state;
      digitalWrite(buzzerPin, state);
      digitalWrite(ledPin, state);
    } else if (alertLevel == 1) {
      // Avertisment moderat: LED și buzzer la frecvență redusă
      counter++;
      if (counter >= 2) { // La fiecare 2 întreruperi
        state = !state;
        digitalWrite(buzzerPin, state);
        digitalWrite(ledPin, state);
        counter = 0; // Resetare contor
      }
    }
  } else {
    // Oprire buzzer și LED
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
}

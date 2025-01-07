#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Constante pentru LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int mq7Pin = A0;
const int buzzerPin = 7;
const int ledPin = 6;

const int coThreshold = 100; // Prag CO

volatile bool toggleBuzzerLed = false; // Control ON/OFF pentru buzzer și LED
volatile bool state = false;           // Stare LED și buzzer
volatile int alertLevel = 0;           // Nivel avertizare: 0 = Safe, 1 = Warning, 2 = Danger High

void setup() {
  lcd.begin(16, 2); // Inițializare LCD
  lcd.print("CO Monitor Init"); // Mesaj de inițializare
  delay(2000); // Mesajul rămâne afișat 2 secunde
  lcd.clear(); // Ștergere ecran

  pinMode(mq7Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Configurare TIMER1
  cli(); // Dezactivare întreruperi
  TCCR1A = 0; 
  TCCR1B = 0; 

  OCR1A = 1562; // Valoare pentru temporizare (aproximativ 1 Hz la prescaler 1024)
  TCCR1B |= (1 << WGM12); // Mod CTC
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A); // Activare întrerupere pe comparație
  sei(); // Activare întreruperi
}

void loop() {
  // Citirea nivelului de CO
  int coLevel = analogRead(mq7Pin);

  // Afișare pe LCD
  lcd.setCursor(0, 0); // Primul rând
  lcd.print("CO Level: "); 
  lcd.print(coLevel);
  lcd.print("   "); // Golire spațiu în plus

  // Niveluri de avertizare
  if (coLevel > coThreshold * 2) { 
    lcd.setCursor(0, 1);
    lcd.print("   DANGER HIGH   "); // Mesaj pericol mare
    alertLevel = 2; // Pericol mare
    toggleBuzzerLed = true; // Activare buzzer și LED
  } else if (coLevel > coThreshold) {
    lcd.setCursor(0, 1);
    lcd.print("    WARNING!     "); // Mesaj avertisment
    alertLevel = 1; // Avertisment moderat
    toggleBuzzerLed = true; // Activare buzzer și LED
  } else {
    lcd.setCursor(0, 1);
    lcd.print("   SAFE LEVEL    "); // Mesaj nivel sigur
    alertLevel = 0; // Nivel sigur
    toggleBuzzerLed = false; // Dezactivare buzzer și LED
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}

// Funcția de întrerupere pentru TIMER1
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

#include <Arduino.h>

// Pin Definitions
const int ROSU = 6;   // LED rosu
const int VERDE = 5;  // LED verde
const int ALBASTRU = 4;  // LED albastru
const int led1 = 10;   // primul led(25%)
const int led2 = 9;    // al doilea led(50%)
const int led3 = 8;    // al treilea led(75%)
const int led4 = 7;    // al patrulea led(100%)
const int start = 3;   // buton start
const int stop = 2;    // buton stop

//variabile ca sa verific cand statia este valabila si cand este in stagiul de incarcare
bool chargingActive = false;  
bool stationAvailable = true; 

bool startBtnFlag = false;    // Start button pressed state
bool stopBtnFlag = false;     // Stop button pressed state

// Debounce timing
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
const unsigned long debounceDelay = 50;

void animatieSTOP() {
 //opresc toate ledurile
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  int i = 0;

  //dupa ce s-a incarcat statia la 100%, ledurile clipesc de 3 ori
  while (i < 3) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(1000);
    i++;
  }

  digitalWrite(ROSU, LOW);
  digitalWrite(VERDE, HIGH);

  chargingActive = false;
  stationAvailable = true;
}

void pornire() {
  if (chargingActive == false && stationAvailable == true) {
    chargingActive = true; 
    digitalWrite(ROSU, HIGH);  
    digitalWrite(VERDE, LOW);  

    digitalWrite(led1, HIGH);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led1, LOW);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led1, HIGH);
    delay(1000);
    if (!chargingActive) return;

    digitalWrite(led2, HIGH);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led2, LOW);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led2, HIGH);
    delay(1000);
    if (!chargingActive) return;

    digitalWrite(led3, HIGH);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led3, LOW);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led3, HIGH);
    delay(1000);
    if (!chargingActive) return;

    digitalWrite(led4, HIGH);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led4, LOW);
    delay(1000);
    if (!chargingActive) return;
    digitalWrite(led4, HIGH);
    delay(1000);
    if (!chargingActive) return;

    animatieSTOP(); // face animatia dupa ce se aprind toate ledurile
  }
}

void oprire(){
    if (chargingActive ==  true) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(1000);
    animatieSTOP();
    }
}


void setup() {
  // LED ca output
  pinMode(ROSU, OUTPUT);
  pinMode(VERDE, OUTPUT);
  pinMode(ALBASTRU, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  //butoanele ca input
  pinMode(start, INPUT);
  pinMode(stop, INPUT);

  // lasam ledul verde aprins deoarece statia este valabila
  digitalWrite(ROSU, LOW);
  digitalWrite(VERDE, HIGH); 
  digitalWrite(ALBASTRU, LOW);   // nu folosim albastru
}

// The loop function runs over and over again forever
void loop() {
  int startState = digitalRead(start); // Read the state of the start button
  int stopState = digitalRead(stop);   // Read the state of the stop button

  // Check for debounced start button press
  if (startState == LOW && !startBtnFlag) {
    unsigned long currentTime = millis();
    if (currentTime - lastDebounceTimeStart > debounceDelay) {
      startBtnFlag = true;
      lastDebounceTimeStart = currentTime;
      if (!chargingActive && stationAvailable) {
        pornire(); // Start charging process
      }
    }
  } else if (startState == HIGH) {
    startBtnFlag = false; // Reset flag when button is released
  }

  if (stopState == LOW ){
    stopState = digitalRead(stop);
    if (stopState == LOW && chargingActive) {
        chargingActive = false;
        oprire();
        return;
      }
    }

     


}

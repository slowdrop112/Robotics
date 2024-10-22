#include <Arduino.h>
 
int led1 = 10;   // LED pentru 25% 
int led2 = 9;    // LED pentru 50% 
int led3 = 8;    // LED pentru 75% 
int led4 = 7;    // LED pentru 100% 
int ledRosu = 6;   // Pin LED rosu RGB 
int ledVerde = 5; // Pin LED verde RGB 
int ledAlbastru = 4;  // Pin LED albastru (nu folosim)
int butonStart = 3; // Pin pentru butonul de start
int butonStop = 2;  // Pin pentru butonul de stop
 
bool isCharging = false;    // Daca incarcarea e activa
bool isFree = true;         // Daca statia e libera
bool startButtonPressed = false; // Starea butonului de start
bool stopButtonPressed = false;  // Starea butonului de stop
 
unsigned long lastDebounceTimeStart = 0;
unsigned long lastDebounceTimeStop = 0;
unsigned long debounceDelay = 10;  // Debouncing time
 
void setup() {
  pinMode(ledRosu, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAlbastru, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
 
  pinMode(butonStart, INPUT);
  pinMode(butonStop, INPUT);
 
  // Pornim statia
  digitalWrite(ledRosu, LOW);
  digitalWrite(ledVerde, HIGH);  // Stația este liberă (verde)
  digitalWrite(ledAlbastru, LOW);    // Nu folosim LED-ul albastru
}
 
void blinkAllLeds() {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  // Clipim toate LEDurile simultan de 3 ori pentru a indica finalizarea
  for (int i = 0; i < 3; i++) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    delay(700);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    delay(700);
  }
 
 
}
 
void stopCharging() {
  // Oprim incarcarea si resetam toate ledurile
 
  // Resetam ledul RGB la starea de liber(verde)
 
  blinkAllLeds();
  digitalWrite(ledRosu, LOW);
  digitalWrite(ledVerde, HIGH);
 
  // Resetam si starile
  isCharging = false;
  isFree = true;
}
 
void delayWithStopCheck(int ms) {
  // Verificăm butonul de stop în timpul delay-ului
  int time = 0;
  while (time < ms) {
    int butonStopState = digitalRead(butonStop);
    if (butonStopState == LOW && (millis() - lastDebounceTimeStop > debounceDelay)) {
      lastDebounceTimeStop = millis();
      stopCharging();
      return; // Ieșim din delay dacă s-a apăsat butonul de stop
    }
    delay(10);  // Așteptăm câte 10ms pentru a verifica din nou
    time += 10;
  }
}
void blinkLED(int led) {
  digitalWrite(led, HIGH);  // LED se aprinde
  delayWithStopCheck(1000); // Verificăm dacă s-a apăsat butonul de stop
  digitalWrite(led, LOW);   // LED se stinge
  delayWithStopCheck(1000);
  digitalWrite(led, HIGH);  // LED se aprinde din nou
  delayWithStopCheck(1000);
}
 
 
 
void startCharging() {
  // incarcarea incepe doar daca este activa
  if (isCharging) {
    blinkLED(led1);  // L1 pentru 25%
 
    if (!isCharging) return; // Dacă oprirea a fost apăsată, ieșim
    blinkLED(led2);  // L2 pentru 50%
 
    if (!isCharging) return;
    blinkLED(led3);  // L3 pentru 75%
 
    if (!isCharging) return;
    blinkLED(led4);  // L4 pentru 100%
 
    // Finalizarea încărcării - LED-urile clipesc simultan de 3 ori
 
    // Stația devine liberă din nou (LED RGB se face verde)
    digitalWrite(ledRosu, LOW);    // Oprim LED-ul roșu
    digitalWrite(ledVerde, HIGH); // Activăm LED-ul verde pentru a indica "liber"
    isCharging = false;
    isFree = true;
    stopCharging();
  }
}
 
void loop() {
  // Citim starea butonului de start cu debouncing
  int butonStartState = digitalRead(butonStart);
  if (butonStartState == LOW && (millis() - lastDebounceTimeStart > debounceDelay)) {
    lastDebounceTimeStart = millis();
    startButtonPressed = true;
  }
 
  // Citim starea butonului de stop cu debouncing
  int butonStopState = digitalRead(butonStop);
  if (butonStopState == LOW && (millis() - lastDebounceTimeStop > debounceDelay)) {
    lastDebounceTimeStop = millis();
    stopButtonPressed = true;
  }
 
  // daca apasam butonul de start si statie e libera
  if (startButtonPressed && isFree) {
    startButtonPressed = false;  
    isCharging = true;           
    isFree = false;              
    digitalWrite(ledRosu, HIGH);  
    digitalWrite(ledVerde, LOW); 
    startCharging();             
  }
 
  // daca apasam butonul de stop si incarcarea este activa
  if (stopButtonPressed && isCharging) {
    stopButtonPressed = false;   // Resetam starea butonului
    stopCharging();              // Oprim incarcarea
  }
}
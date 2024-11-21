#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>

const uint32_t cpuClockHz = 16000000L;
const uint32_t serialBaudRate = 115200;

const int lcdRsPin = 9, lcdEnablePin = 8, lcdD4Pin = 5, lcdD5Pin = 4, lcdD6Pin = 3, lcdD7Pin = 2;
LiquidCrystal lcd(lcdRsPin, lcdEnablePin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);
const int screenRows = 2, screenCols = 16;

const int motorPin = 6;
Servo motor;
int motorPosition = 0;

const unsigned long playerTurnDurationMs = 3000;
const unsigned long maxGameDurationMs = 30000;
unsigned long startTime = 0;

int scoreP1 = 0;
int scoreP2 = 0;

bool showMenu = true;
bool startGame = false;
bool endGame = false;
bool isGameActive = false;
int currentPlayer = 0;

enum EventCode {
  NoEvent = 0,
  Btn1Pressed = 1,
  Btn2Pressed = 2,
  Btn3Pressed = 3,
  Btn4Pressed = 4,
  Btn5Pressed = 5,
  Btn6Pressed = 6,
  RequestInput = 8,
  Player1Red = 9,
  Player1Green = 10,
  Player1Blue = 11,
  Player2Red = 12,
  Player2Green = 13,
  Player2Blue = 14,
  EndGameRequest = 15,
  DummyValue = 255
};

void displayWelcome() {
  showMenu = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press to Start!");
  lcd.setCursor(0, 1);
  motor.write(0);
}

void endGameDisplay() {
  endGame = false;
  isGameActive = false;
  
  int winner = 0;
  int highScore = max(scoreP1, scoreP2);

  if (scoreP1 > scoreP2) winner = 1;
  else if (scoreP2 > scoreP1) winner = 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  if (winner == 0) {
    lcd.print("Game Drawn!");
  } else {
    lcd.print("Player ");
    lcd.print(winner);
    lcd.print(" Wins!");
  }

  lcd.setCursor(0, 1);
  lcd.print("Final Score: ");
  lcd.print(highScore);

  delay(5000);
  showMenu = true;
}

void updateUI() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P1 Score: ");
  lcd.print(scoreP1);

  lcd.setCursor(0, 1);
  lcd.print("P2 Score: ");
  lcd.print(scoreP2);
}

void setupNewGame() {
  startGame = false;
  scoreP1 = 0;
  scoreP2 = 0;
  updateUI();
  currentPlayer = random(1, 3);
  startTime = millis();
  isGameActive = true;
}

void handleSlaveInput() {
  digitalWrite(SS, LOW);
  SPI.transfer(EventCode::RequestInput);
  delay(100);
  byte response = SPI.transfer(EventCode::DummyValue);
  digitalWrite(SS, HIGH);

  if (!isGameActive && response != EventCode::NoEvent) {
    startGame = true;
  }
}

void gameLogic() {
  if (isGameActive) {
    unsigned long timeLeft = (startTime + maxGameDurationMs) - millis();
    motor.write(map(timeLeft, 0, maxGameDurationMs, 0, 180));
    if (millis() - startTime > maxGameDurationMs) {
      endGame = true;
    }
  }
}

void setup() {
  randomSeed(analogRead(0));
  SPI.begin();
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);

  lcd.begin(screenCols, screenRows);
  lcd.clear();

  motor.attach(motorPin);
  showMenu = true;
  Serial.begin(serialBaudRate);
}

void loop() {
  if (showMenu) {
    displayWelcome();
  }

  if (startGame) {
    setupNewGame();
  }

  if (isGameActive) {
    gameLogic();
  }

  handleSlaveInput();

  if (endGame) {
    endGameDisplay();
  }
}

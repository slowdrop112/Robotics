#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

const uint32_t baudRate = 115200;
const int buttonAnalogValues[] = { 506, 342, 261, 258, 203, 196 };
const int errorAnalogValue = 10;

const int rgbLedPinsP1[] = { 7, 6, 5 };
const int rgbLedPinsP2[] = { 4, 3, 2 };

enum Events {
  Empty = 0,
  Button1Pressed = 1,
  Button2Pressed = 2,
  Button3Pressed = 3,
  Button4Pressed = 4,
  Button5Pressed = 5,
  Button6Pressed = 6,
  NoButtonPressed = 7,
  MasterRequestsInputFromSlave = 8,
  CurrentPlayer1Red = 9,
  CurrentPlayer1Green = 10,
  CurrentPlayer1Blue = 11,
  CurrentPlayer2Red = 12,
  CurrentPlayer2Green = 13,
  CurrentPlayer2Blue = 14,
  MasterRequestsStopGame = 15,
  Dummy = 255
};

bool buttonPressed(int analogReadVal, int buttonVal) {
  return abs(analogReadVal - buttonVal) <= errorAnalogValue;
}

void controlRGBLed(const int ledPins[3], int red, int green, int blue) {
  digitalWrite(ledPins[0], red);
  digitalWrite(ledPins[1], green);
  digitalWrite(ledPins[2], blue);
}

ISR(SPI_STC_vect) { 
  byte data = SPDR;

  Serial.print("Received: ");
  Serial.print(data);
  Serial.println("");

  if (data == Events::MasterRequestsInputFromSlave) {
    Serial.println("Master requested input from Slave");
    int buttonAnalogValue = analogRead(A0);
    int i = 0;

    while (i < 6) {
      if (buttonPressed(buttonAnalogValue, buttonAnalogValues[i])) {
        Serial.print("Button ");
        Serial.print(i + 1);
        Serial.println(" pressed");
        SPDR = Events(i + 1);
        break;
      }
      i++;
    }

    if (i == 6) {
      Serial.println("No button pressed");
      SPDR = Events::NoButtonPressed;
    }
  } else if (data == Events::CurrentPlayer1Red) {
    controlRGBLed(rgbLedPinsP1, HIGH, LOW, LOW);
    controlRGBLed(rgbLedPinsP2, LOW, LOW, LOW);
  } else if (data == Events::CurrentPlayer1Green) {
    controlRGBLed(rgbLedPinsP1, LOW, HIGH, LOW);
    controlRGBLed(rgbLedPinsP2, LOW, LOW, LOW);
  } else if (data == Events::CurrentPlayer1Blue) {
    controlRGBLed(rgbLedPinsP1, LOW, LOW, HIGH);
    controlRGBLed(rgbLedPinsP2, LOW, LOW, LOW);
  } else if (data == Events::CurrentPlayer2Red) {
    controlRGBLed(rgbLedPinsP1, LOW, LOW, LOW);
    controlRGBLed(rgbLedPinsP2, HIGH, LOW, LOW);
  } else if (data == Events::CurrentPlayer2Green) {
    controlRGBLed(rgbLedPinsP1, LOW, LOW, LOW);
    controlRGBLed(rgbLedPinsP2, LOW, HIGH, LOW);
  } else if (data == Events::CurrentPlayer2Blue) {
    controlRGBLed(rgbLedPinsP1, LOW, LOW, LOW);
    controlRGBLed(rgbLedPinsP2, LOW, LOW, HIGH);
  } else if (data == Events::MasterRequestsStopGame) {
    controlRGBLed(rgbLedPinsP1, LOW, LOW, LOW);
    controlRGBLed(rgbLedPinsP2, LOW, LOW, LOW);
  }

  Serial.print("Sent: ");
  Serial.print(SPDR);
  Serial.println("");
}

void setup() { 
  pinMode(SS, INPUT_PULLUP);
  pinMode(MISO, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();

  int i = 0;
  while (i < 3) {
    pinMode(rgbLedPinsP1[i], OUTPUT);
    pinMode(rgbLedPinsP2[i], OUTPUT);
    i++;
  }

  controlRGBLed(rgbLedPinsP1, LOW, LOW, LOW);
  controlRGBLed(rgbLedPinsP2, LOW, LOW, LOW);

  Serial.begin(baudRate);
  Serial.println("Slave initialized");
}

void loop() {
}

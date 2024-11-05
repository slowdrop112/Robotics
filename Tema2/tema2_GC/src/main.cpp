#include <Arduino.h>

const int redPin = 6;
const int greenPin = 5;
const int bluePin = 4;

const int buttonStartStop = 3;
const int buttonDifficulty = 2;

// Buttons debouncing
volatile unsigned long buttonDifficultyLastDebounceTimeMillis = 0;
const unsigned long buttonDifficultyDebounceTimeMillis = 50;

volatile unsigned long buttonStartStopLastDebounceTimeMillis = 0;
const unsigned long buttonStartStopDebounceTimeMillis = 50;

const int roundTime = 30000; // 30000 ms = 30 s (Round time)
const int timerO = 0 ;
const int timerEasy = 4; 
const int timerMediu = 3;
const int timerHard = 2;

const int wordsCount = 30;
const String words[wordsCount] = {
  "masina", "copac", "telefon", "calculator", "carte", "floare",
  "banca", "oras", "fereastra", "scaun", "canapea",  "camera",
  "tabla", "pisica", "caine", "pahar", "ceas", "usa",
  "foaie", "soare", "ploaie", "vreme", "lumina", "umbra", 
  "copil", "joc", "culori", "timp", "zambet", "prieteni"
};

enum Difficulty {
  noDif = -1,
  EASY = 0,
  MEDIUM = 1,
  HARD = 2
};

// starile jocului
volatile bool canChangeDifficulty = false;
volatile bool canStartGame = false;
volatile bool canStopGame = false;
volatile bool isGameStarted = false;
volatile bool shouldChangeWord = false;

enum Difficulty Greutate = Difficulty::noDif;
int timePerWord = 0; //punem 0 ca in caz ca dificultatea nu a fost selectata sa fie 0.

long roundTimeStartMilliseconds = 0; //timer pentru cand incepe runda
int correctWordsCounter = 0; // numarul de cuvinte corecte
String currentWord = ""; // cuvantul random actual
String inputText = ""; // ce scriem

void setRgbLed(int redValue, int greenValue, int blueValue) {
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);
}

//animatia de inceput
void blinkAnim (){
    for (int i = 3; i > 0; i--) {
    Serial.println(i);
    setRgbLed(LOW, HIGH, LOW);
    delay(500);
    setRgbLed(LOW, LOW, LOW);
    delay(500);
  }

}

//verificarea butonului de dificultate
void triggerChangeDifficulty() {
  if (millis() - buttonDifficultyLastDebounceTimeMillis > buttonDifficultyDebounceTimeMillis) {
    buttonDifficultyLastDebounceTimeMillis = millis();

    if (isGameStarted) {
      return;
    }

    canChangeDifficulty = true;
  }
}

//verificam butonul de start/stop
void triggerStartStopGame() {
  if (millis() - buttonStartStopLastDebounceTimeMillis > buttonStartStopDebounceTimeMillis) {
    buttonStartStopLastDebounceTimeMillis = millis();

    if (isGameStarted) {
      canStopGame = true;
    }
    else {
      canStartGame = true;
    }
  }
}

// functie pentru ca atunci cand apas butonul de dificultate sa schimbe dificultatea
void ChangeDifficulty() {
  canChangeDifficulty = false;

  // trecem la următoarea dificultate în ciclu
  Greutate = (Difficulty)((Greutate + 1) % 3);

  if (Greutate == EASY) {
    Serial.println("Mod easy");
    timePerWord = timerEasy;
  } 
  else if (Greutate == MEDIUM) {
    Serial.println("Mod medium");
    timePerWord = timerMediu;
  } 
  else if (Greutate == HARD) {
    Serial.println("Mod hard");
    timePerWord = timerHard;
  } 
  else {
    Serial.println("Nu a fost selectata o dificultate :(");
    Greutate = Difficulty::noDif;
    timePerWord = timerO;
  }
}

// functie pentru inceperea jocului
void startGame() {
  canStartGame = false; //canStartGame pe false pentru odata ce apas butonul jocul este inceput

  if (Greutate == Difficulty::noDif) {
    Serial.println("Alege dificultatea am zis! ");
    return; //daca dificultatea ramane pe default, adica noDif, returneaza acest mesaj
  }

  correctWordsCounter = 0;
  inputText = "";

  blinkAnim();

  setRgbLed(LOW, HIGH, LOW);

  noInterrupts(); //apelam functia noInterrupts pentru a dezactiva intreruperile in timpul initializarii timer-ului

  // initializare Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  const unsigned long clock = 16000000; // 16 MHz clock frequency
  const unsigned long prescaler = 1024;
  const unsigned long timeCompareTarget = (clock / prescaler) * timePerWord - 1;

  OCR1A = timeCompareTarget;

  TCCR1B |= (1 << WGM12); // Turn on CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set prescaler to 1024
  TIMSK1 |= (1 << OCIE1A); // Enable timer interrupt for compare mode

  interrupts();

  roundTimeStartMilliseconds = millis();
  isGameStarted = true;
  shouldChangeWord = true;
}

// ISR for timer 1 
ISR(TIMER1_COMPA_vect) {
  shouldChangeWord = true;
}

// functie pentru a schimba cuvantul
void changeWord() {
  shouldChangeWord = false;

  TCNT1 = 0; //cand se schimba cuvantul, timer-ul sa se ia de la 0

  // alegem cuvantul random
  int index = random(0, wordsCount);
  currentWord = words[index];

  inputText = ""; // resetam ce scrie in input

  Serial.print("\n\n");
  Serial.println(currentWord);
}

// functie pentru a reseta jocul in modul initial
void setInactiveState() {
  setRgbLed(HIGH, HIGH, HIGH);
  Greutate = Difficulty::noDif;
  timePerWord = 0;
  canChangeDifficulty = false;
  canStartGame = false;
  canStopGame = false;
  isGameStarted = false;
  correctWordsCounter = 0;
  shouldChangeWord = false;
  currentWord = "";
  inputText = "";

  noInterrupts();

  // Reset Timer 1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 0;

  TCCR1B &= ~(1 << WGM12); // Turn off CTC mode
  TCCR1B &= ~(1 << CS12) & ~(1 << CS10); // Reset prescaler 1024
  TIMSK1 &= ~(1 << OCIE1A); // Disable timer interrupt for compare mode

  interrupts();

  Serial.println("Alege dificultatea");
}

// functie pentru stop joc
void stopGame() {
  Serial.print("\n\nScore: ");
  Serial.println(correctWordsCounter);

  setInactiveState();
}

void setup() {
   Serial.begin(115200);

   randomSeed(analogRead(0)); // seteaza un seed random ca pattern-ul de la random sa nu fie acelasi

  
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

    pinMode(buttonStartStop, INPUT_PULLUP);
    pinMode(buttonDifficulty, INPUT_PULLUP);

   attachInterrupt(digitalPinToInterrupt(buttonDifficulty), triggerChangeDifficulty, LOW);
   attachInterrupt(digitalPinToInterrupt(buttonStartStop), triggerStartStopGame, LOW);

   setInactiveState();
}

// Operational loop
void loop() {
  if (canChangeDifficulty) {
    ChangeDifficulty();
  }

  if (canStartGame) {
    startGame();
  }

  if (canStopGame) {
    stopGame();
  }

  if (isGameStarted) {
    if (shouldChangeWord) {
      changeWord();
    }

    // verifica daca au trecut cele 30 de secunde
    if ((millis() - roundTimeStartMilliseconds >= roundTime) && !canStopGame) {
      canStopGame = true;
    }

    // Handle user input
// Handle user input
if (Serial.available() > 0) {
    String user_input = Serial.readStringUntil('\n'); // Citiți inputul complet până la enter
    user_input.trim(); // Elimină spațiile suplimentare din inputul utilizatorului

    if (user_input == currentWord) { // Verificăm dacă inputul coincide exact cu cuvântul curent
        setRgbLed(LOW, HIGH, LOW); // Cuvânt corect, LED-ul devine verde
        correctWordsCounter++; // Incrementăm scorul
        shouldChangeWord = true; // Setăm să se schimbe cuvântul
    } 
    else {
        setRgbLed(HIGH, LOW, LOW); // Cuvânt incorect, LED-ul devine roșu
      }
   }

  }
}


#include "ChessClock.h"

ChessClock clock(1L * 60 * 1000); // Setta il timer a 1 minuto. In futuro, bisognerà poter decidere il tempo nel loop()

const int BUTTON_PIN = 10; // Identifica il bottone che per ora fa tutto al pin 10

bool buttonPressed() { // Verifica se il bottone è stato premuto
  static bool lastState = HIGH;
  bool currentState = digitalRead(BUTTON_PIN);

  if (lastState == HIGH && currentState == LOW) {
    delay(20);
    lastState = currentState;
    return true;
  }

  lastState = currentState;
  return false;
}

bool gameStarted = false; // La partita non è iniziata ancora!

// FUNZIONE SOLO DI DEBUGGING, DA ELIMINARE IN PROD
unsigned long previousPrintTime = 5000;
int timer(long w, long b, GameState s) {
  int interval = 5000;
  int s2 = 10;
  unsigned long printTime = millis();
  if (printTime - previousPrintTime >= interval) {
    s2 = static_cast<int>(s);
    if (s2 == 0) {
      Serial.println("STOPPED");
    } else if (s2 == 1) {
      Serial.println("RUNNING");
    } else if (s2 == 2) {
      Serial.println("PAUSED");
    } else if (s2 == 3) {
      Serial.println("OVER");
    }
    Serial.println("W");
    Serial.println(String(w)+"\n"); // Print da utilizzare per vedere se realmente scambia lo scorrere del tempo quando il bottone verrà premuto (non ho un bottoneeeee)
    Serial.println("B");
    Serial.println(String(b)+"\n");
    previousPrintTime = printTime;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Setta il pin per il bottone
  Serial.println("ARDUINO CONNECTED!");
}

void loop() {
  clock.update();

  if (buttonPressed()) { // Solo se il bottone è stato premuto allora inizia la partita
    if (clock.getState() == GameState::STOPPED) {
      clock.startWhite(); // Inizia il gioco, parte il bianco
    } else if (clock.getState() == GameState::RUNNING) { // Se preme il bottone e la partita era già iniziata, cambio turno
      clock.switchTurn();
      Serial.println("Turn switched.");
    }
  }

  unsigned long w = clock.getWhiteTime(); // Estrae il tempo del bianco, da mandare al display in futuro
  unsigned long b = clock.getBlackTime(); // Estrae il tempo del nero, da mandare al display in futuro

  timer(w,b,clock.getState());

}
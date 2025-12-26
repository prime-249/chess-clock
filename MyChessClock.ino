#include "ChessClock.h"

ChessClock clock(1L * 60 * 1000); // Setta il timer a 1 minuto. In futuro, bisognerà poter decidere il tempo nel loop()

const int BUTTON_PIN = 2; // Identifica il bottone che per ora fa tutto al pin 2

bool buttonPressed() { // Verifica se il bottone è stato premuto
  static bool lastState = HIGH;
  bool currentState = digitalRead(BUTTON_PIN);

  if (lastState == HIGH && currentState == LOW) {
    lastState = currentState;
    return true;
  }

  lastState = currentState;
  return false;
}


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Setta il pin per il bottone
  bool gameStarted = false; // La partita non è iniziata ancora!
}

void loop() {

  if (buttonPressed()) { // Solo se il bottone è stato premuto allora inizia la partita

    if (!gameStarted) {
      clock.startWhite(); // Inizia il gioco, parte il bianco
      gameStarted = true; //
    } else { // Se preme il bottone e la partita era già iniziata, cambio turno
      clock.switchTurn();
    }
  }

  unsigned long w = clock.getWhiteTime(); // Estrae il tempo del bianco, da mandare al display in futuro
  unsigned long b = clock.getBlackTime(); // Estrae il tempo del nero, da mandare al display in futuro

  Serial.println(String(w)) // Print da utilizzare per vedere se realmente scambia lo scorrere del tempo quando il bottone verrà premuto (non ho un bottoneeeee)
  Serial.println(String(b))
}
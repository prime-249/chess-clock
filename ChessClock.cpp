#include "ChessClock.h"

// Inizializza istanza della classe ChessClock
ChessClock::ChessClock(unsigned long startTimeMs) // Tempo che viene settato nell.ino
  : timeWhite(startTimeMs), // Da parametro
    timeBlack(startTimeMs), // Da parametro
    lastSwitchTime(0), // Inizializza il momento dell'ultimo switch di turno a zero
    whiteTurn(true), // Inizia sempre il bianco
    state(GameState::STOPPED)
{}

GameState ChessClock::getState() const {
  return state;
}

unsigned long ChessClock::currentMillis() const { //Registra il tempo attuale
  return millis();
}

void ChessClock::startWhite() { // Inizia la partita per il bianco
  if (state != GameState::STOPPED) return;
  whiteTurn = true;
  lastSwitchTime = currentMillis();
  state = GameState::RUNNING;
}

void ChessClock::startBlack() { // Inizia la partita per il nero
  if (state != GameState::STOPPED) return;
  whiteTurn = false;
  lastSwitchTime = currentMillis();
  state = GameState::RUNNING;
}

void ChessClock::switchTurn() { // Cambia il turno
  if (state != GameState::RUNNING) return;

  unsigned long now = currentMillis();
  unsigned long elapsed = now - lastSwitchTime;

  if (whiteTurn) {
    timeWhite -= elapsed;
  } else {
    timeBlack -= elapsed;
  }

  whiteTurn = !whiteTurn;
  lastSwitchTime = now;
}

void ChessClock::pause() {
  if (state != GameState::RUNNING) return;

  unsigned long now = currentMillis();
  unsigned long elapsed = now - lastSwitchTime;

  if (whiteTurn) timeWhite -= elapsed;
  else timeBlack -= elapsed;

  state = GameState::PAUSED;
}

void ChessClock::resume() {
  if (state != GameState::PAUSED) return;

  lastSwitchTime = currentMillis();
  state = GameState::RUNNING;
}

unsigned long ChessClock::getWhiteTime() const { // Estrapola il tempo del bianco per il display
  if (state == GameState::RUNNING && whiteTurn) {
    unsigned long remaining = timeWhite - (currentMillis() - lastSwitchTime);
    return remaining > 0 ? remaining : 0;
  }
  return timeWhite;
}

unsigned long ChessClock::getBlackTime() const { // Estrapola il tempo del nero per il display
  if (state == GameState::RUNNING && !whiteTurn) {
    unsigned long remaining = timeBlack - (currentMillis() - lastSwitchTime);
    return remaining > 0 ? remaining : 0;
  }
  return timeBlack;
}

bool ChessClock::isWhiteTurn() const { // Verifica se è il turno del bianco
  return whiteTurn;
}

void ChessClock::update() {
  if (state != GameState::RUNNING) return;

  unsigned long now = currentMillis();
  unsigned long elapsed = now - lastSwitchTime;

  if (whiteTurn) {
    if (elapsed >= timeWhite) {
      timeWhite = 0;
      state = GameState::GAME_OVER;
      Serial.println("GAME OVER!");
    }
  } else {
    if (elapsed >= timeBlack) {
      timeBlack = 0;
      state = GameState::GAME_OVER;
      Serial.println("GAME OVER!");
    }
  }
}
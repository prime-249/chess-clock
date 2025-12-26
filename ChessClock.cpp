#include "ChessClock.h"

// Inizializza istanza della classe ChessClock
ChessClock::ChessClock(unsigned long startTimeMs) // Tempo che viene settato nell.ino
  : timeWhite(startTimeMs), // Da parametro
    timeBlack(startTimeMs), // Da parametro
    lastSwitchTime(0), // Inizializza il momento dell'ultimo switch di turno a zero
    whiteTurn(true), // Inizia sempre il bianco
    running(false) // False fintanto che non viene startata la partita nell'.ino
{}

unsigned long ChessClock::currentMillis() const { //Registra il tempo attuale
  return millis();
}

void ChessClock::startWhite() { // Inizia la partita per il bianco
  whiteTurn = true;
  running = true;
  lastSwitchTime = currentMillis();
}

void ChessClock::startBlack() { // Inizia la partita per il nero
  whiteTurn = false;
  running = true;
  lastSwitchTime = currentMillis();
}

void ChessClock::switchTurn() { // Cambia il turno
  if (!running) return;

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

void ChessClock::pause() { // Stoppa la partita
  if (!running) return;

  unsigned long now = currentMillis();
  unsigned long elapsed = now - lastSwitchTime;

  if (whiteTurn) {
    timeWhite -= elapsed;
  } else {
    timeBlack -= elapsed;
  }

  running = false;
}

unsigned long ChessClock::getWhiteTime() const { // Estrapola il tempo del bianco per il display
  if (running && whiteTurn) {
    return timeWhite - (currentMillis() - lastSwitchTime);
  }
  return timeWhite;
}

unsigned long ChessClock::getBlackTime() const { // Estrapola il tempo del nero per il display
  if (running && !whiteTurn) {
    return timeBlack - (currentMillis() - lastSwitchTime);
  }
  return timeBlack;
}

bool ChessClock::isWhiteTurn() const { // Verifica se è il turno del bianco
  return whiteTurn;
}

bool ChessClock::isRunning() const { // Verifica se è il turno del nero
  return running;
}
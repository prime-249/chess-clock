#ifndef CHESSCLOCK_H
#define CHESSCLOCK_H

#include <Arduino.h>

class ChessClock {
  public:
    ChessClock(unsigned long startTimeMs); // Inizializza con tempo di partenza

    void startWhite(); // Primo turno del bianco
    void startBlack(); // Primo turno del nero
    void switchTurn(); // Alterna il turno

    void pause(); // Mette la partita in pausa (running = false)

    unsigned long getWhiteTime() const; // Estrapola il tempo del bianco per il display
    unsigned long getBlackTime() const; // Estrapola il tempo del nero per il display

    bool isWhiteTurn() const; // Verifica di chi è il turno
    bool isRunning() const; // Verifica se la partita è iniziata/è in pausa

  private:
    unsigned long timeWhite; // Tempo del bianco
    unsigned long timeBlack; // Tempo del nero

    unsigned long lastSwitchTime; // Registra l'ultimo switch per far correttamente scorrere il tempo di uno o l'altro giocatore
    bool whiteTurn; // è il turno del bianco?
    bool running; // la partita è in pausa?

    unsigned long currentMillis() const; // tempo corrente
};

#endif
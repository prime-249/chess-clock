#ifndef CHESSCLOCK_H
#define CHESSCLOCK_H

#include <Arduino.h>

enum class GameState {
  STOPPED,   // prima di iniziare
  RUNNING,   // partita in corso
  PAUSED,    // pausa manuale
  GAME_OVER  // tempo finito
};


class ChessClock {
  public:
    ChessClock(unsigned long startTimeMs); // Inizializza con tempo di partenza

    void startWhite(); // Primo turno del bianco
    void startBlack(); // Primo turno del nero
    void switchTurn(); // Alterna il turno

    void pause(); // Mette la partita in pausa (running = false)
    void resume(); // Riprende la partita dalla pausa

    void update();

    GameState getState() const;

    unsigned long getWhiteTime() const; // Estrapola il tempo del bianco per il display
    unsigned long getBlackTime() const; // Estrapola il tempo del nero per il display

    bool isWhiteTurn() const; // Verifica di chi è il turno

  private:
    unsigned long timeWhite; // Tempo del bianco
    unsigned long timeBlack; // Tempo del nero

    unsigned long lastSwitchTime; // Registra l'ultimo switch per far correttamente scorrere il tempo di uno o l'altro giocatore
    bool whiteTurn; // è il turno del bianco?

    GameState state;
    
    unsigned long currentMillis() const; // tempo corrente
};

#endif
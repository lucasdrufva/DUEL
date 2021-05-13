#pragma once
#include "gameState.h"

class GameState;

class Game
{
public:
    Game();
    inline GameState* getCurrentState() const { return currentState; }
    void render();
    void trigger();
    void command(int command);
    void setState(GameState& newState);

    bool isPlayerOne = true;
    void initPlayer();

    bool playerOneWon = false;
    int score[2] = {0, 0};

private:
    GameState* currentState;
};
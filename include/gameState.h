#pragma once
#include "game.h"

class Game;

class GameState
{
public:
    virtual void enter(Game* game) = 0;
    virtual void render(Game* game) = 0;
    virtual void trigger(Game* game) = 0;
    virtual void command(Game* game, int command) = 0;
    virtual void exit(Game* game) = 0;
    virtual ~GameState(){}
};
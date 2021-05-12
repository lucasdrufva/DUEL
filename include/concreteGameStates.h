#pragma once
#include "gameState.h"
#include "game.h"

class WaitingStart : public GameState
{
public:
    void enter(Game *game) {}
    void render(Game *game);
    void trigger(Game *game);
    void command(Game *game, int command);
    void exit(Game *game) {}
    static GameState &getInstance();

private:
    WaitingStart() {}
    WaitingStart(const WaitingStart &other);
    WaitingStart &operator=(const WaitingStart &other);
};

class Play : public GameState
{
public:
    void enter(Game *game) {}
    void render(Game *game);
    void trigger(Game *game);
    void command(Game *game, int command);
    void exit(Game *game) {}
    static GameState &getInstance();

private:
    Play() {}
    Play(const Play &other);
    Play &operator=(const Play &other);
};

class Countdown : public GameState
{
public:
    void enter(Game *game);
    void render(Game *game);
    void trigger(Game *game) {}
    void command(Game *game, int command);
    void exit(Game *game) {}
    static GameState &getInstance();

private:
    Countdown() {}
    Countdown(const Countdown &other);
    Countdown &operator=(const Countdown &other);

    unsigned long countdownStartTime;
    int timeLeft;

    void calculateTimeLeft(Game *game);
};
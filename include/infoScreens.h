#pragma once
#include "gameState.h"
#include "game.h"

class InfoScreen : public GameState
{
public:
    void enter(Game *game);
    void trigger(Game *game){}

    bool isAffectedPlayer = false;
    unsigned long sceneStartTime;

    explicit InfoScreen(bool isAffectedPlayer);
};

class Won : public InfoScreen
{
public:
    using InfoScreen::InfoScreen;
    void render(Game *game);
    void command(Game *game, int command) {}
    void exit(Game *game) {}
    static GameState &getInstance(bool isAffectedPlayer);

private:
    Won(const Won &other);
    Won &operator=(const Won &other);
};

class FalseStart : public InfoScreen
{
public:
    using InfoScreen::InfoScreen;
    void render(Game *game);
    void command(Game *game, int command) {}
    void exit(Game *game) {}
    static GameState &getInstance(bool isAffectedPlayer);

private:
    FalseStart(const FalseStart &other);
    FalseStart &operator=(const FalseStart &other);
};

class Result : public InfoScreen
{
public:
    using InfoScreen::InfoScreen;
    void render(Game *game);
    void command(Game *game, int command) {}
    void exit(Game *game) {}
    static GameState &getInstance();

private:
    Result(const Result &other);
    Result &operator=(const Result &other);
};
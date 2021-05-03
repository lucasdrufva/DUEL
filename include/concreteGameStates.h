#pragma once
#include "gameState.h"
#include "game.h"

class WaitingStart : public GameState
{
public:
    void enter(Game* game){}
    void render(Game* game);
    void trigger(Game* game);
    void command(Game* game, int command);
    void exit(Game* game){}
    static GameState& getInstance();

private:
    WaitingStart() {}
	WaitingStart(const WaitingStart& other);
	WaitingStart& operator=(const WaitingStart& other);
};

class Play : public GameState
{
public:
    void enter(Game* game){}
    void render(Game* game);
    void trigger(Game* game);
    void command(Game* game, int command);
    void exit(Game* game){}
    static GameState& getInstance();

private:
    Play() {}
	Play(const Play& other);
	Play& operator=(const Play& other);
};

class Countdown : public GameState
{
public:
    void enter(Game* game);
    void render(Game* game);
    void trigger(Game* game){}
    void command(Game* game, int command);
    void exit(Game* game){}
    static GameState& getInstance();

private:
    Countdown() {}
	Countdown(const Countdown& other);
	Countdown& operator=(const Countdown& other);

    unsigned long countdownStartTime;
    int timeLeft;

    void calculateTimeLeft(Game* game);
};

class Result : public GameState
{
public:
    void enter(Game* game);
    void render(Game* game);
    void trigger(Game* game){}
    void command(Game* game, int command){}
    void exit(Game* game){}
    static GameState& getInstance();

private:
    Result() {}
	Result(const Result& other);
	Result& operator=(const Result& other);

    unsigned long sceneStartTime;
};

class FalseStart : public GameState
{
public:
    void enter(Game* game);
    void render(Game* game);
    void trigger(Game* game){}
    void command(Game* game, int command){}
    void exit(Game* game){}
    static GameState& getInstance();
    static GameState& getInstance(bool isFalseStartPlayer);

private:
    FalseStart() {}
    FalseStart(bool isFalseStartPlayer);
	FalseStart(const FalseStart& other);
	FalseStart& operator=(const FalseStart& other);

    unsigned long sceneStartTime;
    bool isFalsePlayer = false;
};
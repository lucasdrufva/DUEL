#include "game.h"
#include "concreteGameStates.h"
#include <ESP8266WiFi.h>

Game::Game()
{
    currentState = &WaitingStart::getInstance();
    initPlayer();
}

void Game::initPlayer()
{
    String mac = WiFi.macAddress();
    Serial.print("mac: ");
    Serial.println(mac);
    if (mac == "40:F5:20:10:5F:D6")
    {
        //player two
        isPlayerOne = false;
        Serial.println("player two");
    }
    else
    {
        //player one
        isPlayerOne = true;
        Serial.println("player one");
    }
}

void Game::setState(GameState &newState)
{
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void Game::render()
{
    currentState->render(this);
}

void Game::trigger()
{
    currentState->trigger(this);
}

void Game::command(int command)
{
    currentState->command(this, command);
}
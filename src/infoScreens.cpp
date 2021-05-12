#include "concreteGameStates.h"
#include "infoScreens.h"
#include <Arduino.h>
#include "SSD1306Wire.h"


extern SSD1306Wire display;
extern const int buzzerPin;

InfoScreen::InfoScreen(bool isAffected)
{
    isAffectedPlayer = isAffected;
}

void InfoScreen::enter(Game *game)
{
    sceneStartTime = millis();
    tone(buzzerPin, 300, 100);
}

void Won::render(Game *game)
{
    display.setFont(ArialMT_Plain_24);
    if (isAffectedPlayer)
    {
        display.drawString(0, 0, "You won");
    }
    else
    {
        display.drawString(0, 0, "You died");
    }

    if (millis() - sceneStartTime > 5000)
    {
        game->setState(Result::getInstance());
    }
}

GameState &Won::getInstance(bool isAffectedPlayer)
{
    static Won singleton(isAffectedPlayer);
    return singleton;
}

void FalseStart::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_16);
    if (isAffectedPlayer)
    {
        display.drawString(0, 0, "You False Start");
    }
    else
    {
        display.drawString(0, 0, "Other player drew to early");
    }

    // Display it on the screen
    display.display();

    if (millis() - sceneStartTime > 5000)
    {
        game->setState(Result::getInstance());
    }
}

GameState &FalseStart::getInstance(bool isAffectedPlayer)
{
    static FalseStart singleton(isAffectedPlayer);
    return singleton;
}

void Result::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Result ");
    if(game->isPlayerOne){
        display.drawString(0, 30, String(game->score[0]));
        display.drawString(30, 30, String(game->score[1]));
    }else {
        display.drawString(0, 30, String(game->score[1]));
        display.drawString(30, 30, String(game->score[0]));
    }

    // Display it on the screen
    display.display();

    if (millis() - sceneStartTime > 5000)
    {
        game->setState(WaitingStart::getInstance());
    }
}

GameState &Result::getInstance()
{
    static Result singleton(false);
    return singleton;
}
#include "concreteGameStates.h"
#include <Arduino.h>
#include "SSD1306Wire.h"
#include "radio.h"
#include "ir.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

extern Adafruit_MPU6050 mpu;
extern SSD1306Wire display;
extern Radio radio;
extern IR ir;
extern const int buzzerPin;

void WaitingStart::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "Start?");

    // Display it on the screen
    display.display();
}

void WaitingStart::trigger(Game *game)
{
    radio.sendStartCommand();
    Serial.println("Starting countdown");
    game->setState(Countdown::getInstance());
}

void WaitingStart::command(Game *game, int command)
{
    if (command == 20)
    {
        Serial.println("Starting countdown");
        game->setState(Countdown::getInstance());
    }
}

GameState &WaitingStart::getInstance()
{
    static WaitingStart singleton;
    return singleton;
}

void Play::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "PLAY");

    // Display it on the screen
    display.display();
}

void Play::trigger(Game *game)
{
    ir.shoot();
    Serial.println("Game over");
    game->setState(WaitingStart::getInstance());
}

void Play::command(Game *game, int command)
{
    if (command == 53)
    {
        Serial.println("palyer won");
        game->playerOneWon = true;
        game->setState(Countdown::getInstance());
    }
    else if (command == 52)
    {
        Serial.println("palyer won");
        game->playerOneWon = false;
        game->setState(Countdown::getInstance());
    }
    else if (command == 10)
    {
        Serial.println("False Start during play!");
        game->setState(FalseStart::getInstance(false));
    }
}

GameState &Play::getInstance()
{
    static Play singleton;
    return singleton;
}

void Countdown::enter(Game *game)
{
    countdownStartTime = millis();
}

void Countdown::calculateTimeLeft(Game *game)
{
    if ((10 - ((millis() - countdownStartTime) / 1000)) != timeLeft)
    {
        timeLeft = (10 - ((millis() - countdownStartTime) / 1000));
        if (timeLeft == 0)
        {
            //check false start
            sensors_event_t a, g, temp;
            mpu.getEvent(&a, &g, &temp);
            Serial.println(a.acceleration.x);
            if (a.acceleration.x < 6)
            {
                tone(buzzerPin, 200, 250);
                radio.sendFalseStartCommand();
                game->setState(FalseStart::getInstance(true));
                return;
            }

            tone(buzzerPin, 440, 200);
            game->setState(Play::getInstance());
        }
        else
        {
            tone(buzzerPin, 300, 100);
        }
    }
}

void Countdown::render(Game *game)
{
    calculateTimeLeft(game);

    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Countdown: ");
    display.setFont(ArialMT_Plain_24);
    display.drawString(40, 25, String(timeLeft));

    // Display it on the screen
    display.display();
}

void Countdown::command(Game *game, int command)
{
    if (command == 10)
    {
        Serial.println("False Start during countdown!");
        game->setState(FalseStart::getInstance(false));
    }
}

GameState &Countdown::getInstance()
{
    static Countdown singleton;
    return singleton;
}

void Result::enter(Game *game)
{
    sceneStartTime = millis();
    tone(buzzerPin, 300, 100);
}

void Result::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Countdown: ");

    // Display it on the screen
    display.display();

    if (millis() - sceneStartTime > 5000)
    {
        game->setState(WaitingStart::getInstance());
    }
}

GameState &Result::getInstance()
{
    static Result singleton;
    return singleton;
}

FalseStart::FalseStart(bool isFalseStartPlayer)
{
    isFalsePlayer = isFalseStartPlayer;
}

void FalseStart::enter(Game *game)
{
    sceneStartTime = millis();
    tone(buzzerPin, 300, 100);
}

void FalseStart::render(Game *game)
{
    display.clear();
    // Print to the screen
    display.setFont(ArialMT_Plain_16);
    if (isFalsePlayer)
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

GameState &FalseStart::getInstance(bool isFalseStartPlayer)
{
    static FalseStart singleton(isFalseStartPlayer);
    return singleton;
}
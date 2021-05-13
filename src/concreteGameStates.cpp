#include "concreteGameStates.h"
#include "infoScreens.h"
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
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "Start?");
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
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 0, "PLAY");
}

void Play::trigger(Game *game)
{
    ir.shoot();
}

void Play::command(Game *game, int command)
{
    if (command == 52)
    {
        Serial.println("player one won");
        game->score[0]++;
        game->setState(Won::getInstance(game->isPlayerOne ? true : false));
    }
    else if (command == 53)
    {
        Serial.println("player two won");
        game->score[1]++;
        game->setState(Won::getInstance(game->isPlayerOne ? false : true));
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

    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Countdown: ");
    display.setFont(ArialMT_Plain_24);
    display.drawString(40, 25, String(timeLeft));
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
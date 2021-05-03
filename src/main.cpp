#include <Arduino.h>
#include <Wire.h>
#include "game.h"
#include "gameState.h"
#include "concreteGameStates.h"
#include "radio.h"
#include "ir.h"

#include "SSD1306Wire.h"
#include <ESP8266WiFi.h>
#include <espnow.h>

Game game;
Radio radio;
IR ir;

SSD1306Wire display(0x3c, 5, 4);

extern const uint16_t IrLedPin = 13;
extern const int buzzerPin = 14;
const int buttonPin = 15;
int buttonState = 0;

void setup()
{
  pinMode(buttonPin, INPUT);

  display.init();
  display.setContrast(255);


  Serial.begin(115200);

  delay(1000);

  Serial.println("Hi!!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonPin)){
    game.trigger();
  }

  game.render();
  delay(2);
}
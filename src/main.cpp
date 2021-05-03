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
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Game game;
Radio radio;
IR ir;

Adafruit_MPU6050 mpu;
SSD1306Wire display(0x3c, 5, 4);

extern const uint16_t IrLedPin = 13;
extern const int buzzerPin = 14;
const int buttonPin = 15;
int buttonState = 0;

void setup()
{
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);

  Serial.println("Setup OLED");

  display.init();
  display.setContrast(255);

  Serial.println("Setup MPU");

  Wire.begin(5, 4);
  // Try to initialize mpu
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    /*while (1) {
      delay(10);
    }*/
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  delay(100);

  Serial.println("Hi!!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonPin)){
    game.trigger();
  }

  game.render();
}
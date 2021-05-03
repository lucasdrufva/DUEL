#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <algorithm>
#include <iostream>

class Radio
{
public:
    Radio();
    void sendStartCommand();
    void sendFalseStartCommand();

private:
    uint8_t otherPlayerAddress[6];
    const uint8_t firstGunAddres[6] = {0x40, 0xF5, 0x20, 0x10, 0xBA, 0x95};
    const uint8_t secondGunAddres[6] = {0x40, 0xF5, 0x20, 0x10, 0x5F, 0xD6};

    void setOtherPlayerAddress();
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
};

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
  int command;
} struct_message;
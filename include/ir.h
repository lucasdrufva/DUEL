#pragma once
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "game.h"

class IR
{
public:
    IR();
    void shoot();

private:
    uint16_t sAddress;
    uint16_t sCommand;
    uint64_t nec;
};
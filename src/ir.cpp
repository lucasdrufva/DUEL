#include "ir.h"


extern const uint16_t IrLedPin;
IRsend irsend(IrLedPin);

extern Game game;

void IR::begin(){
    Serial.println("Init ir");

    irsend.begin();
    if(game.isPlayerOne){
        sCommand = 0x0034;
        nec = irsend.encodeNEC(sAddress, sCommand);
    }else {
        sCommand = 0x0035;
        nec = irsend.encodeNEC(sAddress, sCommand);
    }
}

void IR::shoot(){
    irsend.sendNEC(nec);
    Serial.println("shoot ir");
}
#include "ir.h"

extern const uint16_t IrLedPin;
IRsend irsend(IrLedPin);

extern Game game;

IR::IR(){
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
}
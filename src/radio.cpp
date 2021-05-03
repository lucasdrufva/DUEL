#include "radio.h"
#include "game.h"

extern Game game;
struct_message message;

void Radio::setOtherPlayerAddress()
{
  if (game.isPlayerOne)
  {
    std::copy(std::begin(secondGunAddres), std::end(secondGunAddres), std::begin(otherPlayerAddress));
  }
  else
  {
    std::copy(std::begin(firstGunAddres), std::end(firstGunAddres), std::begin(otherPlayerAddress));
  }
}

void handleCommand(int command){
    game.command(command);
}

Radio::Radio()
{
    // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  setOtherPlayerAddress();

  // Init ESP-NOW
  if (esp_now_init() != 0)
  {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  //esp_now_register_send_cb(OnDataSent);
  //esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *incomingData, uint8_t len){
    memcpy(&message, incomingData, sizeof(message));
    handleCommand(message.command);
  });

  // Register peer
  esp_now_add_peer(otherPlayerAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void Radio::sendStartCommand(){
    message.command = 20;
    esp_now_send(otherPlayerAddress, (uint8_t *)&message, sizeof(message));
}

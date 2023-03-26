
#include "defaults.h"

#include "Network.h"
#include "Ntp.h"
#include "Mqtt.h"
#include "Sensors.h"
#include "WebApi.h"


void setup()
{
  Serial.begin(SERIAL_BAUDRATE);
  while (!Serial)
    yield();

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("[SPIFFS] : An Error has occurred while mounting SPIFFS");
    return;
  }

  Network.init();
  Ntp.init();
  WebApi.init();
  Sensors.init();

  Mqtt.init();
}

void loop()
{
  Network.loop();
  Sensors.loop();
  WebApi.loop();

  Mqtt.loop();
}
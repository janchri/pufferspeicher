
#include "defaults.h"
#include "Logger.h"

#include "Network.h"
#include "Ntp.h"
#include "Mqtt.h"
#include "Sensors.h"
#include "WebApi.h"


void setup()
{
  Logger.begin();

  if (!LittleFS.begin()) {
    Logger.println("[LittleFS] : An error has occurred while mounting.");
  }
  Logger.println("[LittleFS] :  ... successfully mounted.");

  Network.init();
  Ntp.init();
  WebApi.init();
  Sensors.init();
  Mqtt.init();
}

void loop()
{
  delay(1);
  Network.loop();
  Sensors.loop();
  WebApi.loop();
  Mqtt.loop();
}
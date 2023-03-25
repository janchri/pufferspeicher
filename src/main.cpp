
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

  Network.init();
  Ntp.init();
  Sensors.init();

  Mqtt.init();
  WebApi.init();
}

void loop()
{
  Network.loop();
  Sensors.loop();
  Mqtt.loop();
  WebApi.loop();
}
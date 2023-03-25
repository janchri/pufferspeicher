
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
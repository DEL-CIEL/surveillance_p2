#include <Arduino.h>
#include "SSD1306.h"
#include "Wire.h"

SSD1306 ecranOled(0x3c, 5, 4);

void setup()
{
  ecranOled.init();
  ecranOled.clear();
  ecranOled.setFont(ArialMT_Plain_16);
  ecranOled.drawString(0, 10, "Mon Appli V1.0");
  ecranOled.display();
}

void loop()
{

}
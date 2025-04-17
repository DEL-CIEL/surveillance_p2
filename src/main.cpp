#include <Arduino.h>
#include "SSD1306.h"
#include "Wire.h"
#include "CSon.h"

SSD1306 ecranOled(0x3c, 5, 4);
CSon son;

void setup()
{
  Serial.begin(9600);

  ecranOled.init();
  ecranOled.clear();
  ecranOled.setFont(ArialMT_Plain_16);
  ecranOled.drawString(0, 10, "Mon Appli V1.0");
  ecranOled.display();

  son.Setup();
}

void loop()
{
  son.SamplesDmaAcquisition();
  Serial.print("nvSonoreMoyen: ");
  Serial.println(son.niveauSonoreMoyen);
  sleep(1);
  Serial.print("nvSonoreCrete: ");
  Serial.println(son.niveauSonoreCrete);
  sleep(1);
}
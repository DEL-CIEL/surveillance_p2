#include <Arduino.h>
#include "SSD1306.h"
#include "Wire.h"
#include "CSon.h"

#define PERIODE_RELEVE 10000  // période relevé et envoi en ms

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
  float niveauSonoreMoy=0; 
  int periodeReleve = PERIODE_RELEVE/son.tempsEchantillon;

  float niveauSonoreMoyenDB=0; 
  float niveauSonoreCreteDB=0;

  niveauSonoreMoyenDB = 20 * log10( niveauSonoreMoy )-14.56 ;   
  niveauSonoreCreteDB = 20 * log10( son.niveauSonoreCrete )-18.474 ;

  son.SamplesDmaAcquisition();
  Serial.print("niveuaSonoreCreteDB: ");
  Serial.println(niveauSonoreCreteDB);
  sleep(1);
  Serial.print("niveauSonoreMoyenDB: ");
  Serial.println(niveauSonoreMoy);
  sleep(1);
}
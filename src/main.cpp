#include <Arduino.h>
#include "SSD1306.h"
#include "Wire.h"
#include "CSon.h"

#define PERIODE_RELEVE 10000  // période relevé et envoi en ms

SSD1306 ecranOled(0x3c, 5, 4);
CSon son;
int compteurAffichage = 0;


void AfficherSpectre(float* vRe) {
  int largeurBarre = 1;       // Largeur de chaque barre
  int espacement = 0;         // Espacement entre les barres
  int hauteurMax = 63;        // Hauteur maximale de l'écran (64 lignes)

  ecranOled.clear();          // Effacer l'écran

  // Affichage du spectre (128 colonnes disponibles sur l'écran)
  for (int i = 1; i < 128; i++) {
    double val = vRe[i];
    int hauteurBarre = map(val, 0, 700000, 0, hauteurMax);

    // Dessiner une barre verticale (à partir du bas de l'écran)
    ecranOled.fillRect(i * (largeurBarre + espacement), 64 - hauteurBarre, largeurBarre, hauteurBarre);
  }

  ecranOled.display();  // Mettre à jour l'écran
}


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

  if(compteurAffichage % 2 == 0)
  {
    AfficherSpectre(son.vReal);
  } compteurAffichage++; 
}
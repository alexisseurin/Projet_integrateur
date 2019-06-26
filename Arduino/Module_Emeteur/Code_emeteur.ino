
/**
 * Exemple de code pour la bibliothèque VirtualWire – Client d'envoi de texte
 */
 
#include <VirtualWire.h>

int RF_TX_PIN = A0;
int salut = 65;

void setup() {
  Serial.begin(9600);

  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
   vw_set_tx_pin(RF_TX_PIN);
  
  Serial.println("Go !"); 
}
 
void loop() {
  
  // Lit un nombre depuis le port série
  float val = Serial.parseFloat();
  Serial.println(val
  );
  
  vw_send((byte *) &val, sizeof(val)); // On envoie le message
  
  vw_send((byte *) &salut, sizeof(salut)); // On envoie le message
    Serial.println(salut);
  vw_wait_tx(); // On attend la fin de l'envoi
}

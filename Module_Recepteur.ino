//                                    Code du recepteur 433 MHz                                    */


#include <VirtualWire.h>

int analogPin = A0;
float vitesse;
float trmin;

void setup() {
  Serial.begin(9600);

  // Initialisation de la bibliothèque VirtualWire
  vw_set_rx_pin(analogPin);
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages

  Serial.println("Go !");
}

void loop() {
  float val;
  float pst;
  float dis;
  byte taille_message = sizeof(val);



  // recuperation des données et calcul pour la vitesse
  if (vw_get_message((byte *) &val, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non
    trmin = val / 20 * 60;
    vitesse = (2 * PI * 0.0325 * trmin / 60) * 10; // Formule pour calculer la vitesse
    vitesse = vitesse - 102; // déchiffrage

    Serial.print("Vitesse : ");
    Serial.println(vitesse); // Affiche le message

    /* if (vitesse <= 2.5 && vitesse >= -2.5)
      {
       Serial.print("Vitesse : ");
       Serial.println(vitesse); // Affiche le message
      }*/
    delay(100);
  }

  vw_wait_rx();

}

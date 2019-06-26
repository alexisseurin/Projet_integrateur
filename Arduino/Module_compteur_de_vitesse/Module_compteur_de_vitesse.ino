#include <FreqCounter.h>

// Branchement cable bleu en pin 5
// Branchement cable blanc A0

// Variables utilisées

unsigned long frq;    //fréquence mesurée

int cnt;              //nombre de mesures réalisées

int encoches = 20; //nombre d encoches de la roue codeuse (1 ou plus)

float trmin;  //vitesse de rotation en tour/min

float ms; // vitesse en m/s


// Initialisation

void setup() {

  Serial.begin(9600);   //connection au port série
}

void loop() {

  //compensation (étalonnage)
  FreqCounter::f_comp = 10; // Cal Value / Calibrate with professional Freq Counter
  // 10, 100 ou 1000 ms pour une résolution de 100, 10 et 1 Hz
  FreqCounter::start(100);  // 100 ms Gate Time

  // Attendre jusqu'à avoir un comptage terminé

  while (FreqCounter::f_ready == 0) {
    frq = FreqCounter::f_freq; // a ne pas supprimer permet de calculer le trmn

    trmin = frq / encoches * 60; //Vitesse de rotation en tour/min

    Serial.print("  tour/min: ");
    Serial.println(trmin);

    ms = (2 * PI * 0.032 * trmin / 60) * 10; // Calcul de la vitesse en m/s

    Serial.print(" vitesse en m/s: ");
    Serial.println(ms);
    delay(500);

  }

}

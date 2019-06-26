#include <SharpIR.h>

#define IR A1// Declaration du PIN analogique du capteur
#define model 1080 // Reference du capteur de la librairie
const int led = 8;

SharpIR SharpIR(IR, model);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {

  int distance = SharpIR.distance();  // Cela retourne à la distance à l'objet que vous mesurez

  Serial.print("Distance: ");
  Serial.print(distance); // Affichage dans le moniteur série
  Serial.println("  cm ");

  if (distance > 8 ) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  delay(500);
}

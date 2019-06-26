#include <Wire.h>
#include <SharpIR.h>
#include <VirtualWire.h>
#include "VirtualWire.h"
#include "Grove_I2C_Motor_Driver.h"
#include <FreqCounter.h>  //Inclure la librairie de fréquence
#define I2C_ADDRESS 0x0F

#include <SharpIR.h>
#define IR A1 // Declaration du PIN analogique du capteur
#define model 1080 // Reference du capteur de la librairie

//Declaration des vitesses
// Motor 1 : Deux moteurs de gauche
// Motor 2 : Deux moteurs de droite

//-------------------------------------------------------------------------------
// Declaration pin radio
int RF_TX_PIN = A2;

// Declaration vitesse moteur
int V_Max = 50;

//Declaration des capteurs suiveur de ligne

const int capteurGauche = 4;
const int capteurCentre = 3;
const int capteurDroit = 2;
const int capteurVGauche = 6;
const int capteurVDroit = 7;

bool etatcapteurGauche;
bool etatcapteurCentre;
bool etatcapteurDroit;
bool etatcapteurVGauche;
bool etatcapteurVDroit;

// Variables utilisées

unsigned long frq;    //fréquence mesurée
int cnt;              //nombre de mesures réalisées
int encoches = 20; //nombre d encoches de la roue codeuse (1 ou plus)
float trmin;  //vitesse de rotation en tour/min
float ms; // vitesse en m/s

// Variable LED distance
const int led = 8;
float val = 0;
int pin_sharp = A1;  // fil jaune du capteur sharp branché


//---------------------------------------------------------------------------
void setup() {
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);

  // Initialisation des capteurs

  pinMode(capteurGauche, INPUT);
  pinMode(capteurCentre, INPUT);
  pinMode(capteurDroit, INPUT);
  //  pinMode(capteurtGauche, INPUT);

  // Initionlisation de la radio

  vw_set_tx_pin(RF_TX_PIN); // Setup transmit pin
  vw_setup(2000); // Transmission speed in bits per second.



  // Initialisation de la LED
  pinMode(led, OUTPUT);
  analogReference(EXTERNAL); // tension analogique max sera 3,3 V


}

//---------------------------------------------------------------------------
//Fonctions pour les moteurs
void avancer()
{
  Motor.speed(MOTOR1, V_Max);
  Motor.speed(MOTOR2, V_Max);

  delay(200);
  Serial.println("Avant !");
}

void gauche()
{
  Motor.speed(MOTOR2, 55);
  Motor.speed(MOTOR1, -30);
  delay(200);
  Serial.println("Gauche !");
}

void droite()
{
  Motor.speed(MOTOR2, -30);
  Motor.speed(MOTOR1, 55);
  delay(200);
  Serial.println("Droite !");
}

void reculer()
{
  // Fonction encore a tester pour quand les 3 capteurs sont en blanc
  Motor.speed(MOTOR1, -45);
  Motor.speed(MOTOR2, -45);
  Serial.println("Recule");
}

//---------------------------------------------------------------------------
// Mode suiveur de ligne

void Suiveur()
{
  etatcapteurGauche = digitalRead(capteurGauche);
  etatcapteurCentre = digitalRead(capteurCentre);
  etatcapteurDroit = digitalRead(capteurDroit);
  etatcapteurVGauche = digitalRead(capteurVGauche);
  etatcapteurVDroit = digitalRead(capteurVDroit);

  if (etatcapteurCentre) //Si le capteur du centre détecte du noir
  {
    if ((etatcapteurGauche) && (!etatcapteurDroit)) { //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
      Serial.println("Tourner à gauche");
      digitalWrite(capteurVGauche, LOW);

      gauche();
    }
    else if ((!etatcapteurGauche) && (etatcapteurDroit)) { //S'il y a du blanc à gauche et du noir à droite, tourner à droite
      Serial.println("Tourner à droite");

      droite();

    }
    else {
      Serial.println("Avancer tout droit");

      avancer();
      //Si les conditions plus haut ne s'appliquent pas, continuer tout droit
    }

  }

  else //Si le capteur du centre détecte du blanc
  {
    if ((etatcapteurGauche) && (!etatcapteurDroit)) {
      Serial.println("Tourner à gauche");
      gauche();
      //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
    }

    else if ((!etatcapteurGauche) && (etatcapteurDroit)) {
      Serial.println("Tourner à droite");
      droite();
      //S'il y a du blanc à gauche et du noir à droite, tourner à droite
    }

    else {
      Serial.println("recule...");

      reculer();
      //Si les conditions plus haut ne s'appliquent pas
    }
  }

  /* if ((etatcapteurGauche) && (etatcapteurDroit)) {
      gauche();
    }

    if ((etatcapteurGauche) && (etatcapteurCentre) && (etatcapteurDroit)) {
      int r;
      r = random(2);

      switch (r) {
        case 0 :
          Serial.println("Menu 0");
          droite();
        case 1:
          Serial.println("Menu 1");
          gauche();
          /* case 2 :
             Serial.println("Menu 2");
             avancer();
      }
    }*/

}

//---------------------------------------------------------------------------
void radiovitesse() {

  float val = analogRead(A0);
  vw_send((byte *) &val, sizeof(val)); // On envoie le message

  vw_wait_tx(); // On attend la fin de l'envoi
  Serial.print("Test Radio vitesse ");
  Serial.println(val);


}

//---------------------------------------------------------------------------
// Valeur moyenne pour le systeme led distance IR
float valeur_moyenne(float taille) {
  int total = 0;
  for (int i = 0; i < taille; i++) {
    float lecture = analogRead(A1);
    total = total + lecture;
  }
  return (total / taille);
}
//--------------------------------------------------------------------------
// Suiveur

void suiveur() {
  etatcapteurGauche = digitalRead(capteurGauche);
  etatcapteurCentre = digitalRead(capteurCentre);
  etatcapteurDroit = digitalRead(capteurDroit);
  etatcapteurVGauche = digitalRead(capteurVGauche);
  etatcapteurVDroit = digitalRead(capteurVDroit);

  if (etatcapteurCentre) //Si le capteur du centre détecte du noir
  {
    if ((etatcapteurGauche) && (!etatcapteurDroit)) { //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
      Serial.println("Tourner à gauche");
      digitalWrite(capteurVGauche, LOW);

      gauche();
    }
    else if ((!etatcapteurGauche) && (etatcapteurDroit)) { //S'il y a du blanc à gauche et du noir à droite, tourner à droite
      Serial.println("Tourner à droite");

      droite();

    }
    else {
      Serial.println("Avancer tout droit");

      avancer();
      //Si les conditions plus haut ne s'appliquent pas, continuer tout droit
    }

  }

  else //Si le capteur du centre détecte du blanc
  {
    if ((etatcapteurGauche) && (!etatcapteurDroit)) {
      Serial.println("Tourner à gauche");
      gauche();
      //S'il y a du noir à gauche et du blanc à droite, tourner à gauche
    }

    else if ((!etatcapteurGauche) && (etatcapteurDroit)) {
      Serial.println("Tourner à droite");
      droite();
      //S'il y a du blanc à gauche et du noir à droite, tourner à droite
    }

    else {
      Serial.println("recule...");

      reculer();
      //Si les conditions plus haut ne s'appliquent pas
    }
  }

}
//--------------------------------------------------------------------------

void loop() {

  suiveur();
  radiovitesse();

  //--------------------------------------------------------
  // Systeme pour la mesure de la place
  float distance = 32076.69016894 * pow(valeur_moyenne(10), -1.245865753);
  Serial.print(distance);
  Serial.print("cm : ");//affichage a l'écran

  //Detection d'obstalcles
  if (distance < 10) {
    digitalWrite(led, LOW);
    Serial.println("Il y'a un obstacle");
  }

  else if (distance > 10 ) {
    digitalWrite(led, HIGH);
    Serial.println("Il y'a une place de libre");
  }

}

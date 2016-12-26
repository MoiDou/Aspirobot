/*librairie de gestion des capteurs US de detection de distance*/
/*Pierre de MONTIGNY*/
/*le 17 novembre 2016*/
/*V 1.1*/

#include "arduino.h"
#include "gestionUS.h"

gestionUS::gestionUS(int distance_detection , int nb_mesure, int trig_gauche, int trig_droit, int echo_droit, int echo_gauche, int trig_centre, int echo_centre)
{
	pinMode(trig_droit, OUTPUT);
	pinMode(trig_gauche, OUTPUT);
	pinMode(trig_centre, OUTPUT);
	digitalWrite(trig_droit, LOW);
	digitalWrite(trig_gauche, LOW);
	digitalWrite(trig_centre, LOW);
	pinMode(echo_droit, INPUT);
	pinMode(echo_gauche, INPUT);
	pinMode(echo_centre, INPUT);
	cm_droit = new long[nb_mesure+1];
	cm_gauche = new long[nb_mesure+1];
	cm_centre = new long[nb_mesure+1];
	cm_droit[nb_mesure] = 0;
	cm_gauche[nb_mesure] = 0;
	cm_centre[nb_mesure] = 0;
}

int gestionUS::detectionObstacle(int distance_detection , int nb_mesure, int trig_gauche, int trig_droit, int echo_droit, int echo_gauche, int trig_centre, int echo_centre)
{
	obstacle = 0;
  for (i = 0; i < nb_mesure; i ++)
  {
    digitalWrite(trig_droit, HIGH);	// front haut pour activer le Tx US
    delayMicroseconds(30);
    digitalWrite(trig_droit, LOW);
    lecture_echo_droit = pulseIn(echo_droit, HIGH); // ecoute du Rx US
	
    digitalWrite(trig_gauche, HIGH);	// front haut pour activer le Tx US
    delayMicroseconds(30);
    digitalWrite(trig_gauche, LOW);
    lecture_echo_gauche = pulseIn(echo_gauche, HIGH);	// ecoute du Rx US
	
	digitalWrite(trig_centre, HIGH);	// front haut pour activer le Tx US
    delayMicroseconds(30);
    digitalWrite(trig_centre, LOW);
    lecture_echo_centre = pulseIn(echo_centre, HIGH);	// ecoute du Rx US

    cm_droit[i] = lecture_echo_droit / 58;	//calcul du temps de retour US (valeur dépendante du capteur)
    cm_gauche[i] = lecture_echo_gauche / 58; //calcul du temps de retour US (valeur dépendante du capteur)
	cm_centre[i] = lecture_echo_centre / 58;

    cm_droit[nb_mesure] = cm_droit[nb_mesure] + cm_droit[i]; //incrémentation du tableau des prises de mesures de distances
    cm_gauche[nb_mesure] = cm_gauche[nb_mesure] + cm_gauche[i];
	cm_centre[nb_mesure] = cm_centre[nb_mesure] + cm_centre[i];
	/*
	Serial.println("Distance gauche : ");
    Serial.println(cm_gauche[i]);
	Serial.println("Distance droit : ");
    Serial.println(cm_droit[i]);
	Serial.println("Distance centre : ");
    Serial.println(cm_centre[i]);
	*/
  }
   
    cm_droit[nb_mesure] = cm_droit[nb_mesure]/nb_mesure;	//moyenne des mesure (distance1+distance2+distance3+.... / nombre de mesure)
    cm_gauche[nb_mesure] = cm_gauche[nb_mesure]/nb_mesure;
	cm_centre[nb_mesure] = cm_centre[nb_mesure]/nb_mesure;

   if ((cm_droit[nb_mesure] > distance_detection) and (cm_gauche[nb_mesure] > distance_detection) and (cm_centre[nb_mesure] > distance_detection))
    {
      obstacle = 0; // pas d'obstacle
    }

   if (((cm_droit[nb_mesure] > distance_detection) and (cm_gauche[nb_mesure] < distance_detection) and (cm_centre[nb_mesure] < distance_detection)) or ((cm_droit[nb_mesure] > distance_detection) and (cm_gauche[nb_mesure] < distance_detection) and (cm_centre[nb_mesure] > distance_detection)))
    {
      obstacle = 1; // obstacle a gauche
    }

   if (((cm_droit[nb_mesure] < distance_detection) and (cm_gauche[nb_mesure] > distance_detection) and (cm_centre[nb_mesure] < distance_detection)) or ((cm_droit[nb_mesure] < distance_detection) and (cm_gauche[nb_mesure] > distance_detection) and (cm_centre[nb_mesure] > distance_detection)))
    {
      obstacle = 2; // obstacle a droite
    }

   if (((cm_droit[nb_mesure] < distance_detection) and (cm_gauche[nb_mesure] < distance_detection) and (cm_centre[nb_mesure] < distance_detection)) or ((cm_droit[nb_mesure] > distance_detection) and (cm_gauche[nb_mesure] > distance_detection) and (cm_centre[nb_mesure] < distance_detection)))
    {
      obstacle = 3; // iceberg droit devant
    }

  i = 0 ;
  return obstacle ;
}
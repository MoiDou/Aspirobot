/*aspirateur robot*/
/*Pierre et Vincent de MONTIGNY*/
/*le 17 novembre 2016*/
/*V 0.0.1*/
//--------------------------------------------------------------------------------------------------------------

#include <gestionUS.h>

/// definition des broches utilises
int led_droit = 53;
int led_gauche = 52;
int distance_detection = 15; //pour les capteurs US
int nb_mesure = 2; //monbre de mesure pour la moyenne des capteurs US
int trig_gauche = 22;
int trig_droit = 23;
int trig_centre = 25;
int echo_droit = 30;
int echo_gauche = 31;
int echo_centre = 33;
gestionUS gestionUS(distance_detection ,nb_mesure,trig_gauche,trig_droit,echo_droit,echo_gauche,trig_centre,echo_centre);

///definition des variables du programme main
int casDetecte = 0; //cas de détection des capteurs US
double cap = 0;	//valeur du cap suivi mesuré par le compas	
  
void setup()
{
 pinMode(led_droit, OUTPUT);
 pinMode (led_gauche, OUTPUT);
 Serial.begin(9600);
}


void loop()
{
  casDetecte = 0;
 
  casDetecte = gestionUS.detectionObstacle(distance_detection ,nb_mesure,trig_gauche,trig_droit,echo_droit,echo_gauche,trig_centre,echo_centre);
   switch(casDetecte)
  {
   case 0:	//obstacle > distance de détection ->avance
   digitalWrite(led_droit, LOW);
   digitalWrite(led_gauche, LOW);
   break;

   case 1:	//obstacle capteur gauche ->tourne à droite
   digitalWrite(led_droit, LOW);
   digitalWrite(led_gauche, HIGH);
   break;

   case 2:	//obstacle capteur droit ->tourne à gauche
   digitalWrite(led_droit, HIGH);
   digitalWrite(led_gauche, LOW);
   break;

   case 3:	//obstacle capteur centre -> recule et tourne à gauche
   digitalWrite(led_droit, HIGH);
   digitalWrite(led_gauche, HIGH);
   break;
  }
  
  
}

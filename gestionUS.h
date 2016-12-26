/*librairie de gestion des capteurs US de detection de distance*/
/*Pierre de MONTIGNY*/
/*le 17 novembre 2016*/
/*V 1.1*/

#ifndef gestionUS_h
#define gestionUS_h

#include "Arduino.h"

class gestionUS
{
  public:
	gestionUS(int distance_detection , int nb_mesure, int trig_gauche, int trig_droit, int echo_droit, int echo_gauche, int trig_centre, int echo_centre);
	int detectionObstacle(int distance_detection , int nb_mesure, int trig_gauche, int trig_droit, int echo_droit, int echo_gauche, int trig_centre, int echo_centre);
	
  private:
	//variable de la ss fonction detection obstacle
	int obstacle = 0 ;
	long lecture_echo_droit;
	long lecture_echo_gauche;
	long lecture_echo_centre;
	int i; //variable boucle
	int distance_detection;
	int nb_mesure;
  	int trig_gauche;
	int trig_droit;
	int trig_centre;
	int echo_droit;
	int echo_gauche;
	int echo_centre;
	//pointeur tableau ss fonction
	long *cm_droit;
	long *cm_gauche;
	long *cm_centre;

};

#endif
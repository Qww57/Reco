/**
 * \file distance.h
 * \brief calcul de la distance et de la position des boules dans le repère
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée à la mesure de la distance des boules détectées
 * en fonction de leur rayon à l'écran et de la position de la webcam
 *
 */

#ifndef DISTANCE_H
#define DISTANCE_H


int calculDistanceSimplifie(int radius);

float calculDistance(Boule boule, int thetax, int thetay);

position calculPositionSimplifie(Boule boule);

position calculPosition(Boule boule, int thetax, int thetay);


#endif // DISTANCE_H

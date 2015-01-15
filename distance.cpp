/**
 * \file distance.cpp
 * \brief calcul de la distance et de la position des boules dans le repère
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée à la mesure de la distance des boules détectées
 * en fonction de leur rayon à l'écran et de la position de la webcam
 *
 */

#include <math.h>
#include "structures.h"
#include "distance.h"


int calculDistanceSimplifie(int radius){
    // On calcule la distance entre la boule et la caméra en utilisant le théorème de Thalès
    // Webcam bien droite
    // Référence: à 50 cm, on a une boule de la taille 33 ua.
        // On a un résultat en cm à fin
    int distance;
    distance = floor(50*33/radius);
    return distance;
}


position calculPositionSimplifie(Boule boule){ /// TO DO

}


float calculDistance(Boule boule, position camera){ /// TO DO
    // On calcule la distance en utilisant le théorème de Thalès
    // On tient en compte l'angle de la caméra
}



position calculPosition(Boule boule, position camera){

}



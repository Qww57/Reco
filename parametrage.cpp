/**
 * \file parametrage.cpp
 * \brief paramètrage de la détection des couleurs
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie ayant pour but de paramètrer la détection des couleurs par la webcam.
 * Un paramètrage par défaut est prévu.
 *
 */

#include "parametrage.h"
#include "structures.h"


/// PARAMETRAGE DES COULEURS
// Définir les valeurs HSV des couleurs par défault
 jeuCouleurs defaut(){
    jeuCouleurs _defaut;
    _defaut.rouge.iLowH = 0; _defaut.rouge.iHighH = 179;
    _defaut.rouge.iLowS = 244; _defaut.rouge.iHighS = 255;
    _defaut.rouge.iLowV = 45; _defaut.rouge.iHighV = 114;

    _defaut.jaune.iLowH = 3; _defaut.jaune.iHighH = 66;
    _defaut.jaune.iLowS = 231; _defaut.jaune.iHighS = 255;
    _defaut.jaune.iLowV = 62; _defaut.jaune.iHighV = 140;

    _defaut.bleu.iLowH = 110; _defaut.bleu.iHighH = 141;
    _defaut.bleu.iLowS = 55; _defaut.bleu.iHighS = 255;
    _defaut.bleu.iLowV = 6; _defaut.bleu.iHighV = 116;

    return _defaut;
 }



// Définir manuellement les valeurs HSV des couleurs
 void parametrage(int k, colorCalibrage courant, jeuCouleurs sortie){ /// TO DO
    // taper la commande: xmodmap -pk > mykeyboard.txt pour avoir la liste des keycodes
    // ici 9 = SPACE

 }

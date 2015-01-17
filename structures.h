/**
 * \file structures.h
 * \brief définition des structures utilisées
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Définition des structures utilisées
 *
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

/**
 * \struct colorCalibrage
 * \brief structure de paramètrage HSV des couleurs
 *
 * colorCalibrage contient toutes les informations nécessaires pour
 * calibrer une couleur en HSV. On y retrouve ainsi les valeurs mins
 * et max de H, S et V.
 *
 */
struct colorCalibrage{
    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;
};

/**
 * \struct jeuCouleurs
 * \brief structure contenant l'ensemble du paramètrage HSV des couleurs
 *
 * jeuCouleurs contient 3 colorCalibrage. Il permet ainsi de regrouper
 * toutes les valeurs HSV pour les 3 différentes boules de billard.
 *
 */
struct jeuCouleurs{
    colorCalibrage rouge;
    colorCalibrage bleu;
    colorCalibrage jaune;
};

/**
 * \struct position
 * \brief structure décrivant la position dans l'espace
 *
 * position dans un repère (x,y,z) et orientation avec angles
 *
 */
struct position{
    int x;
    int y;
    /*int z;
    float thetax;
    float thetay;
    float thetaz;*/
};

/**
 * \struct position
 * \brief structure décrivant la position dans l'espace avec des flottants
 *
 * Utile pour déterminer la matrice de changement de repère
 *
 */
struct fposition{
    double x;
    double y;
};

/**
 * \struct Boule
 * \brief structure décrivant une Boule
 *
 * contient la couleur de cette boule
 * contient son rayon réel mais aussi celui perçu par la caméra
 * contient la position de la boule
 *
 */
struct Boule {
    std::string couleur;
    double rayon_reel = 27; // 54 mm de diamètre mesuré
    double rayon_vu;
    cv::Point centre;
};

struct jeuBoules {
    Boule rouge;
    Boule jaune;
    Boule bleu;
};

/**
 * \struct Billard
 * \brief structure décrivant le billard
 * \todo affiner les paramètres présents
 *
 *
 *
 */
struct Billard {
    // points vus à l'écran, on s'intéresse qu'à x et y
    cv::Point sommet0;
    cv::Point sommet1;
    cv::Point sommet2;
    cv::Point sommet3;

    /*position sommet1;
    position sommet2;
    position sommet3;
    position sommet4;*/

    fposition fsommet1;
    fposition fsommet2;
    fposition fsommet3;
    fposition fsommet4;

    // longueur vues par la caméra
    double longueur_gauche;
    double longueur_droite;
    double largeur_avant;
    double largeur_arriere;

    // longueur réelles
    double Longueur_reelle;
    double largeur_reelle;

    // points dans le repère vu du dessus

};

#endif // STRUCTURES_H

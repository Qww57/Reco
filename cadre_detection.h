/**
 * \file cadre_detetcion.h
 * \brief programme de detection du billard
 * \author Quentin.T
 * \version 0.1
 * \date 13 janvier 2015
 *
 * Partie dédiée à la reconnaissance du billard
 * lors de l'initialisation du projet
 *
 */


#ifndef CADRE_DETECTION_H
#define CADRE_DETECTION_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"

/// FONCTION PRINCIPALE

/**
 * \fn void cadreDetection_callback(int, void*, Mat img)
 * \brief Fonction de détection du cadre du billard
 *
 * \param Mat img en entrée
 * \return création d'une fenêtre à l'écran "Billard"
 *         où le billard est affiché
 */
void cadreDetection_callback(cv::Mat img, std::vector<cv::Point> anglesBillard);


/**
 * \fn
 * \brief Fonction de détection du cadre du billard
 *
 * \param
 * \return création d'une fenêtre à l'écran "Billard"
 *         où le billard est affiché
 */
std::vector<cv::Point> cadreDetection_callback(cv::Mat img);


/**
 * \fn
 * \brief Fonction de détection du cadre du billard
 *
 * \param
 * \return création d'une fenêtre à l'écran "Billard"
 *         où le billard est affiché
 */
Billard cadreDetection2_callback(cv::Mat img);

bool parametrageCadreDone();


/// AUTRES
/**
 * \fn
 * \brief Distance entre deux points
 *
 * \param cv::Point point1, cv::Point point2
 * \return cv::Point
 */
int distancePoints(cv::Point point1, cv::Point point2);

/**
 * \fn
 * \brief Milieu de deux points
 *
 * \param cv::Point point1, cv::Point point2
 * \return cv::Point
 */
cv::Point milieuPoints(cv::Point point1, cv::Point point2);

/**
 * \fn
 * \brief Périmètre d'un contours
 *
 * \param std::vector<cv::Point> contours
 * \return int perimetre
 */
int perimetrePoints(std::vector<cv::Point> contours);


/**
 * \fn
 * \brief Fonction de repositionnement des angles détectés
 *
 * \param listes de cv::Point en entrée
 * \return void
 *
 *  Lorsque l'on obtient la liste des angles des quadrilatères, on ne sait pas
 *  où est l'angle d'origine du quadrilatère. Cette fonction a pour but de placer
 *  cet angle en haut à gauche de l'écran.
 *  Le booléen sert à avoir un affichage graphique pour tracer ce que la fonction
 *  effectue sur l'image cv::Mat en entrée.
 *
 */
void repositionnement(std::vector<cv::Point> &contours, cv::Mat dst, bool aff);


#endif // CADRE_DETECTION_H

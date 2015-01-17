/**
 * \file reconnaissance.h
 * \brief programme de detection des formes et des couleurs
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée à la reconnaissance du billard et de ses boules
 *
 */

#ifndef RECONNAISSANCE_H
#define RECONNAISSANCE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"

extern int thresh;
extern int max_thresh;
extern colorCalibrage calibrage;


/// CREATION DES FENETRES


/**
 * \fn void contours_callback(int, void*, Mat img)
 * \brief Fonction de test de la détection des contours
 *
 * \param Mat img en entrée
 * \return création d'une fenêtre à l'écran montrant les contours
 */
void contours_callback(cv::Mat imgG);


/**
 * \fn void color_callback(int, void*, Mat img)
 * \brief Fonction de test de la détection des couleurs
 *
 * \param Mat img en entrée
 * \return création d'une fenêtre à l'écran où les couleurs sont détectées par seuil
 */
void color_callback(cv::Mat img, colorCalibrage *calibrage);



/// CREATION DES TRACKBARS


/**
 * \fn void contours_createtrackbar()
 * \brief Fonction de création des trackbars de contours_callback()
 *
 * \param
 * \return création d'une trackbar sur la fenêtre "contours" de contours_callback()
 */
void contours_createtrackbar();

/**
 * \fn void color_createtrackbar()
 * \brief Fonction de création des trackbars de color_callback()
 *
 * \param
 * \return création d'une trackbar sur la fenêtre "Thresholded Image" de color_callback()
 */
void color_createtrackbar();



#endif //RECONNAISSANCE_H

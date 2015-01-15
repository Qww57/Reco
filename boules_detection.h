/**
 * \file boules_detection.h
 * \brief programme de detection des boules
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée à la reconnaissance des boules de billard
 *
 */

extern int sigmaX;
extern int sigmaY;
extern int minRayon;
extern int maxRayon;

#ifndef BOULES_DETECTION_H
#define BOULES_DETECTION_H

/**
 * \fn void bouleDetection_callback(int, void*, Mat img)
 * \brief Fonction de détection des boules de billard
 *
 * \param Mat img en entrée
 * \return création d'une fenêtre à l'écran "Boule"
 *         où les boules sont détectées, retracées et où leur distance est affichée
 */
void bouleDetection_callback(int, void*, cv::Mat img);


/**
 * \fn void bouleDetection_createtrackbar()
 * \brief Fonction de création des trackbars de bouleDetection_callback()
 *
 * \param
 * \return création d'une trackbar sur la fenêtre "Boules" de bouleDetection_callback()
 */
void bouleDetection_createtrackbar();

#endif // BOULES_DETECTION_H

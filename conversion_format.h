/**
 * \file conversion_format.cpp
 * \brief programmes de conversion des types
 * \author Quentin.T
 * \version 0.1
 * \date 13 janvier 2015
 *
 * Partie dédiée aux différentes fonctions de conversions
 * des types de données utilisés par le reste des programmes
 *
 */


#ifndef CONVERSION_FORMAT_H
#define CONVERSION_FORMAT_H

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"

/**
 * \fn string int2string(int a)
 * \brief Fonction de conversion d'un entier en string
 *
 * \param entier à convertir
 * \return entier converti en string
 */
std::string int2string(int a);

/**
 * \fn string int2string(cv::Point point)
 * \brief Fonction de conversion d'un entier en string
 *
 * \param entier à convertir
 * \return entier converti en string
 */
std::string point2string(cv::Point point);

/**
 * \fn position point2position(cv::Point point)
 * \brief Fonction de conversion d'un cv::Point en position
 *
 * \param Point à convertir
 * \return position convertie
 */
position point2position(cv::Point point);


fposition point2fposition(cv::Point point);

#endif //CONVERSION_FORMAT_H

/**
 * \file projection.h
 * \brief Programme de projection du billard dans le plan
 * \author Quentin.T
 * \version 0.1
 * \date 15 janvier 2015
 *
 *
 *
 *
 */

 #include <vector>
 #include "structures.h"


/// MATRICE de passage à partir des positions à l'écran et des vraies valeurs de l et L
//   A B
//   C D

float parametreA(fposition pos1, fposition pos2, float l, float L);

float parametreB(fposition pos1, fposition pos2, float l, float L);

float parametreC(fposition pos1, fposition pos2, float l, float L);

float parametreD(fposition pos1, fposition pos2, float l, float L);

std::vector<std::vector<float> > matricedepassage(position pos1, position pos2, float l, float L);

std::vector<fposition> produitmatriciel2x2(std::vector<fposition> contours, float A, float B, float C, float D);

std::vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4);

std::vector<float> float2vector(float A, float B, float C, float D);

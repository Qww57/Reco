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

float parametreE(Billard billard, float l, float L);

float parametreB(Billard billard, float l, float L, float E);

float parametreA(Billard billard, float l, float L, float E, float B);

float parametreF(Billard billard, float l, float L);

float parametreD(Billard billard, float l, float L, float F);

float parametreC(Billard billard, float l, float L, float F, float D);

bool test_parametre(Billard billard, float E);

std::vector<std::vector<float> > matricedepassage(position pos1, position pos2, float l, float L);

std::vector<fposition> produitmatriciel2x2(std::vector<fposition> contours, std::vector<float> coefficients);

std::vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4);

std::vector<float> float2vector(float A, float B, float C, float D, float E, float F);

void affichage_projection(std::vector<cv::Point> cadre, cv::Mat drawing);

cv::Mat changement_echelle(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4);

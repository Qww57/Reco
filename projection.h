/**
 * \file projection.h
 * \brief Programme de projection du billard dans le plan
 * \author Quentin.T
 * \version 0.1
 * \date 15 janvier 2015
 *
 *  A DEBUGER
 *
 *
 */

 #include <vector>
 #include "structures.h"


/// MATRICE de passage à partir des positions à l'écran et des vraies valeurs de l et L
//   A B
//   C D

double parametreE(Billard billard, double l, double L);

double parametreB(Billard billard, double l, double L, double E);

double parametreA(Billard billard, double l, double L, double E, double B);

double parametreF(Billard billard, double l, double L);

double parametreD(Billard billard, double l, double L, double F);

double parametreC(Billard billard, double l, double L, double F, double D);

bool test_parametre(Billard billard, double E);

std::vector<double> matrice(Billard b, float L, float l);

std::vector<std::vector<double> > matricedepassage(position pos1, position pos2, double l, double L);

std::vector<fposition> produitmatriciel2x2(std::vector<fposition> contours, std::vector<double> coefficients);

fposition produitmatriciel2x2simple(fposition point, std::vector<double> coefficients);

std::vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4);

std::vector<double> double2vector(double A, double B, double C, double D, double E, double F);

void affichage_projection(std::vector<cv::Point> cadre, cv::Mat drawing);

cv::Mat changement_echelle(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4);// pas utilisée

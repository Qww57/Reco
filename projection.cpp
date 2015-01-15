/**
 * \file projection.cpp
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
#include <math.h>
#include <limits>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "structures.h"

using namespace std;
using namespace cv;


/// MATRICE de passage à partir des positions à l'écran et des vraies valeurs de l et L
//   A B
//   C D

float parametreA(fposition pos1, fposition pos2, float l, float L){ // A TESTER
    float A;
    A = - l / (pos2.y - (pos1.y/pos1.x)*pos2.x) * (pos2.x / pos1.x);
    if ((A != A) || (isinf(A)))
        A = 1;
    return A;
}

float parametreB(fposition pos1, fposition pos2, float l, float L){ // A TESTER
    float B;
    B = l / (pos2.y - (pos1.y/pos1.x)*pos2.x);
    if ((B != B) || (isinf(B)))
        B = 1;
    return B;
}

float parametreC(fposition pos1, fposition pos2, float l, float L){ // A TESTER
    float C;
    C = (L - (L*(1-pos2.x/pos1.x)/(pos2.y - (pos1.y/pos1.x)*pos2.x))*pos1.y)/pos1.x;
    if ((C != C) || (isinf(C)))
        C = 1;
    return C;
}

float parametreD(fposition pos1, fposition pos2, float l, float L){ // A TESTER
    float D;
    D = L*(1-pos2.x/pos1.x)/(pos2.y - (pos1.y/pos1.x)*pos2.x);
    if ((D != D) || (isinf(D)))
        D = 1;
    return D;
}


// VERIFIER LA POSITION DE CHACUN DES SOMMETS / QUI EST OU ?

fposition produitmatriciel2x2simple(fposition point, float A, float B, float C, float D){
    fposition sortie;
    sortie.x = A*point.x + B*point.y;
    sortie.y = C*point.x + D*point.y;
    return sortie;
}

vector<fposition> produitmatriciel2x2(vector<fposition> contours, float A, float B, float C, float D){
    vector<fposition> sortie;
    for (int i=0; i <= contours.size();i++)
        sortie[i]= produitmatriciel2x2simple(contours[i], A, B, C, D);
    return sortie;
}

vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4){
    vector<fposition> sortie;
    sortie[0] = position1;
    sortie[1] = position2;
    sortie[2] = position3;
    sortie[3] = position4;
    return sortie;
}

vector<float> float2vector(float A, float B, float C, float D){
    vector<float> sortie;
    sortie[0] = A; sortie[1] = B; sortie[2] = C; sortie[3] = D;
    return sortie;
}

// VERIFIER LA POSITION DE CHACUN DES SOMMETS / QUI EST OU ?
void conversionRepereBillard(Billard _billard){  // A FAIRE
        //matricedepassage(_billard.sommet1, _billard.sommet2);

}

void affichage_projection(vector<Point> cadre, Mat dst, vector<vector<float> > matrice){

}

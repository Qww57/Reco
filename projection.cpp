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
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "structures.h"

using namespace std;
using namespace cv;



/// \todo voir pourquoi dans le main fposition2vector fait tout planter

/// MATRICE de passage à partir des positions à l'écran et des vraies valeurs de l et L
//   A B
//   C D
bool test_parametre(Billard billard, float E){
    bool probleme = false;
    if ((E != E) || (isinf(E))||(E==0)||(abs(E)>100)||(abs(E)<0.00001)){
        probleme = true;
    }
    return probleme;
}


float parametreE(Billard billard, float l, float L){
    float E;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    float W = Y*billard.fsommet3.x - billard.fsommet3.x;
    float X = billard.fsommet2.y - Y*billard.fsommet2.x;
    float Edenom = ((1-billard.sommet2.x/billard.fsommet1.x)*Y + (1-billard.fsommet3.x/billard.fsommet1.x)*W);
    E = L*(W+X) / Edenom;
    if (test_parametre(billard, E))
        E = 1;
    return E;
}

float parametreB(Billard billard, float l, float L, float E){ // A TESTER
    float B;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    float X = billard.fsommet2.y - Y*billard.fsommet2.x;
    B = (L-E*(1-billard.fsommet2.x/billard.fsommet1.x))/X;
    if (test_parametre(billard, B))
        B = 1;
    return B;
}

float parametreA(Billard billard, float l, float L, float B, float E){ // A TESTER
    float A;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    A = -B*Y -E/billard.fsommet1.x;
    if (test_parametre(billard, A))
        A = 1;
    return A;
}

float parametreF(Billard billard, float l, float L){
    float F;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    float W = Y*billard.fsommet3.x - billard.fsommet3.x;
    float X = billard.fsommet4.y - Y*billard.fsommet4.x;
    float Fdenom = ((1-billard.sommet4.x/billard.fsommet1.x)*Y + (1-billard.fsommet3.x/billard.fsommet1.x)*W);
    F = l*(W+X) / Fdenom;
    if (test_parametre(billard, F))
        F = 1;
    return F;
}

float parametreD(Billard billard, float l, float L, float E){ // A TESTER
    float D;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    float X = billard.fsommet4.y - Y*billard.fsommet4.x;
    D = (l-E*(1-billard.fsommet4.x/billard.fsommet1.x))/X;
    if (test_parametre(billard, D))
        D = 1;
    return D;
}

float parametreC(Billard billard, float l, float L, float D, float F){ // A TESTER
    float C;
    float Y = billard.fsommet1.y/billard.fsommet1.x;
    C = -D*Y -F/billard.fsommet1.x;
    if (test_parametre(billard, C))
        C = 1;
    return C;
}


// VERIFIER LA POSITION DE CHACUN DES SOMMETS / QUI EST OU ?

fposition produitmatriciel2x2simple(fposition point, vector<float> coefficients){
    fposition sortie;
    sortie.x = coefficients[0]*point.x + coefficients[1]*point.y + coefficients[5];
    sortie.y = coefficients[3]*point.x + coefficients[4]*point.y + coefficients[6];
    return sortie;
}

vector<fposition> produitmatriciel2x2(vector<fposition> contours, vector<float> coefficients){
    vector<fposition> sortie;
    for (int i=0; i <= contours.size();i++)
        sortie.push_back(produitmatriciel2x2simple(contours[i],coefficients));
    return sortie;
}

vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4){
    vector<fposition> pvect;
    pvect.push_back(position1);
    pvect.push_back(position2);
    pvect.push_back(position3);
    pvect.push_back(position4);
    return pvect;
}

vector<float> float2vector(float A, float B, float C, float D, float E, float F){
    vector<float> sortie;
    sortie.push_back(A);
    sortie.push_back(B);
    sortie.push_back(C);
    sortie.push_back(D);
    sortie.push_back(E);
    sortie.push_back(F);
    return sortie;
}

// VERIFIER LA POSITION DE CHACUN DES SOMMETS / QUI EST OU ?
void conversionRepereBillard(Billard _billard){  // A FAIRE
        //matricedepassage(_billard.sommet1, _billard.sommet2);

}

void affichage_projection(vector<Point> cadre, Mat drawing){

    float l = 5.5;
    float L = 8.5;

    Point p1 = Point(0,0);
    Point p2 = Point(0,l);
    Point p3 = Point(L,l);
    Point p4 = Point(L,0);

    /// Image prévue
    line(drawing, p1, p2, Scalar(255,0,0),2,8,0);
    line(drawing, p2, p3, Scalar(255,0,0),2,8,0);
    line(drawing, p3, p4, Scalar(255,0,0),2,8,0);
    line(drawing, p4, p1, Scalar(255,0,0),2,8,0);

    /// Image prévue de l'image prévue (BLEUE)

    Point p11 = Point(118,153);
    Point p12 = Point(444,153);
    Point p13 = Point(444,390);
    Point p14 = Point(118,390);

    /// Image prévue (VERTE)
    /*line(drawing, p11, p12, Scalar(0,255,0),2,8,0);
    line(drawing, p12, p13, Scalar(0,255,0),2,8,0);
    line(drawing, p13, p14, Scalar(0,255,0),2,8,0);
    line(drawing, p14, p11, Scalar(0,255,0),2,8,0);*/

    /// Image prévue redimensionnée (BLEUE)
    p1.y = p1.y + 153;
    p1.x = p1.x + 118;
    p2.y = (p2.y)*47 + 153;
    p2.x = (p2.x) + 118;
    p3.y = (p3.y)*47 + 153;
    p3.x = (p3.x)*41 + 118;
    p4.y = (p4.y) + 153;
    p4.x = (p4.x)*41 + 118;

    line(drawing, p1, p2, Scalar(255,0,0),2,8,0);
    line(drawing, p2, p3, Scalar(255,0,0),2,8,0);
    line(drawing, p3, p4, Scalar(255,0,0),2,8,0);
    line(drawing, p4, p1, Scalar(255,0,0),2,8,0);

    /// Image captée
    cadre[1].y = cadre[1].y + 153;
    cadre[1].x = cadre[1].x + 118;
    cadre[2].y = (cadre[2].y)*47 + 153;
    cadre[2].x = (cadre[2].x) + 118;
    cadre[3].y = (cadre[3].y)*47 + 153;
    cadre[3].x = (cadre[3].x)*41 + 118;
    cadre[4].y = (cadre[4].y) + 153;
    cadre[4].x = (cadre[4].x)*41 + 118;

    line(drawing, cadre[1], cadre[2], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[2], cadre[3], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[3], cadre[4], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[4], cadre[1], Scalar(255,0,255),2,8,0);

    /// Show in a window
    namedWindow( "Projection", CV_WINDOW_AUTOSIZE );
    imshow( "Projection", drawing );

}


void changement_echelle(Point p1, Point p2, Point p3, Point p4){
    ///\todo trouver les vraies valeurs
    Mat drawing;
    p1.x = p1.x + 150;
    p1.y = p1.y + 110;
    p2.x = (p2.x)*36 + 150;
    p2.y = (p2.y) + 110;
    p3.x = (p3.x)*36 + 150;
    p3.y = (p3.y)*43 + 110;
    p4.x = (p4.x) + 150;
    p4.y = (p4.y)*43 + 110;

    line(drawing, p1, p2, Scalar(255,0,0),2,8,0);
    line(drawing, p2, p3, Scalar(255,0,0),2,8,0);
    line(drawing, p3, p4, Scalar(255,0,0),2,8,0);
    line(drawing, p4, p1, Scalar(255,0,0),2,8,0);

    namedWindow( "Projection", CV_WINDOW_AUTOSIZE );
    imshow("Projection", drawing);
}














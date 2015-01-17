/**
 * \file projection.cpp
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
#include <math.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "structures.h"
#include "conversion_format.h"

using namespace std;
using namespace cv;


///\todo corriger la matrice de passage
///\todo 1) tester les calculs matriciel
///\todo 2) corriger les formules des paramètres



/// MATRICE de passage à partir des positions à l'écran et des vraies valeurs de l et L
//   A B  x  +  E
//   C D  y  +  F

vector<double> matrice(Billard b, float L, float l){
    vector<double> sortie;
    /* PREMIERE PARTIE*/
    double Y = b.fsommet3.y / b.fsommet1.y;
    double W = b.fsommet2.x - Y*b.fsommet1.x;
    double K = b.fsommet2.y/b.fsommet1.y - 1;

    double Edenom = 1 + K/W*(b.fsommet3.x - b.fsommet1.x*Y) - Y;
    double E = l / Edenom;

    double B = E * K/W;

    double A = -(B*b.fsommet1.x-E)/b.fsommet1.y;

    /* DEUXIEME PARTIE */
    double X = b.fsommet2.y/b.fsommet1.y;
    double H = b.fsommet2.x - X * b.fsommet1.x;
    double Z = (X-1)/H;

    double Fdenom = (Z*b.fsommet3.y - b.fsommet3.y/b.fsommet1.y + Z *b.fsommet3.x + 1);
    double Fnum = (1 + (b.fsommet3.y - b.fsommet3.x)/H)*L;

    double F = Fnum/Fdenom;

    double D = (L + (X-1)*F)/H;

    double C = - D*b.fsommet1.x/b.fsommet1.y - F/b.fsommet1.y;

    sortie.push_back(A);
    sortie.push_back(B);
    sortie.push_back(C);
    sortie.push_back(D);
    sortie.push_back(E);
    sortie.push_back(F);

    return sortie;
}


/* VERSION 2
bool test_parametre(Billard billard, double E){
    bool probleme = false;
    if ((E != E) || (isinf(E))||(E==0)||(abs(E)>100000)||(abs(E)<0.0000001)){
        probleme = true;
    }
    return probleme;
}

double parametreE(Billard billard, double l, double L){
    double E;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    double W = Y*billard.fsommet3.y - billard.fsommet3.y;
    double X = billard.fsommet2.x - Y*billard.fsommet2.y;
    double Edenom = ((1-billard.sommet2.y/billard.fsommet1.y)*Y + (1-billard.fsommet3.y/billard.fsommet1.y)*W);
    E = l*(W+X) / Edenom;
    if (test_parametre(billard, E))
        E = 1;
    return E;
}

double parametreB(Billard billard, double l, double L, double E){ // A TESTER
    double B;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    double X = billard.fsommet2.x - Y*billard.fsommet2.y;
    B = (l-E*(1-billard.fsommet2.y/billard.fsommet1.y))/X;
    if (test_parametre(billard, B))
        B = 1;
    return B;
}

double parametreA(Billard billard, double l, double L, double B, double E){ // A TESTER
    double A;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    A = -B*Y -E/billard.fsommet1.y;
    if (test_parametre(billard, A))
        A = 1;
    return A;
}

double parametreF(Billard billard, double l, double L){
    double F;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    double W = Y*billard.fsommet3.y - billard.fsommet3.y;
    double X = billard.fsommet4.x - Y*billard.fsommet4.y;
    double Fdenom = ((1-billard.sommet4.y/billard.fsommet1.y)*Y + (1-billard.fsommet3.y/billard.fsommet1.y)*W);
    F = L*(W+X) / Fdenom;
    if (test_parametre(billard, F))
        F = 1;
    return F;
}

double parametreD(Billard billard, double l, double L, double F){ // A TESTER
    double D;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    double X = billard.fsommet4.x - Y*billard.fsommet4.y;
    D = (L-F*(1-billard.fsommet4.y/billard.fsommet1.y))/X;
    if (test_parametre(billard, D))
        D = 1;
    return D;
}

double parametreC(Billard billard, double l, double L, double D, double F){ // A TESTER
    double C;
    double Y = billard.fsommet1.x/billard.fsommet1.y;
    C = -D*Y -F/billard.fsommet1.y;
    if (test_parametre(billard, C))
        C = 1;
    return C;
} */

/* VERSION 1
double parametreE(Billard billard, double l, double L){
    double E;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    double W = Y*billard.fsommet3.x - billard.fsommet3.x;
    double X = billard.fsommet2.y - Y*billard.fsommet2.x;
    double Edenom = ((1-billard.sommet2.x/billard.fsommet1.x)*Y + (1-billard.fsommet3.x/billard.fsommet1.x)*W);
    E = L*(W+X) / Edenom;
    if (test_parametre(billard, E))
        E = 1;
    return E;
}

double parametreB(Billard billard, double l, double L, double E){ // A TESTER
    double B;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    double X = billard.fsommet2.y - Y*billard.fsommet2.x;
    B = (L-E*(1-billard.fsommet2.x/billard.fsommet1.x))/X;
    if (test_parametre(billard, B))
        B = 1;
    return B;
}

double parametreA(Billard billard, double l, double L, double B, double E){ // A TESTER
    double A;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    A = -B*Y -E/billard.fsommet1.x;
    if (test_parametre(billard, A))
        A = 1;
    return A;
}

double parametreF(Billard billard, double l, double L){
    double F;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    double W = Y*billard.fsommet3.x - billard.fsommet3.x;
    double X = billard.fsommet4.y - Y*billard.fsommet4.x;
    double Fdenom = ((1-billard.sommet4.x/billard.fsommet1.x)*Y + (1-billard.fsommet3.x/billard.fsommet1.x)*W);
    F = l*(W+X) / Fdenom;
    if (test_parametre(billard, F))
        F = 1;
    return F;
}

double parametreD(Billard billard, double l, double L, double F){ // A TESTER
    double D;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    double X = billard.fsommet4.y - Y*billard.fsommet4.x;
    D = (l-F*(1-billard.fsommet4.x/billard.fsommet1.x))/X;
    if (test_parametre(billard, D))
        D = 1;
    return D;
}

double parametreC(Billard billard, double l, double L, double D, double F){ // A TESTER
    double C;
    double Y = billard.fsommet1.y/billard.fsommet1.x;
    C = -D*Y -F/billard.fsommet1.x;
    if (test_parametre(billard, C))
        C = 1;
    return C;
}
*/

/// PRODUIT MATRICIEL

fposition produitmatriciel2x2simple(fposition point, vector<double> coefficients){
    fposition sortie;
    sortie.x = coefficients[3]*point.x + coefficients[2]*point.y + coefficients[5];
    sortie.y = coefficients[1]*point.x + coefficients[0]*point.y + coefficients[4];
    return sortie;
}
/*
fposition produitmatriciel2x2simple(fposition point, vector<double> coefficients){
    fposition sortie;
    sortie.x = coefficients[0]*point.x + coefficients[1]*point.y + coefficients[4];
    sortie.y = coefficients[2]*point.x + coefficients[3]*point.y + coefficients[5];
    return sortie;
}*/

vector<fposition> produitmatriciel2x2(vector<fposition> contours, vector<double> coefficients){
    vector<fposition> sortie;
    for (int i=0; i <= contours.size();i++)
        sortie.push_back(produitmatriciel2x2simple(contours[i],coefficients));
    return sortie;
}


/// CONVERSION DES FORMATS

vector<fposition> fposition2vector(fposition position1,fposition position2,fposition position3,fposition position4){
    vector<fposition> pvect;
    pvect.push_back(position1);
    pvect.push_back(position2);
    pvect.push_back(position3);
    pvect.push_back(position4);
    return pvect;
}

vector<double> double2vector(double A, double B, double C, double D, double E, double F){
    vector<double> sortie;
    sortie.push_back(A);
    sortie.push_back(B);
    sortie.push_back(C);
    sortie.push_back(D);
    sortie.push_back(E);
    sortie.push_back(F);
    return sortie;
}


void affichage_projection(vector<Point> cadre, Mat drawing){

    double L = 326;
    double l = 237;
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
    /*p1.y = p1.y + 153;
    p1.x = p1.x + 118;
    p2.y = (p2.y)*47 + 153;
    p2.x = (p2.x) + 118;
    p3.y = (p3.y)*47 + 153;
    p3.x = (p3.x)*41 + 118;
    p4.y = (p4.y) + 153;
    p4.x = (p4.x)*41 + 118;*/

    line(drawing, p11, p12, Scalar(255,0,0),2,8,0);
    line(drawing, p12, p13, Scalar(255,0,0),2,8,0);
    line(drawing, p13, p14, Scalar(255,0,0),2,8,0);
    line(drawing, p14, p11, Scalar(255,0,0),2,8,0);

    /// Image captée
    /*cadre[0].y = cadre[0].y + 153;
    cadre[0].x = cadre[0].x + 118;
    cadre[1].y = (cadre[1].y) + 153;
    cadre[1].x = (cadre[1].x) + 118;
    cadre[2].y = (cadre[2].y) + 153;
    cadre[2].x = (cadre[2].x) + 118;
    cadre[3].y = (cadre[3].y) + 153;
    cadre[3].x = (cadre[3].x) + 118;*/

    line(drawing, cadre[0], cadre[1], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[1], cadre[2], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[2], cadre[3], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[3], cadre[0], Scalar(255,0,255),2,8,0);

    /*cadre[0].y = cadre[0].y + 153;
    cadre[0].x = cadre[0].x + 118;
    cadre[1].y = (cadre[1].y)*5 + 153;
    cadre[1].x = (cadre[1].x) + 118;
    cadre[2].y = (cadre[2].y)*5 + 153;
    cadre[2].x = (cadre[2].x)*5 + 118;
    cadre[3].y = (cadre[3].y) + 153;
    cadre[3].x = (cadre[3].x)*5 + 118;

    line(drawing, cadre[0], cadre[1], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[1], cadre[2], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[2], cadre[3], Scalar(255,0,255),2,8,0);
    line(drawing, cadre[3], cadre[0], Scalar(255,0,255),2,8,0);*/


    /// Show in a window
    namedWindow( "Projection", CV_WINDOW_AUTOSIZE );
    imshow( "Projection", drawing );

}


void projection(Billard billard, Mat imgFlip){

    cout << "Billard: "
         << "(" << billard.fsommet1.x << ";" << billard.fsommet1.y <<")"
         << "(" << billard.fsommet2.x << ";" << billard.fsommet2.y <<")"
         << "(" << billard.fsommet3.x << ";" << billard.fsommet3.y <<")"
         << "(" << billard.fsommet4.x << ";" << billard.fsommet4.y <<")"<<endl;

    //affichage_projection_test(imgFlip);

        /* UTILISATION DE LA PROJECTION */
        double l = 237;
        double L = 326;
        /*
        double E = parametreE(billard, l, L);
        double B = parametreB(billard, l, L, E);
        double A = parametreA(billard, l, L, E, B);
        double F = parametreF(billard, l, L);
        double D = parametreD(billard, l, L, F);
        double C = parametreC(billard, l, L, F, D);
        vector<double> coefficients = double2vector(A,B,C,D,E,F) ;
        */
        vector<double> coefficients = matrice(billard, L, l);
        cout << "A " << coefficients[0] << " B " << coefficients[1] << " C " << coefficients[2] <<" D "<< coefficients[3] << " E " << coefficients[4] << " F " << coefficients[5] << endl;
        //cout << "A :" << A << " B :" << B << " C :" << C << " D: " << D <<" E "<< E << " F " << F << endl;
        vector<fposition> fcontours = fposition2vector(billard.fsommet1, billard.fsommet2, billard.fsommet3, billard.fsommet4);
        vector<fposition> nouveaucadre = produitmatriciel2x2(fcontours, coefficients);
        vector<Point> _nouveaucadre = vecfposition2vecpoint(nouveaucadre);
        cout << _nouveaucadre[0] << " / " << _nouveaucadre[1] <<" / "<< _nouveaucadre[2] << " / " << _nouveaucadre[3] << endl;
        affichage_projection(_nouveaucadre, imgFlip);

}


void changement_echelle(Point p1, Point p2, Point p3, Point p4){ // pas utilisé
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














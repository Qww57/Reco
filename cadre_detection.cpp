/**
 * \file cadre_detetcion.cpp
 * \brief programme de detection du billard
 * \author Quentin.T
 * \version 0.1
 * \date 13 janvier 2015
 *
 * Partie dédiée à la reconnaissance du billard
 * lors de l'initialisation du projet
 *
 */

#include <vector>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"
#include "distance.h"
#include "conversion_format.h"
#include "cadre_detection.h"

using namespace cv;
using namespace std;


int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
double fontScale = 1;


///IDEES
// on les valeurs des mesures des cotés par rapport à ce que ça devrait être
// on calcule peut être même les valeurs des angles
// on obtient la conversion des bords du billard dans (x,y)


void cadreDetection_callback(Mat img, vector<Point> &anglesBillard){ //INUTILE

// se fait une fois au démarrage, dans le but de trouver la position du billard.
// vérifier que le résultat est satisfaisant et valider avant le début de la partie

// on note la position de chacun des coins => vector ?
// on mesure chacun d'un coté

    // Concersion du gris en image binaire
    Mat imgG;
    cvtColor( img, imgG, CV_BGR2GRAY );
    Mat imgB;
    Canny(imgG, imgB, 0, 50, 5 );

    // Find contours
    vector<vector<cv::Point> > contours;
    findContours(imgB, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // The array for storing the approximation curve
    vector<Point> approx;

    // We'll put the labels in this destination image
    Mat dst = img;

    // écriture sur les images
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 1;

    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02,true);

        // Skip small or non-convex objects
        if (fabs(cv::contourArea(contours[i])) < 300 || !isContourConvex(approx))
            continue;

        if (approx.size() == 3)
            continue;

        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();
            if (approx.size() == 4){
                line(dst, approx[0], approx[1], Scalar::all(255), 1, 8, 0);
                line(dst, approx[1], approx[2], Scalar::all(255), 1, 8, 0);
                line(dst, approx[2], approx[3], Scalar::all(255), 1, 8, 0);
                line(dst, approx[3], approx[0], Scalar::all(255), 1, 8, 0);
            // FAIRE AFFICHAGE SUR LE TRUC
                //string s0;
                //putText(dst, s0, approx[0], fontFace, fontScale,Scalar::all(255),1,0);
                cout << "Approx : " << approx[0] << approx[1] << approx[2] << approx[3] << endl;
                anglesBillard = approx;
            }
            else
                continue;
        }

        else
            continue;

    } // end of for() loop
    namedWindow( "Billard", CV_WINDOW_AUTOSIZE );
    imshow("Billard", dst);

};

vector<Point> cadreDetection_callback(Mat img){//INUTILE

    vector<Point> cadre;

    // Concersion du gris en image binaire
    Mat imgG;
    cvtColor( img, imgG, CV_BGR2GRAY );
    Mat imgB;
    Canny(imgG, imgB, 0, 50, 5 );

    // Find contours
    vector<vector<cv::Point> > contours;
    findContours(imgB, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // The array for storing the approximation curve
    vector<Point> approx;

    // We'll put the labels in this destination image
    Mat dst = img;

    // écriture sur les images
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 1;

    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02,true);

        // Skip small or non-convex objects
        if (fabs(cv::contourArea(contours[i])) < 300 || !isContourConvex(approx))
            continue;

        if (approx.size() == 3)
            continue;

        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();
            if (approx.size() == 4){
                line(dst, approx[0], approx[1], Scalar::all(255), 1, 8, 0);
                line(dst, approx[1], approx[2], Scalar::all(255), 1, 8, 0);
                line(dst, approx[2], approx[3], Scalar::all(255), 1, 8, 0);
                line(dst, approx[3], approx[0], Scalar::all(255), 1, 8, 0);
            // FAIRE AFFICHAGE
                //string s0;
                //putText(dst, s0, approx[0], fontFace, fontScale,Scalar::all(255),1,0);
                cout << "Approx : " << approx[0] << approx[1] << approx[2] << approx[3] << endl;
                cadre = approx;
            }
            else
                continue;
        }

        else
            continue;

    } // end of for() loop
    namedWindow( "Billard", CV_WINDOW_AUTOSIZE );
    imshow("Billard", dst);

    return cadre;
};

Billard cadreDetection2_callback(Mat img){ // voir si on repasse pas ça en void et on met le billard en entrée aussi

    if (!parametrageCadreDone()){ // si le paramétrage n'est pas fait bool = "false", on le fait

        vector<Point> cadre;
        Billard _billard;

        // Concersion du gris en image binaire
        Mat imgG;
        cvtColor( img, imgG, CV_BGR2GRAY );
        Mat imgB;
        Canny(imgG, imgB, 0, 50, 5 );

        // Find contours
        vector<vector<cv::Point> > contours;
        findContours(imgB, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        // The array for storing the approximation curve
        vector<Point> approx;

        // We'll put the labels in this destination image
        Mat dst = img;

        // écriture sur les images
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1;

        for (int i = 0; i < contours.size(); i++)
        {
            // Approximate contour with accuracy proportional to the contour perimeter
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02,true);

            // Skip small or non-convex objects
            if (fabs(cv::contourArea(contours[i])) < 300 || !isContourConvex(approx))
                continue;

            else if (approx.size() >= 4 && approx.size() <= 6)
            {
                // Number of vertices of polygonal curve
                int vtc = approx.size();
                if (approx.size() == 4){
                    if (perimetrePoints(approx) > 400){

                        // REPOSITIONNEMENT
                        repositionnement(approx, dst, false);

                        //AFFICHAGE DES LIGNES
                        line(dst, approx[0], approx[1], Scalar::all(255), 2, 8, 0);
                        line(dst, approx[1], approx[2], Scalar::all(255), 2, 8, 0);
                        line(dst, approx[2], approx[3], Scalar::all(255), 2, 8, 0);
                        line(dst, approx[3], approx[0], Scalar::all(255), 2, 8, 0);

                        // AFFICHAGE DES POSITIONS
                        /*string s0 = point2string(approx[0]);
                        putText(dst, s0, approx[0], fontFace, fontScale,Scalar::all(255),1,0);
                        string s1 = point2string(approx[1]);
                        putText(dst, s1, approx[1], fontFace, fontScale,Scalar::all(255),1,0);
                        string s2 = point2string(approx[2]);
                        putText(dst, s2, approx[2], fontFace, fontScale,Scalar::all(255),1,0);
                        string s3 = point2string(approx[3]);
                        putText(dst, s3, approx[3], fontFace, fontScale,Scalar::all(255),1,0);*/

                        // AFFICHAGE DU NUMERO DE L'ANGLE
                        string s0 = "0";
                        putText(dst, s0, approx[0], fontFace, fontScale,Scalar::all(255),1,0);
                        string s1 = "1";
                        putText(dst, s1, approx[1], fontFace, fontScale,Scalar::all(255),1,0);
                        string s2 = "2";
                        putText(dst, s2, approx[2], fontFace, fontScale,Scalar::all(255),1,0);
                        string s3 = "3";
                        putText(dst, s3, approx[3], fontFace, fontScale,Scalar::all(255),1,0);

                        // CALCUL DES LONGUEURS
                        int l1, l2, l3, l4;
                        l1 = distancePoints(approx[0],approx[1]);
                        l2 = distancePoints(approx[1],approx[2]);
                        l3 = distancePoints(approx[2],approx[3]);
                        l4 = distancePoints(approx[3],approx[0]);

                        // AFFICHAGE DES LONGUEURS
                        Point mil1, mil2, mil3, mil4;
                        mil1 = milieuPoints(approx[0],approx[1]);
                        mil2 = milieuPoints(approx[1],approx[2]);
                        mil3 = milieuPoints(approx[2],approx[3]);
                        mil4 = milieuPoints(approx[3],approx[0]);

                        string ss0 = int2string(l1);
                        putText(dst, ss0, mil1, fontFace, fontScale,Scalar::all(255),1,0);
                        string ss1 = int2string(l2);
                        putText(dst, ss1, mil2, fontFace, fontScale,Scalar::all(255),1,0);
                        string ss2 = int2string(l3);
                        putText(dst, ss2, mil3, fontFace, fontScale,Scalar::all(255),1,0);
                        string ss3 = int2string(l4);
                        putText(dst, ss3, mil4, fontFace, fontScale,Scalar::all(255),1,0);


                        // ENREGISTREMENT DES DONNEES DANS LE BILLARD
                        _billard.fsommet1=point2fposition(approx[0]);
                        _billard.fsommet2=point2fposition(approx[1]);
                        _billard.fsommet3=point2fposition(approx[2]);
                        _billard.fsommet4=point2fposition(approx[3]);
                                //faire suite
                    }
                    else
                        cout << "Quadrilatère detecté mais non affiché" << endl;
                }
                else
                    continue;
            }
            else
                continue;

        } // end of for() loop
        namedWindow( "Billard", CV_WINDOW_AUTOSIZE );
        imshow("Billard", dst);

        return _billard;
    }
}

bool parametrageCadreDone(){ // TO DO
    // déterminer quand on a paramétré le truc
    bool param = false;
    return param;
}






/// FONCTIONS D'AIDE

int distancePoints(Point point1, Point point2){
    int distance;
    distance = floor(sqrt(abs((point2.x-point1.x)*(point2.x-point1.x)+(point2.y-point1.y)*(point2.y-point1.y))));
    return distance;
}

Point milieuPoints(Point point1, Point point2){
    Point milieu;
    milieu.x = (point1.x + point2.x)/2;
    milieu.y = (point1.y + point2.y)/2;
    return milieu;
}

int perimetrePoints(vector<Point> contours){
    if (contours.size() == 4){
        int perimetre;
        perimetre =   distancePoints(contours[0],contours[1])
                    + distancePoints(contours[1],contours[2])
                    + distancePoints(contours[2],contours[3])
                    + distancePoints(contours[3],contours[0]);
        return perimetre;
    }
    else return 0;
}


void repositionnement(vector<Point> &approx, Mat dst, bool aff){

    vector<Point> copie = approx;
    int indiceBD = -1;
    int indiceHG = -1;

    int minDistance = 1500;
    int maxDistance = 0;

    if (aff){

        // HAUT A GAUCHE ET BAS DROITE
        for (int i=0; i < approx.size(); i++){
            int d = distancePoints(approx[i], Point(0,0));
            string sss = int2string(d);
            Point mil = milieuPoints(Point(0,0),approx[i]);
            putText(dst, sss, mil, fontFace, fontScale,Scalar::all(255),1,0);
            line(dst, Point(1,1), approx[i], Scalar::all(255), 2, 8, 0);
            if (d <= minDistance){
                minDistance = d;
                indiceHG = i;
            }
            if (d >= maxDistance){
                maxDistance = d;
                indiceBD = i;
            }
        }

        // BAS A GAUCHE ET HAUT A DROITE
        int indiceBG = ((indiceHG+indiceBD)/2)%4;
        int indiceHD = (indiceBG+2)%4;

        string s2s = "B";
        putText(dst, s2s, approx[indiceHD], fontFace, fontScale,Scalar::all(255),1,0);
        string s3s = "D";
        putText(dst, s3s, approx[indiceBG], fontFace, fontScale,Scalar::all(255),1,0);
        string s0s = "A";
        putText(dst, s0s, approx[indiceHG], fontFace, fontScale,Scalar::all(255),1,0);
        string s1s = "C";
        putText(dst, s1s, approx[indiceBD], fontFace, fontScale,Scalar::all(255),1,0);

        approx[0] = copie[indiceHG];
        approx[1] = copie[indiceHD];
        approx[2] = copie[indiceBD];
        approx[3] = copie[indiceBG];


    }
    else {
        // HAUT A GAUCHE ET BAS DROITE
        for (int i=0; i < approx.size(); i++){
            int d = distancePoints(approx[i], Point(0,0));
            if (d <= minDistance){
                minDistance = d;
                indiceHG = i;
            }
            if (d >= maxDistance){
                maxDistance = d;
                indiceBD = i;
            }
        }

        // BAS A GAUCHE ET HAUT A DROITE

        int indiceBG = ((indiceHG+indiceBD)/2)%4;
        int indiceHD = (indiceBG+2)%4;

        approx[0] = copie[indiceHG];
        approx[1] = copie[indiceHD];
        approx[2] = copie[indiceBD];
        approx[3] = copie[indiceBG];

    }


}
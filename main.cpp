/**
 * \file main.cpp
 * \brief Programme principal
 * \author Quentin.T
 * \version 0.1
 * \date 10 janvier 2015
 *
 * Programme principal de reconnaissance du billard et de ses boules
 *
 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "gtest/gtest.h"

#include "structures.h"
#include "cadre_detection.h"
#include "boules_detection.h"
#include "projection.h"
#include "conversion_format.h"

using namespace cv;
using namespace std;


/**
*
* \todo
// - faire la projection: DONE
// - faire les tests unitaire de la projection
// - faire la fonction de calcul de la position simplifiée
// - faire le parametrage de la detection : DONE : A TESTER
// - faire la détection de la canne
// - refaire la fonction de calcul de la distance non simplifiée (plus tard)
// - refaire la fonction de calcul de la position non simplifiée (plus tard)
// - faire le calibrage des couleurs (plus tard)
// - déttecter les boules mêmes à moitié occultées (bonus)
*
*/


/// MAIN

int main( int argc, char** argv){

    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    vector<Point> anglesBillard;
    Billard billard;
    billard.fsommet1.x = 0; billard.fsommet1.y = 0;
    billard.fsommet2.x = 0; billard.fsommet2.y = 0;
    billard.fsommet3.x = 0; billard.fsommet3.y = 0;
    billard.fsommet4.x = 0; billard.fsommet4.y = 0;


    vector<vector<Point> > historiquedespositions;


    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        /// Flip image, convert image to gray and blur it
        Mat imgFlip;
        flip(imgOriginal,imgFlip,1);

        Mat imgGray;
        cvtColor( imgFlip, imgGray, CV_BGR2GRAY );
        blur( imgFlip, imgGray, Size(3,3) );

        /// Create Windows and Trackbars
        //imshow("Original", imgFlip);
        //contours_callback( 0, 0, imgGray);
        //color_callback( 0, 0, imgFlip);
        //bouleDetection_callback(0,0,imgFlip);
        //contours_createtrackbar();
        //color_createtrackbar();
        //bouleDetection_createtrackbar();

        billard = cadreDetection2_callback(imgFlip, historiquedespositions);
        //affichage_projection_test(imgFlip);

        /* UTILISATION DE LA PROJECTION */
        float l = 5.5;
        float L = 8.5;
        float E = parametreE(billard, l, L);
        float B = parametreB(billard, l, L, E);
        float A = parametreA(billard, l, L, E, B);
        float F = parametreF(billard, l, L);
        float D = parametreD(billard, l, L, F);
        float C = parametreC(billard, l, L, F, D);
        vector<float> coefficients = float2vector(A,B,C,D,E,F) ;

        cout << "A :" << A << " B :" << B << " C :" << C << " D: " << D <<" E "<< E << " F " << F << endl;
        vector<fposition> fcontours = fposition2vector(billard.fsommet1, billard.fsommet2, billard.fsommet3, billard.fsommet4);
        vector<fposition> nouveaucadre = produitmatriciel2x2(fcontours, coefficients);
        vector<Point> _nouveaucadre = vecfposition2vecpoint(nouveaucadre);
        affichage_projection(_nouveaucadre, imgFlip);



        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }
    return(0);
}











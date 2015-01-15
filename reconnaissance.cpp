/**
 * \file reconnaissance.cpp
 * \brief programmes de detection avec openCV
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée au test des différentes fonctions d'openCV
 * Ne sera pas forcement utilisé au final dans le projet
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"
#include "reconnaissance.h"

using namespace cv;
using namespace std;


/// PARAMETRES

int thresh = 100;
int max_thresh = 255;

colorCalibrage calibrage;


/// TEST DES FONCTIONS DE RECONNAISSANCE

void contours_callback(Mat img){ // INUTILE
    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( img, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        Scalar color = Scalar(255,255,255);
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }

    /// Show in a window
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}

void color_callback(Mat img){ // INUTILE
    Mat imgHSV;

    cvtColor(img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;

    inRange(imgHSV, Scalar(calibrage.iLowH, calibrage.iLowS, calibrage.iLowV),
                    Scalar(calibrage.iHighH, calibrage.iHighS, calibrage.iHighV), imgThresholded); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //morphological closing (fill small holes in the foreground)
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    imshow("Thresholded Image", imgThresholded); //show the thresholded image
}




/// CREATION DES TRACKBARS

void contours_createtrackbar(){ // INUTILE
    //cvCreateTrackbar("LowH", "Control", &calibrage.iLowH, 179);
    createTrackbar( " Canny thresh:", "Contours", &thresh, max_thresh); // cvCreateTrackbar
}

void color_createtrackbar(){ // INUTILE

    //Create trackbars in "Thresholded Image" window
    createTrackbar("LowH", "Thresholded Image", &calibrage.iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Thresholded Image", &calibrage.iHighH, 179);

    createTrackbar("LowS", "Thresholded Image", &calibrage.iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Thresholded Image", &calibrage.iHighS, 255);

    createTrackbar("LowV", "Thresholded Image", &calibrage.iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Thresholded Image", &calibrage.iHighV, 255);
}



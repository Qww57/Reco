/**
 * \file boules_detection.cpp
 * \brief programme de detection des boules
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie dédiée à la reconnaissance des boules de billard
 *
 */

#include <string>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "structures.h"
#include "distance.h"
#include "conversion_format.h"

using namespace cv;
using namespace std;

int sigmaX = 2;
int sigmaY = 2;
int minRayon = 30;
int maxRayon = 90;

void bouleDetection_callback(int, void*, Mat img){

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

    /* ALTERNATIVE 1 */

    GaussianBlur( imgG, imgG, Size(9, 9), sigmaX, sigmaY );
    vector<Vec3f> circles;
    HoughCircles(imgG, circles, CV_HOUGH_GRADIENT,2, imgG.rows/4, 200, 100 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        if (radius < maxRayon || radius < minRayon) { // enlever les grands cercles qui sont des erreurs en général
            // draw the circle center
            circle( dst, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // draw the circle outline
            circle( dst, center, radius, Scalar(0,0,255), 1, 8, 0 );
            // give further informations
            string s = int2string(radius);
            putText(dst, s, center, fontFace, fontScale, Scalar::all(255), 1,8);
            string s1 = "Nombre cercles : "+ int2string(circles.size());
            Point _point;
            _point.x =100;
            _point.y = 100;
            putText(dst,s1, _point, fontFace, fontScale, Scalar::all(255),1,0 );
            if (radius != 0) {
                int distance = calculDistanceSimplifie(radius);
                string s2 = "Distance : " +int2string(distance)+ "cm";
                Point _point1; _point1.x =center.x; _point1.y = center.y-50;
                putText(dst,s2, _point1, fontFace, fontScale, Scalar::all(255),1,0);
            }
        }
    }
    /* ALTERNATIVE 2 */
    /*
    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true) * 0.02,true);

        // Skip small or non-convex objects
        if (fabs(cv::contourArea(contours[i])) < 100 || !isContourConvex(approx))
            continue;

        if (approx.size() == 3)
            continue;

        else if (approx.size() >= 4 && approx.size() <= 6)
            continue;

        else
        {
          // Detect and label circles
            double area = contourArea(contours[i]);
            Rect r = boundingRect(contours[i]);
            int radius = r.width / 2;
            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 && std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2){
                putText(dst, "Cercle", contours[i][0],fontFace, fontScale, Scalar::all(255), thickness,8);
                Scalar color = Scalar(255,255,255);
                int milieu = floor(contours[i].size()/2)+1; // trace le rayon
                line(dst,contours[i][0], contours[i][milieu], Scalar::all(255));
                //circle(dst, ??centre??, radius, color, 1, 8,0)
            }
    } // end of for() loop
    */
    namedWindow( "Boules", CV_WINDOW_AUTOSIZE );
    imshow("Boules", dst);
}


void bouleDetection_createtrackbar(){

    //Create trackbars in "Formes" window
    createTrackbar("Sigma X", "Boules", &sigmaX, 10);
    createTrackbar("Sigma Y", "Boules", &sigmaY, 10);
    createTrackbar("Rayon min", "Boules", &minRayon, 150);
    createTrackbar("Rayon max", "Boules", &maxRayon, 150);

}


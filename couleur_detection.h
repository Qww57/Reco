#ifndef COULEUR_DETECTION_H
#define COULEUR_DETECTION_H


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.h"

#include "structures.h"
#include "parametrage.h"

using namespace std;
using namespace cv;

CvPoint binarisation(IplImage *image, int *nbPixels, colorCalibrage *calibrage);

#endif //BOULE_DETECTION_H

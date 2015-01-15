/**
 * \file conversion_format.cpp
 * \brief programmes de conversion des types
 * \author Quentin.T
 * \version 0.1
 * \date 13 janvier 2015
 *
 * Partie dédiée aux différentes fonctions de conversions
 * des types de données utilisés par le reste des programmes
 *
 */

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "conversion_format.h"
#include "structures.h"

using namespace std;
using namespace cv;

string int2string(int a){
    string s;
    ostringstream convert;
    convert << a;
    s = convert.str();
    return s;
}

string point2string(Point point){
    string s;
    int a = point.x;
    int b = point.y;
    string sa = int2string(a);
    string sb = int2string(b);
    ostringstream convert;
    convert << " (" << sa << ";"<< sb<< ") ";
    s = convert.str();
    return s;
}

position point2position(Point point){
    position _position;
    _position.x = point.x;
    _position.y = point.y;
    return _position;
}

fposition point2fposition(Point point){
    fposition _position;
    _position.x = (float) point.x;
    _position.y = (float) point.y;
    return _position;
}

Point fposition2point(fposition fpos){
    Point _point;
    _point.x = (int) fpos.x;
    _point.y = (int) fpos.y;
    return _point;
}

vector<Point> vecfposition2vecpoint(vector<fposition> entree){
    vector<Point> sortie;
    for (int i = 0; i< entree.size(); i++)
        sortie.push_back(fposition2point(entree[i]));
    return sortie;
}


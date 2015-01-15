
// int perimetrePoints(std::vector<cv::Point> contours);
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "cadre_detection.h"
#include "structures.h"

#include "gtest/gtest.h"


using namespace std;
using namespace cv;


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/// PROJECTION



/// CADRE DETECTION

TEST(perimetrePoints, carre)
{
    vector<Point> contours;
    Point p1 = Point(0,0);
    Point p2 = Point(0,1);
    Point p3 = Point(1,1);
    Point p4 = Point(1,0);
    contours.push_back(p1);
    contours.push_back(p2);
    contours.push_back(p3);
    contours.push_back(p4);

    ASSERT_EQ(4, perimetrePoints(contours));
}



TEST(milieuPoints, points_tous_pairs_ou_impairs)
{
    Point p1 = Point(0,0);
    Point p2 = Point(20,10);
    Point p3 = Point(10,5);

    Point p4 = Point(0,0);
    Point p5 = Point(10,4);
    Point p6 = Point(5,2);

    EXPECT_EQ(p3, milieuPoints(p1,p2));
    EXPECT_EQ(p6, milieuPoints(p3,p4));
}

TEST(milieuPoints, points_pairs_et_impairs)
{
    Point p1 = Point(0,0);
    Point p2 = Point(21,11);
    Point p3 = Point(10,5);

    Point p4 = Point(0,0);
    Point p5 = Point(11,5);
    Point p6 = Point(5,2);

    EXPECT_EQ(p3, milieuPoints(p1,p2));
    EXPECT_EQ(p6, milieuPoints(p3,p4));
}

TEST(distancePoints, distance_normale ){
    Point p1 = Point(0,0);
    Point p2 = Point(10,0);
    int d1 = 10;

    Point p3 = Point(10,10);
    Point p4 = Point(10,30);
    int d2 = 20;

    EXPECT_EQ(d1, distancePoints(p1,p2));
    EXPECT_EQ(d2, distancePoints(p3,p4));
}


TEST(distancePoints, distance_arrondie ){
    Point p1 = Point(5,5);
    Point p2 = Point(0,0);
    int d1 = 7;

    EXPECT_EQ(d1, distancePoints(p1,p2));
}

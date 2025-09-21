#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
    Mat img = imread("../resources/test_image_2.png");
    Mat gray, binary;
cvtColor(img, gray, COLOR_BGR2GRAY);
threshold(gray, binary, 250, 255, THRESH_BINARY);
Mat hsv;
  cvtColor(img, hsv, COLOR_BGR2HSV);
  Mat mask;
  inRange(hsv, Scalar(100,50,50), Scalar(140, 255, 255), mask);
    Mat resultImage1 = img.clone();
    Mat edges;
Canny(gray, edges, 250, 255);
    Mat morph;
Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
morphologyEx(edges, morph, MORPH_CLOSE, kernel);
    vector<vector<Point>> contours;
vector<Vec4i> hierarchy;
findContours(morph, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
Mat contourImg = Mat::zeros(img.size(), CV_8UC3);
for (size_t i = 0; i < contours.size(); i++) {
drawContours(contourImg, contours, (int)i, Scalar(0, 255, 0), 2);
}
for (size_t i = 0; i < contours.size(); i++) {
double area = contourArea(contours[i]);
if (area < 96|| (area > 97&& area < 1200) || area > 1400) {continue ;}
Rect bbox = boundingRect(contours[i]);
rectangle(img, bbox, Scalar(0, 0, 255), 2);
}
imshow("aa", img);
  waitKey(0);
  imwrite("../image/result.jpg",img);
return 0;
}
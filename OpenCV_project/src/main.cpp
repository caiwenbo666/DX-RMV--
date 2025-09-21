#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
  Mat img = imread("../resources/test_image.png");
  if (img.empty()) 
  {
    std::cout << "无法读取图像!" << std::endl;
    return -1;
  }
  imwrite("../image/01_original_image.jpg",img);
  Mat gray;
  cvtColor(img, gray, COLOR_BGR2GRAY);
  imwrite("../image/02_grayscale_image.jpg",gray);
  Mat hsv;
  cvtColor(img, hsv, COLOR_BGR2HSV);
  imwrite("../image/03_hsv_image.jpg",hsv);
  Mat blurImg;
  blur(img, blurImg, Size(5, 5));
  imwrite("../image/04_blur_image.jpg",blurImg);
  Mat gaussianImg;
  GaussianBlur(img, gaussianImg, Size(5, 5), 1.5);
  imwrite("../image/05_gaussian_blur_image.jpg",gaussianImg);
  Mat mask;
  inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask);
  imwrite("../image/06_red_mask.jpg",mask);
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  Mat resultImage = img.clone();
  Mat resultImage1 = img.clone();
  for (size_t i = 0; i < contours.size(); i++) 
  {
    drawContours(resultImage, contours, i, Scalar(0, 255, 0), 2); 
  }
  imwrite("../image/07_red_counters.jpg",resultImage);
  for (size_t i = 0; i < contours.size(); i++) 
  {
     Rect boundingBox = boundingRect(contours[i]);
     rectangle(resultImage1, boundingBox, Scalar(255, 0, 0), 2); 
  }
  imwrite("../image/08_red_bounding_boxes.jpg",resultImage1);
  Mat adaptive;
  adaptiveThreshold(gray, adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY, 11, 2);
  imwrite("../image/09_brinary_image.jpg",adaptive);
  Mat dilateImg, erodeImg, morphImg;
  Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
  dilate(adaptive, dilateImg, kernel);
  imwrite("../image/10_dilated_image.jpg",dilateImg);
  erode(adaptive, erodeImg, kernel);
  imwrite("../image/11_eroded_image.jpg",erodeImg);  
  Mat colorImage;
  cvtColor(erodeImg, colorImage, COLOR_GRAY2BGR);
  findContours(erodeImg, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
     for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        
        Rect bbox = boundingRect(contours[i]);
        Point seedPoint(bbox.x + bbox.width / 2, bbox.y + bbox.height / 2);
        
        Scalar color(rand() % 256, rand() % 256, rand() % 256);
        floodFill(colorImage, seedPoint, color, 0, Scalar(5, 5, 5), Scalar(5, 5, 5), 8);
    }
    
    imwrite("../image/12_flood_fill.jpg", colorImage);
  Mat shapeImage = Mat::zeros(300, 300, CV_8UC1);
    rectangle(shapeImage, Point(50, 50), Point(250, 250), Scalar(255), -1);
    putText(shapeImage, "Visual studio", Point(150, 200), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 0), 2);
    imwrite("../image/13_shapes_text.jpg", shapeImage);
    findContours(shapeImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    Mat contourImage = Mat::zeros(shapeImage.size(), CV_8UC3);
    drawContours(contourImage, contours, -1, Scalar(0, 0, 255), 2);
    imwrite("../image/14_drawn_red_counters.jpg", contourImage);
    Mat contourImage1= Mat::zeros(shapeImage.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        Rect bbox = boundingRect(contours[i]);
        rectangle(contourImage1, bbox, Scalar(0, 0, 255), 2);
    }
    imwrite("../image/15_drawn_red_bounding_boxes.jpg", contourImage1);
    Point2f center(img.cols / 2.0f, img.rows / 2.0f);
    Mat rotationMatrix = getRotationMatrix2D(center, 35, 1.0);
    Mat rotatedImage;
    warpAffine(img, rotatedImage, rotationMatrix, img.size());
    imwrite("../image/16_rotated_35_degrees.jpg", rotatedImage);
    int cropWidth = img.cols / 2;
    int cropHeight = img.rows / 2;
    Rect cropRegion(0, 0, cropWidth, cropHeight);
    Mat croppedImage = img(cropRegion);
     imwrite("../image/17_cropped_quarter.jpg", croppedImage);
  return 0;
}

// Image Processing with OpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//the iostream to use like cout
#include <iostream>
//the core.hpp declares the image data structure.
#include <opencv2/core.hpp>
/*the highgui.hpp header file that contains all the graphical interface functions that 
  allow you to easily visualize and interact with your images. like(imshow(),imread(), ... ),
  and can react to mouse or key events */
#include <opencv2/highgui.hpp>

//to don't add the namespace in code (remove std::)
using namespace std;
//makes the openCV classes and functions easier to identify within your code.(remove cv::)
using namespace cv;


int openImage();

int main()
{
	int num = 9;

	do {


		cout << "1 - Open and save a Image\n\n";

		cout << "Choice app One: ";
		cin >> num;



		switch (num){
		case 1: openImage(); break;
		case 2:
			//
			break;
		case 3 :
			//
			break;
		}

	} while (num == 0);
}

int openImage() {

	Mat image;
	
	cout << "this Image is " << image.rows << " x " << image.cols << endl;
	//image as a three channel color
	image = imread("images/Dog.jpg");

	if (image.empty()) {
		return 0;
	}
	//name of the windows
	namedWindow("Oregnal Dog Image");
	imshow("Oregnal Dog Image", image);


	//ROTATE_90_CLOCKWISE = 0, //!<Rotate 90 degrees clockwise
	Mat flip90_Image;
	flip(image, flip90_Image, 0);
	namedWindow("Rotate 90 degrees clockwise Dog Image");
	imshow("Rotate 90 degrees clockwise Dog Image", flip90_Image);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_flip90_Image.bmp", flip90_Image);

	//ROTATE_180 = 1, //!<Rotate 180 degrees clockwise
	Mat flip180_Image;
	flip(image, flip180_Image, 1);
	namedWindow("Rotate 180 degrees clockwise Dog Image");
	imshow("Rotate 180 degrees clockwise Dog Image", flip180_Image);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_flip180_Image.tiff", flip90_Image);

	//ROTATE_90_COUNTERCLOCKWISE = 2, //!<Rotate 270 degrees clockwise
	Mat flip270_Image;
	flip(image, flip270_Image, 2);
	namedWindow("Rotate 270 degrees clockwise Dog Image");
	imshow("Rotate 270 degrees clockwise Dog Image", flip270_Image);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_flip270_Image.png", flip90_Image);

	/*This is very advantageous since several computer vision algorithms require gray level images.
	   Converting an input color image on the fly as you read it will save you time and minimize your memory usage. */
	//reade gray level images
	Mat grayImage = imread("images/dog.jpg", IMREAD_GRAYSCALE);
	namedWindow("IMREAD_GRAYSCALE Dog Image");
	imshow("IMREAD_GRAYSCALE Dog Image", grayImage);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_GrayImage.jpg", grayImage);

	//to Pause the app
	waitKey(0);

	return 0;
}
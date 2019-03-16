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

//#include <opencv2/imgproc.hpp>

//to don't add the namespace in code (remove std::)
using namespace std;
//makes the openCV classes and functions easier to identify within your code.(remove cv::)
using namespace cv;


void openImage();
void highguiEvents();

int main()
{
	int num = 9;

	do {


		cout << "1 - Open and save a Image\n";
		cout << "2 - Mouse Event\n";

		cout << "\nChoice app One: ";
		cin >> num;



		switch (num){
		case 1: openImage(); break;
		case 2: highguiEvents();  break;
		case 3 :
			//
			break;
		}

	} while (num == 0);
}

void openImage() {

	Mat image;
	
	cout << "this Image is " << image.rows << " x " << image.cols << endl;
	//image as a three channel color
	image = imread("images/Dog.jpg");

	if (image.empty()) {
		cout << "image not exsist " << endl;
		
	}
	//name of the windows
	namedWindow("Oregnal Dog Image");
	//an image made up of integers designated as cv16u for 16 bit unsigned integers or cv32s for a 32 bit sine integers.
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

	//ROTATE_90 them 180_ = -1, //!<Rotate 90 degrees then 180 degrees clockwise
	Mat flip_minus1_Image;
	flip(image, flip_minus1_Image, -1);
	namedWindow("Rotate 90 degrees then 180 degrees Dog Image");
	imshow("Rotate 90 degrees then 180 degrees Dog Image", flip_minus1_Image);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_flip90_180_Image.png", flip_minus1_Image);

	/*This is very advantageous since several computer vision algorithms require gray level images.
	   Converting an input color image on the fly as you read it will save you time and minimize your memory usage. */
	//reade gray level images
	Mat grayImage = imread("images/dog.jpg", IMREAD_GRAYSCALE);
	namedWindow("IMREAD_GRAYSCALE Dog Image");
	imshow("IMREAD_GRAYSCALE Dog Image", grayImage);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_GrayImage.jpg", grayImage);
	cout << "IMREAD_GRAYSCALE Image is " << grayImage.rows << " x " << grayImage.cols << "| channels: " << grayImage.channels() << endl;

	//
	//in IMREAD_GRAYSCALE we convert the imahe channels to 1, but here IMREAD_COLOR we convert this channel to 3
	Mat colorImage = imread("images/Dog_GrayImage.jpg", IMREAD_COLOR);
	namedWindow("IMREAD_COLOR Dog Image");
	imshow("IMREAD_COLOR Dog Image", colorImage);
	//save image in local disk (image extension (.bmp .jpg .png .tiff))
	imwrite("images/Dog_GrayImage_in3Channels.jpg", colorImage);
	cout << "IMREAD_COLOR Image is " << colorImage.rows << " x " << colorImage.cols <<"| channels: " <<colorImage.channels() << endl;
	//example: in IMREAD_GRAYSCALE (x 50, y100 ) = (180), but in IMREAD_COLOR convert 1 channel to 3 (x 50, y100 ) = rgb(r=180, g=180,b=180)


	//to Pause the app
	waitKey(0);
}

/*
the first parameter is an integer that is used to specify which type of mouse event has triggered the call to the callback function.
The other two (x , y) parameters are simply the pixel coordinates of the mouse location when the event has occurred.
The flags are used to determine which button was pressed when the mouse event was triggered.
Finally the last perimeter is used to send an extra parameter to the function in the form of a pointer to any object.
*/
void onMouse(int event, int x, int y, int flags, void* param) {

	Mat *im = reinterpret_cast<Mat*>(param);

	//get mouse location
	cout << "Mouse location at (" << x << "," << y << ") value is : " << static_cast<int>(im->at<uchar>(Point(x, y))) << endl;

	switch (event){

	case EVENT_LBUTTONDOWN:
			cout << "EVENT_LBUTTON DOWN at (" << x << "," << y << ") value is : " <<
			static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
			break;
	case EVENT_LBUTTONUP:
		cout << "EVENT_LBUTTON UP at (" << x << "," << y << ") value is : " <<
			static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
		break;
	case EVENT_MOUSEMOVE:
		cout << "EVENT_MOUSE MOVE at (" << x << "," << y << ") value is : " <<
			static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
		break;
	case EVENT_LBUTTONDBLCLK:
		cout << "EVENT_LBUTTON DBLCLK at (" << x << "," << y << ") value is : " <<
			static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
		break;
	
	}

}
void highguiEvents() {

	//image as a three channel color
	Mat image = imread("images/Dog.jpg");

	if (image.empty()) {
		cout << "image not exsist " << endl;

	}

	//name of the windows
	namedWindow("Oregnal Dog Image");
	//an image made up of integers designated as cv16u for 16 bit unsigned integers or cv32s for a 32 bit sine integers.
	imshow("Oregnal Dog Image", image);

	setMouseCallback("Oregnal Dog Image", onMouse, reinterpret_cast<void*>(&image));



	waitKey(0);
}


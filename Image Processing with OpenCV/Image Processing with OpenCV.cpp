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
// for drow chaps, mithod likes (circle, )
#include <opencv2/imgproc.hpp>

//to don't add the namespace in code (remove std::)
using namespace std;
//makes the openCV classes and functions easier to identify within your code.(remove cv::)
using namespace cv;


void openImage();
void mouseEvents();
void cvMatStractuer();

int main()
{
	int num = 9;
	do {
		cout << "1 - Open and save a Image\n";
		cout << "2 - Mouse Event\n";
		cout << "3 - cvMat Stractuer\n";

		cout << "\nChoice app One: "; 
		cin >> num;

		switch (num){
		case 1: openImage(); break;
		case 2: mouseEvents();  break;
		case 3:cvMatStractuer(); break;

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
	//image location in memory
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
	case EVENT_RBUTTONDOWN:

		//drow the circal shape
		circle(*im, Point(x, y), 65, 0, 3);

		//write text in image
		string message = "this my dog";
		int msgLingth = message.length();//get string length
		int txt_X_Center = x - msgLingth * 10;
		putText(*im, message ,Point(txt_X_Center, y), FONT_HERSHEY_PLAIN, 2.5, 255, 2);
		//display in the same window name
		imshow("Oregnal Dog Image", *im);

		break;
	
	}

}
void mouseEvents() {

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


void cvMatStractuer() {


	/*
	CV_8U specify the type of each matrix element
	Which corresponds to one byte pixel grayscale images .
	The letter U  means it is unsigned.*/

	// create a new image made of 240 rows and 320 columns
	Mat image1(240, 320, CV_8U, 100);
	// or:
	// Mat image1(240,320,CV_8U,cv::Scalar(100));

	imshow("Image", image1); // show the image
	waitKey(0); // wait for a key pressed

	// re-allocate a new image using the create method when an image has already been previously allocated.
	// (only if size or type are different)
	image1.create(200, 200, CV_8U);
	imshow("Image1.create", image1); 
	waitKey(0); 

	image1 = 200;
	imshow("=200", image1); // show the image
	waitKey(0); // wait for a key pressed


	imshow("Image after all", image1); // after all change show the image1
	waitKey(0); // wait for a key pressed

	// create a red color image
	// channel order is BGR
	Mat image2(240, 320, CV_8UC3, Scalar(0, 0, 255));
	// or:
	// cv::Mat image2(cv::Size(320,240),CV_8UC3);
	// image2= cv::Scalar(0,0,255);

	imshow("Image", image2); // show the image
	waitKey(0); // wait for a key pressed

	// read an image
	Mat image3 = imread("images/dog.jpg");

	// all these images point to the same data block
	//if we change anything in image1 or image4 will change image3
	Mat image4(image3);
	image1 = image3;

	// these images are new copies of the source image
	image3.copyTo(image2);
	Mat image5 = image3.clone();

	// transform the image for testing
	flip(image3, image3, 1);

	flip(image1, image1, -1);//if we change anything in image1 or image4 will change image3

	// check which images have been affected by the processing
	imshow("Image3", image3);
	imshow("Image1 same data image3", image1);
	imshow("Image2", image2);
	imshow("Image4 same data", image4);
	imshow("Image5", image5);
	waitKey(0); // wait for a key pressed

	// get a gray-level image from a function
	// create image
	Mat ima(500, 500, CV_8U, 50);

	Mat gray = ima;

	imshow("Image", gray); // show the image
	waitKey(0); // wait for a key pressed

	// read the image in gray scale
	image1 = imread("images/dog.jpg", IMREAD_GRAYSCALE );

	// convert the image into a floating point image [0,1]
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);

	imshow("Image", image2); // show the image

	// Test Matx
	// a 3x3 matrix of double-precision
	Matx33d matrix(3.0, 2.0, 1.0,
		2.0, 1.0, 3.0,
		1.0, 2.0, 3.0);
	// a 3x1 matrix (a vector)
	Matx31d vector(5.0, 1.0, 3.0);
	// multiplication
	Matx31d result = matrix * vector;

	std::cout << result;


	waitKey(0);
}



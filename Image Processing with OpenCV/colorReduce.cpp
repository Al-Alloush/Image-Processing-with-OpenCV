
#include "pch.h"
#include "colorReduce.h"
#include <iostream>

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

using namespace std;
using namespace cv;

// 1st version
// see recipe Scanning an image with pointers
void colorReduce(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line

	for (int j = 0; j < nl; j++) {

		// get the address of row j
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			data[i] = data[i] / div * div + div / 2;

			// end of pixel processing ----------------

		} // end of line
	}
}

// version with input/ouput images
// see recipe Scanning an image with pointers
/*This extra overhead can be avoided by defining a function that gives the user the option to either use or not use in place processing, 
the signature of the method would then be like this:*/
void colorReduceIO(const Mat &image, // input image, this image will not be modified by the function.
						 Mat &result, // output image is passed as a reference such that the calling function will see the output argument modified by this call
						 int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols; // number of columns
	int nchannels = image.channels(); // number of channels

	//	allocate output image if necessary
	//	verify whether the output image has an allocated data buffer with a size and pixel type that matches the one of the input images. 
	//	create that build a matrix of the same size and type, as the input image.
	result.create(image.rows, image.cols, image.type());

	for (int j = 0; j < nl; j++) {
		// get the addresses of input and output row j
		const uchar* data_in = image.ptr<uchar>(j);
		uchar* data_out = result.ptr<uchar>(j);
		for (int i = 0; i < nc*nchannels; i++) {
			// process each pixel ---------------------
			data_out[i] = data_in[i] / div * div + div / 2;
			// end of pixel processing ----------------
		} // end of line
	}
}

// version 3
// this version uses the dereference operator *
void colorReduce3(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	uchar div2 = div >> 1; // div2 = div/2

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {


			// process each pixel ---------------------

			*data++ = *data / div * div + div2;

			// end of pixel processing ----------------

		} // end of line
	}
}

// version 4
// this version uses the modulo operator
void colorReduce4(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	uchar div2 = div >> 1; // div2 = div/2

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			int v = *data;
			*data++ = v - v % div + div2;

			// end of pixel processing ----------------

		} // end of line
	}
}

// version 5
// this version uses a binary mask
void colorReduce5(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = 1 << (n - 1); // div2 = div/2

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			*data &= mask;     // masking
			*data++ |= div2;   // add div/2

		  // end of pixel processing ----------------

		} // end of line
	}
}


// version 6
// this version uses direct pointer arithmetic with a binary mask
void colorReduce6(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	int step = image.step; // effective width
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = div >> 1; // div2 = div/2

	// get the pointer to the image buffer
	uchar *data = image.data;

	for (int j = 0; j < nl; j++) {

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			*(data + i) &= mask;
			*(data + i) += div2;

			// end of pixel processing ----------------

		} // end of line

		data += step;  // next line
	}
}

// version 7
// this version recomputes row size each time
void colorReduce7(Mat image, int div) {

	int nl = image.rows; // number of lines
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < image.cols * image.channels(); i++) {

			// process each pixel ---------------------

			*data &= mask;
			*data++ += div / 2;

			// end of pixel processing ----------------

		} // end of line
	}
}

// version 8
// this version optimizes the case of continuous image
void colorReduce8(Mat image, int div) {
	int nl = image.rows; // number of lines
	int nc = image.cols * image.channels(); // total number of elements per line
	//isContinuous() is returns true if the image does not include badded pixels.
	if (image.isContinuous()) {
		// then no padded pixels
		nc = nc * nl;
		nl = 1;  // it is now a 1D array
	}
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// defined two lines for mask which is used for round of pixel value, mask used to round the pixel value 
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = div >> 1; // div2 = div/2

   //	in case of continuous images
	/*	this loop is executed only once in case of continuous images, 
		now when the continuity test tells us that the image does not contain padded pixels we eliminate 
		the outer loop by setting the width to 1 and the height to W into H.	*/
	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);
		for (int i = 0; i < nc; i++) {
			// process each pixel ---------------------
			*data &= mask;
			*data++ += div2;
			// end of pixel processing ----------------
		} // end of line
	}
}

// version 9
// this versions applies reshape on continuous image
void colorReduce9(Mat image, int div) {

	if (image.isContinuous()) {
		// no padded pixels
		//the reshape method changes the matrix dimensions without requiring any memory copying or re-allocation.
		image.reshape(1,   // new number of channels, the number of columns is readjusted accordingly.
			1); // new number of rows
	}
	// number of columns set accordingly

	int nl = image.rows; // number of lines
	int nc = image.cols*image.channels(); // number of columns

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = div >> 1; // div2 = div/2

	for (int j = 0; j < nl; j++) {

		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			*data &= mask;
			*data++ += div2;

			// end of pixel processing ----------------

		} // end of line
	}
}

// version 10
// this version processes the 3 channels inside the loop with Mat_ iterators
void colorReduce10(Mat image, int div) {

	// get iterators
	cv::Mat_<cv::Vec3b>::iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::iterator itend = image.end<cv::Vec3b>();
	uchar div2 = div >> 1; // div2 = div/2

	for (; it != itend; ++it) {

		// process each pixel ---------------------

		(*it)[0] = (*it)[0] / div * div + div2;
		(*it)[1] = (*it)[1] / div * div + div2;
		(*it)[2] = (*it)[2] / div * div + div2;

		// end of pixel processing ----------------
	}
}

// version 11
// this version uses iterators on Vec3b
void colorReduce11(Mat image, int div) {

	// get iterators
	cv::MatIterator_<cv::Vec3b> it = image.begin<cv::Vec3b>();
	cv::MatIterator_<cv::Vec3b> itend = image.end<cv::Vec3b>();

	const cv::Vec3b offset(div / 2, div / 2, div / 2);

	for (; it != itend; ++it) {

		// process each pixel ---------------------

		*it = *it / div * div + offset;
		// end of pixel processing ----------------
	}
}

// version 12
// this version uses iterators with a binary mask
void colorReduce12(Mat image, int div) {

	// div must be a power of 2
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0
	uchar div2 = div >> 1; // div2 = div/2

	// get iterators
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();


	// scan all pixels
	for (; it != itend; ++it) {

		// process each pixel ---------------------

		(*it)[0] &= mask;
		(*it)[0] += div2;
		(*it)[1] &= mask;
		(*it)[1] += div2;
		(*it)[2] &= mask;
		(*it)[2] += div2;

		// end of pixel processing ----------------
	}
}

// version 13
// this versions uses ierators from Mat_ 
void colorReduce13(Mat image, int div) {

	// get iterators
	cv::Mat_<cv::Vec3b> cimage = image;
	cv::Mat_<cv::Vec3b>::iterator it = cimage.begin();
	cv::Mat_<cv::Vec3b>::iterator itend = cimage.end();
	uchar div2 = div >> 1; // div2 = div/2

	for (; it != itend; it++) {

		// process each pixel ---------------------

		(*it)[0] = (*it)[0] / div * div + div2;
		(*it)[1] = (*it)[1] / div * div + div2;
		(*it)[2] = (*it)[2] / div * div + div2;

		// end of pixel processing ----------------
	}
}


// version 14
// this version uses the at method
void colorReduce14(Mat image, int div) {

	int nl = image.rows; // number of lines
	int nc = image.cols; // number of columns
	uchar div2 = div >> 1; // div2 = div/2

	for (int j = 0; j < nl; j++) {
		for (int i = 0; i < nc; i++) {

			// process each pixel ---------------------

			image.at<cv::Vec3b>(j, i)[0] = image.at<cv::Vec3b>(j, i)[0] / div * div + div2;
			image.at<cv::Vec3b>(j, i)[1] = image.at<cv::Vec3b>(j, i)[1] / div * div + div2;
			image.at<cv::Vec3b>(j, i)[2] = image.at<cv::Vec3b>(j, i)[2] / div * div + div2;

			// end of pixel processing ----------------

		} // end of line
	}
}


// version 15
// this version uses Mat overloaded operators
void colorReduce15(Mat image, int div) {

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	// mask used to round the pixel value
	uchar mask = 0xFF << n; // e.g. for div=16, mask= 0xF0

	// perform color reduction
	image = (image&cv::Scalar(mask, mask, mask)) + cv::Scalar(div / 2, div / 2, div / 2);
}

// version 16
// this version uses a look up table
void colorReduce16(Mat image, int div) {

	cv::Mat lookup(1, 256, CV_8U);

	for (int i = 0; i < 256; i++) {

		lookup.at<uchar>(i) = i / div * div + div / 2;
	}

	cv::LUT(image, lookup, image);
}
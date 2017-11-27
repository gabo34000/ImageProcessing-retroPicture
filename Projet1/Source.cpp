#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace cv;
using namespace std;

void stretchPixels(Mat image)
{

}

void distortColors(Mat image)
{
	srand((unsigned)time(NULL));

	int width = image.size().width;
	int height = image.size().height;
	int rx = (rand() % 10) - 5;
	int ry = (rand() % 10) - 5;
	int gx = (rand() % 10) - 5;
	int gy = (rand() % 10) - 5;
	int bx = (rand() % 10) - 5;
	int by = (rand() % 10) - 5;
	Mat buffer = image.clone();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if ((y + by) >= 0 && (x + bx) >= 0 &&
				(y + by) < height && (x + bx) < width)
				image.at<cv::Vec3b>(y, x)[0] = buffer.at<cv::Vec3b>(y + by, x + bx)[0];
			
			if ((y + gy) >= 0 && (x + gx) >= 0 &&
				(y + gy) < height && (x + gx) < width)
				image.at<cv::Vec3b>(y, x)[1] = buffer.at<cv::Vec3b>(y + gy, x + gx)[1];

			if ((y + ry) >= 0 && (x + rx) >= 0 &&
				(y + ry) < height && (x + rx) < width)
				image.at<cv::Vec3b>(y, x)[2] = buffer.at<cv::Vec3b>(y + ry, x + rx)[2];
		}
	}
}

void addNoise(Mat image)
{

}

void addTimeStamp(Mat image)
{

}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	//todo
	stretchPixels(image);
	distortColors(image);
	addNoise(image);
	addTimeStamp(image);

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}


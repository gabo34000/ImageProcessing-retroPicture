#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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

void stretchPixels(Mat image)
{

}

void distortColors(Mat image)
{

}

void addNoise(Mat image)
{

}

void addTimeStamp(Mat image)
{

}
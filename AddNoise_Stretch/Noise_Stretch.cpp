#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace cv;
using namespace std;

void stretchPixels(Mat image);
void addNoise(Mat image);

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
	//stretchPixels(image);
	//distortColors(image);
	addNoise(image);
	//addTimeStamp(image);

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}

void stretchPixels(Mat image)
{
	Vec3b color_image;
	int image_width, image_height;
	int randNum,tmp;
	int *randLocation, *randSize;

	image_width = image.cols;
	image_height = image.rows;

	srand(time(NULL));
	randNum = rand() % 3 +1;

	randLocation = new int [randNum];
	randSize = new int[randNum];

	for (int i = 0; i < randNum; i++){
		tmp = rand() % (image_height / 3) + (image_height / 3)*i;

		randLocation[i] = tmp;
		randSize[i] = rand() % (image_height/3);
	}

	for (int i = 0; i < randNum; i++){
		if (i == randNum - 1){
			if (randLocation[i] + randSize[i] >= image_height){
				randSize[i] -= (randLocation[i] + randSize[i]) - image_height + rand() % (image_height - randLocation[i]);
			}
		}
		else if (randLocation[i] + randSize[i] >= randLocation[i + 1]){
			randSize[i] -= (randLocation[i] + randSize[i]) - randLocation[i + 1] + rand() % (randLocation[i + 1] - randLocation[i]);
		}
	}

	for (int k = 0; k < image_width; k++){
		for (int i = 0; i < randNum; i++){
			color_image = image.at<Vec3b>(randLocation[i], k);
			for (int j = 0; j < randSize[i]; j++){
				image.at<Vec3b>(randLocation[i] + j, k) = color_image;
			}
		}
	}
}

void distortColors(Mat image)
{

}

void addNoise(Mat image)
{
	Mat noiseimage;
	string noiseName;
	Vec3b color_image, color_noiseimage;
	
	int image_width, image_height, noiseimage_width, noiseimage_height;
	int num_repeat_width, num_repeat_height;

	getline(cin, noiseName, '\n');
	noiseimage = imread(noiseName);

	image_width = image.cols;
	image_height = image.rows;
	noiseimage_width = noiseimage.cols;
	noiseimage_height = noiseimage.rows;

	num_repeat_width = image_width / noiseimage_width;
	num_repeat_height = image_height / noiseimage_height;

	for (int l = 0; l <= num_repeat_height; l++){
		for (int j = 0; j < noiseimage_height; j++){
			for (int k = 0; k <= num_repeat_width; k++){
				for (int i = 0; i < noiseimage_width; i++){
					if (i + k*noiseimage_width < image_width && j + l*noiseimage_height < image_height){

						color_image = image.at<Vec3b>(j + l*noiseimage_height, i + k*noiseimage_width);
						color_noiseimage = noiseimage.at<Vec3b>(j, i);

						color_image[0] = color_image[0] * color_noiseimage[0] / 255;
						color_image[1] = color_image[1] * color_noiseimage[1] / 255;
						color_image[2] = color_image[2] * color_noiseimage[2] / 255;

						image.at<Vec3b>(j + l*noiseimage_height, i + k*noiseimage_width) = color_image;
					}
				}
			}
		}
	}
	
}

void addTimeStamp(Mat image)
{

}
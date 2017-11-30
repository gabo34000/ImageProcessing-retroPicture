#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#pragma warning(disable : 4996)
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

void addTimeStamp(Mat image, Mat imageC)
{
	time_t t = time(0);
	struct tm * now = localtime(&t);

	int day = now->tm_mday;
	int month = now->tm_mon + 1;
	int year = now->tm_year + 1900;
	int hour = now->tm_hour;
	int min = now->tm_min;
	int size = 0;
	int size2 = 0;
	//PM OR AM
	Mat M = imread("pm.png", IMREAD_COLOR);
	if (hour > 12) {
		hour = hour - 12;
		M = imread("pm.png", IMREAD_COLOR);
		cv::resize(M, M, M.size() / 3);
		M.copyTo(image(cv::Rect(30, image.size().height - 80, M.cols, M.rows)));
	}
	else {
		M = imread("am.png", IMREAD_COLOR);
		cv::resize(M, M, M.size() / 3);
		M.copyTo(image(cv::Rect(30, image.size().height - 80, M.cols, M.rows)));
	}
	//HOUR
	if (hour < 10) {
		string hh = std::to_string(hour) + ".png";
		Mat H = imread(hh, IMREAD_COLOR);
		cv::resize(H, H, H.size() / 3);
		H.copyTo(image(cv::Rect(M.size().width + 45, image.size().height - 80, H.cols, H.rows)));
		size = M.size().width + 45 + H.size().width;
	}
	else {
		Mat H = imread("1.png", IMREAD_COLOR);
		cv::resize(H, H, H.size() / 3);
		H.copyTo(image(cv::Rect(M.size().width + 45, image.size().height - 80, H.cols, H.rows)));
		hour = hour - 10;
		string hh = std::to_string(hour) + ".png";
		H = imread(hh, IMREAD_COLOR);
		cv::resize(H, H, H.size() / 3);
		H.copyTo(image(cv::Rect(M.size().width + 45 + H.size().width, image.size().height - 80, H.cols, H.rows)));
		size = M.size().width + 40 + H.size().width + H.size().width;
	}
	Mat pts = imread("2pts.png", IMREAD_COLOR);
	cv::resize(pts, pts, pts.size() / 3);
	pts.copyTo(image(cv::Rect(size + 5, image.size().height - 75, pts.cols, pts.rows)));
	size = size + pts.size().width;
	//MIN
	std::string s = std::to_string(min);
	char const *pchar = s.c_str();
	int i = pchar[0] - 48;
	string dec = std::to_string(i) + ".png";
	Mat DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size + 10, image.size().height - 80, DEC.cols, DEC.rows)));
	size = DEC.size().width + size;
	if (min > 9) {
		i = pchar[1] - 48;
		dec = std::to_string(i) + ".png";
		Mat MIN = imread(dec, IMREAD_COLOR);
		cv::resize(MIN, MIN, MIN.size() / 3);
		MIN.copyTo(image(cv::Rect(size + 12, image.size().height - 80, MIN.cols, MIN.rows)));
		size = MIN.size().width + size;
	}
	//MONTH
	string mm = std::to_string(month) + "m.png";
	M = imread(mm, IMREAD_COLOR);
	cv::resize(M, M, M.size() / 3);
	M.copyTo(image(cv::Rect(30, image.size().height - 50, M.cols, M.rows)));
	size2 = M.size().width + 43;
	//DAY
	s = std::to_string(day);
	pchar = s.c_str();
	i = pchar[0] - 48;
	dec = std::to_string(i) + ".png";
	DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size2, image.size().height - 50, DEC.cols, DEC.rows)));
	size2 = DEC.size().width + size2;
	if (day > 9) {
		i = pchar[1] - 48;
		dec = std::to_string(i) + ".png";
		DEC = imread(dec, IMREAD_COLOR);
		cv::resize(DEC, DEC, DEC.size() / 3);
		DEC.copyTo(image(cv::Rect(size2 + 3, image.size().height - 50, DEC.cols, DEC.rows)));
		size2 = DEC.size().width + size2 + 20;
	}

	//YEAR
	s = std::to_string(year);
	pchar = s.c_str();
	i = pchar[0] - 48;
	dec = std::to_string(i) + ".png";
	DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size2, image.size().height - 50, DEC.cols, DEC.rows)));
	size2 = DEC.size().width + size2 + 3;
	i = pchar[1] - 48;
	dec = std::to_string(i) + ".png";
	DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size2, image.size().height - 50, DEC.cols, DEC.rows)));
	size2 = DEC.size().width + size2 + 3;
	i = pchar[2] - 48;
	dec = std::to_string(i) + ".png";
	DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size2, image.size().height - 50, DEC.cols, DEC.rows)));
	size2 = DEC.size().width + size2 + 3;
	i = pchar[3] - 48;
	dec = std::to_string(i) + ".png";
	DEC = imread(dec, IMREAD_COLOR);
	cv::resize(DEC, DEC, DEC.size() / 3);
	DEC.copyTo(image(cv::Rect(size2, image.size().height - 50, DEC.cols, DEC.rows)));
	size2 = DEC.size().width + size2 + 3;


	for (int y = image.size().height - 80; y <image.size().height - 20; y++)
	{
		for (int x = 30; x< size2; x++)
		{
			Vec3b color = image.at<Vec3b>(Point(x, y));
			Vec3b colorC = imageC.at<Vec3b>(Point(x, y));
			if (color[0] < 20 && color[1] < 20 && color[2] < 20) {
				color[0] = colorC[0];
				color[1] = colorC[1];
				color[2] = colorC[2];
			}
			image.at<Vec3b>(Point(x, y)) = color;
		}
	}
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
	Mat imageC;
	imageC = imread(argv[1], IMREAD_COLOR);

	//todo
	stretchPixels(image);
	distortColors(image);
	addNoise(image);
	addTimeStamp(image, imageC);

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}


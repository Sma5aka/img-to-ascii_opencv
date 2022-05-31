#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "windows.h"
#include <locale.h>
#include <ctime>

void colorReduce(cv::Mat& image, int div = 64) {
	int nl = image.rows;
	int nc = image.cols * image.channels();

	for (int j = 0; j < nl; j++) {
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {
			data[i] = data[i] / div * div + div / 2;
		}
	}
}

inline void set_ind(cv::Mat& image, int row, int col, unsigned int ind) {
	image.at<cv::Vec3b>(row, col)[0] = ind;
	image.at<cv::Vec3b>(row, col)[1] = ind;
	image.at<cv::Vec3b>(row, col)[2] = ind;
}

void norm_pix(cv::Mat& image) {
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {

			int brightness = int(image.at<cv::Vec3b>(i, j)[0]) + int(image.at<cv::Vec3b>(i, j)[1]) + int(image.at<cv::Vec3b>(i, j)[2]);

			if (brightness <= 16) {
				set_ind(image, i, j, 1);
			}
			else if (brightness <= 32 && brightness > 16) {
				set_ind(image, i, j, 2);
			}
			else if (brightness <= 48 && brightness > 32) {
				set_ind(image, i, j, 3);
			}
			else if (brightness <= 64 && brightness > 48) {
				set_ind(image, i, j, 4);
			}
			else if (brightness <= 80 && brightness > 64) {
				set_ind(image, i, j, 5);
			}
			else if (brightness <= 96 && brightness > 80) {
				set_ind(image, i, j, 6);
			}
			else if (brightness <= 112 && brightness > 96) {
				set_ind(image, i, j, 7);
			}
			else if (brightness <= 128 && brightness > 112) {
				set_ind(image, i, j, 8);
			}
			else if (brightness <= 144 && brightness > 128) {
				set_ind(image, i, j, 9);
			}
			else if (brightness <= 160 && brightness > 144) {
				set_ind(image, i, j, 10);
			}
			else if (brightness <= 176 && brightness > 160) {
				set_ind(image, i, j, 11);
			}
			else if (brightness <= 192 && brightness > 176) {
				set_ind(image, i, j, 12);
			}
			else if (brightness <= 208 && brightness > 192) {
				set_ind(image, i, j, 13);
			}
			else if (brightness <= 224 && brightness > 208) {
				set_ind(image, i, j, 14);
			}
			else if (brightness <= 240 && brightness > 224) {
				set_ind(image, i, j, 15);
			}
			else if (brightness <= 255 && brightness > 240) {
				set_ind(image, i, j, 16);
			}
		}
	}
}

int main(int argc, const char** argv) {

	system("color 2");
	const int width = 120;
	const int height = 30;
	const int len = width * height;

	char* screen = new char[width * height + 1];
	screen[width * height] = '\0';

	char gradientik[] = "  .:!/r(l1Z4H9W8$@";
	const int gradientSize = 15;

	cv::Mat shape(height, width, CV_64F);
	
	cv::VideoCapture cap(0);
	
	cv::Mat img;
	cv::Mat img2;

	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;

	while (true) {
		current_ticks = clock();
		

		cap.read(img);
		cap.read(img2);

		cv::resize(img, img, cv::Size(shape.cols * 1, shape.rows * 1), 0, 0, cv::INTER_LINEAR);
		img = img * 0.2;
		norm_pix(img);

		for (int i = 0; i < width; i++) {
			for (int f = 0; f < height; f++) {
				for (int k = 0; k < gradientSize + 1; k++) {
					if (int(img.at<cv::Vec3b>(f, i)[0]) - 1 == k) {

						screen[i + f * width] = gradientik[k];
						break;
					}
				}
			}
		}

		if (!cv::EVENT_LBUTTONDOWN)
			break;

		printf(screen);
		cv::imshow("Video", img2);

		delta_ticks = clock() - current_ticks;
		if (delta_ticks > 0)
			fps = CLOCKS_PER_SEC / delta_ticks;
		//std::cout << "\n" << fps << "\n";
		cv::waitKey(1);
	}
	system("pause");
	return 0;
}
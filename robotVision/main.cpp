#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

int main()
{
	cv::Mat image=cv::Mat::zeros(4, 4, CV_8UC1);

	std::cout << image << "\n";

	return 0;
}

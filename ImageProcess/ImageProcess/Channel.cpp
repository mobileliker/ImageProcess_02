#include "StdAfx.h"
#include "Channel.h"

#include <sstream>
#include <fstream>


CChannel::CChannel(void)
	: m_debug(DEFAULT_DEBUG)
{

}


CChannel::~CChannel(void)
{
}


int CChannel::Gray(Mat src, Mat& gray)
{
	cvtColor(src, gray, CV_BGR2GRAY);

	if(m_debug)
	{ 
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_gray.bmp";
		imwrite(ss.str(), gray);
	}

	return 0;
}

int CChannel::iRGB(Mat src, Mat &dst, const int type)
{
	vector<Mat> channels;

	split(src, channels);

	dst = channels.at(type);

	return 0;
}

int CChannel::iHSV(Mat src, Mat &dst, const int type)
{
	Mat hsv;
	cvtColor(src, hsv, CV_BGR2HSV);
	vector<Mat> channels;
	split(hsv, channels);
	dst = channels.at(type);

	if(0 == type) dst.convertTo(dst, CV_8U, 256.0/180);

	if(m_debug)
	{ 
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_gray.bmp";
		imwrite(ss.str(), dst);

		//std::ofstream outfile("tmp/debug_hsv.txt");
		int max = -1, min = 500;
		for(int i = 0; i < dst.rows; ++i)
		{
			for(int j = 0; j < dst.cols; ++j)
			{
				if(max < dst.at<uchar>(i, j)) max = dst.at<uchar>(i, j);
				if(min > dst.at<uchar>(i, j)) min = dst.at<uchar>(i, j);
				//outfile << "(" << i << "," << j << "):" << (int)dst.at<uchar>(i, j) << std::endl;
			}
		}
		//outfile.close();
	}

	return 0;
}
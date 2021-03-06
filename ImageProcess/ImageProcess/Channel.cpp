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

	if(3 == type)
	{		
		/*dst.create(src.rows, src.cols, CV_8UC(1));
		for(int i = 0; i < dst.rows; ++i)
		{
			for(int j = 0; j < dst.cols; ++j)
			{
				
				uchar value = src.at<Vec3b>(i, j)[0] > src.at<Vec3b>(i, j)[1] ? src.at<Vec3b>(i, j)[0] : src.at<Vec3b>(i, j)[1];
				if(value < src.at<Vec3b>(i, j)[2]) value = src.at<Vec3b>(i, j)[2];
				dst.at<uchar>(i, j) = value;
			}
		}*/
		max(channels.at(0), channels.at(1), dst);
		max(channels.at(2), dst, dst);
	}
	else if(4 == type)
	{
		dst.create(src.rows, src.cols, CV_8UC(1));
		for(int i = 0; i < dst.rows; ++i)
		{
			for(int j = 0; j < dst.cols; ++j)
			{
				dst.at<uchar>(i, j) = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2]) / 3;  
			}
		}
	}
	else
	{
		dst = channels.at(type);
	}

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
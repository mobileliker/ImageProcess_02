#include "StdAfx.h"
#include "Channel.h"

#include <sstream>


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

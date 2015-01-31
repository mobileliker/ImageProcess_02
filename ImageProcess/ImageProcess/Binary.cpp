#include "StdAfx.h"
#include "Binary.h"

#include "Histogram.h"


CBinary::CBinary(void) : m_debug(DEFAULT_DEBUG)
{
}


CBinary::~CBinary(void)
{
}


int CBinary::Mode(Mat src, Mat &dst)
{
	int i,j;
	int size = 10;

	CHistogram histogram;

	int arr_hist[256];

	histogram.Hist(src, arr_hist);

	//find Left Peak
	for(i = 0; i < 256 - 1; ++i)
	{
		if(arr_hist[i] > arr_hist[i + 1])
		{
			for(j = i + 1; j < i + 1 + size && j < 256; ++j)
			{
				if(arr_hist[i] < arr_hist[j]) break;
			}
			if(j >= i + 1 + size || j >= 256) break;
		}
	}
	int idx_l = i;

	//find Right Peak
	for(i = 256 - 1; i > idx_l; --i)
	{
		if(arr_hist[i - 1] < arr_hist[i])
		{
			for(j = i - 1; j > i - 1 - size && j >= 0; --j)
			{
				if(arr_hist[i] < arr_hist[j]) break;
			}
			if(j <= i - 1 - size || j < 0) break;
		}
	}
	if(i <= idx_l) return 1;
	int idx_r = i;

	//find Min;
	int idx_min = (idx_l + idx_r) / 2;
	for(i = idx_l; i <= idx_r; ++i)
	{
		if(arr_hist[idx_min] > arr_hist[i]) idx_min = i;
	}
	
	threshold(src, dst,idx_min, 255, CV_THRESH_BINARY);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_mode.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}

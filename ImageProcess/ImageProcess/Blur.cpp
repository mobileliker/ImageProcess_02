#include "StdAfx.h"
#include "Blur.h"


CBlur::CBlur(void): m_debug(DEFAULT_DEBUG)
{
}


CBlur::~CBlur(void)
{
}


int CBlur::Salt(Mat src, Mat &dst,int n)
{
	src.copyTo(dst);
	for (int k = 0; k < n; ++k) {
		int i = rand() % dst.cols;
		int j = rand() % dst.rows;
		int s = rand() % 2;


		for(int p = 0; p < dst.channels(); ++p)
		{
			dst.at<Vec3b>(j,i)[p] = 255 * s;
		}
	}

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_noise_salt.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

int CBlur::HomogeneousBlur(Mat src, Mat& dst, int n)
{
	blur(src, dst, Size(n, n));
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_blur_homogeneous.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}


int CBlur::iGuassianBlur(Mat src, Mat &dst, int n)
{
	GaussianBlur(src, dst, Size(n, n), 0, 0);
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_blur_gaussian.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

int CBlur::iMedianBlur(Mat src, Mat &dst, int n)
{
	medianBlur(src, dst, n);
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_blur_median.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

int CBlur::iBilatrialBlur(Mat src, Mat &dst, int n)
{
	bilateralFilter(src, dst, n, n * 2, (double)n / 2);
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_blur_bilatrial.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

//http://blog.csdn.net/lichengyu/article/details/31829787
double generateGaussianNoise()
{
	static double TWO_PI = 6.2831853071795864769252866;
	static bool hasSpare = false;
	static double rand1, rand2;
 
	if(hasSpare)
	{
		hasSpare = false;
		return sqrt(rand1) * sin(rand2);
	}
 
	hasSpare = true;
 
	rand1 = rand() / ((double) RAND_MAX);
	if(rand1 < 1e-100) rand1 = 1e-100;
	rand1 = -2 * log(rand1);
	rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;
 
	return sqrt(rand1) * cos(rand2);
}


void AddGaussianNoise(Mat& I)
{
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if(I.isContinuous()){
		nCols *= nRows;
		nRows = 1;
	}

	int i,j;
	uchar* p;
	for(i = 0; i < nRows; ++i){
		p = I.ptr<uchar>(i);
		for(j = 0; j < nCols; ++j){
			double val = p[j] + generateGaussianNoise() * 128;
			if(val < 0)
				val = 0;
			if(val > 255)
				val = 255;

			p[j] = (uchar)val;

		}
	}

}

int CBlur::Gaussian(Mat src, Mat &dst)
{
	src.copyTo(dst);
	AddGaussianNoise(dst);
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_noise_gaussian.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

int CBlur::iAdaptiveBilateralBlur(Mat src, Mat &dst, int n)
{
	adaptiveBilateralFilter(src, dst, Size(n, n), 75);
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_blur_bilatrial.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}


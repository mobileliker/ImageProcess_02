#include "StdAfx.h"
#include "Histogram.h"
#include <fstream>


CHistogram::CHistogram(void): m_debug(DEFAULT_DEBUG)
{
}


CHistogram::~CHistogram(void)
{
}


int CHistogram::Show(Mat src, Mat& hist)
{
	IplImage img = src;
	IplImage *gray_plane = &img;

	int hist_size = 256;    //直方图尺寸
	int hist_height = 256;
	float range[] = {0,255};  //灰度级的范围
	float* ranges[]={range};
	//创建一维直方图，统计图像在[0 255]像素的均匀分布
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);

	//计算灰度图像的一维直方图
	cvCalcHist(&gray_plane,gray_hist,0,0);
	//归一化直方图
	cvNormalizeHist(gray_hist,1.0);

	int scale = 2;
	//创建一张一维直方图的“图”，横坐标为灰度级，纵坐标为像素个数（*scale）
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale,hist_height),8,3);
	cvZero(hist_image);
	//统计直方图中的最大直方块
	float max_value = 0;
	cvGetMinMaxHistValue(gray_hist, 0,&max_value,0,0);
	
	//分别将每个直方块的值绘制到图中
	for(int i=0;i<hist_size;i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //像素i的概率
		int intensity = cvRound(bin_val*hist_height/max_value);  //要绘制的高度
		cvRectangle(hist_image,
			cvPoint(i*scale,hist_height-1),
			cvPoint((i+1)*scale - 1, hist_height - intensity),
			CV_RGB(255,255,255));  
	}

	hist = hist_image;

	if(m_debug)
	{ 
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_hist.bmp";
		imwrite(ss.str(), hist);
	}

	return 0;
}


int CHistogram::Hist(Mat src, int * arr_hist)
{
	IplImage img = src;
	IplImage *gray_plane = &img;

	int hist_size = 256;    //直方图尺寸
	int hist_height = 256;
	float range[] = {0,255};  //灰度级的范围
	float* ranges[]={range};

	//创建一维直方图，统计图像在[0 255]像素的均匀分布
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);

	//计算灰度图像的一维直方图
	cvCalcHist(&gray_plane,gray_hist,0,0);
	
	for(int i=0;i<hist_size;i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //像素i的概率
		arr_hist[i] = (int)bin_val;
	}

	if(m_debug)
	{
		std::ofstream outfile("tmp/debug_hist.txt");
		for(int i = 0; i < hist_size; ++i)
		{
			outfile << i << " : " << arr_hist[i] << std::endl;
		}
		outfile.close();
	}
	return 0;
}

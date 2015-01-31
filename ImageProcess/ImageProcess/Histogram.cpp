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

	int hist_size = 256;    //ֱ��ͼ�ߴ�
	int hist_height = 256;
	float range[] = {0,255};  //�Ҷȼ��ķ�Χ
	float* ranges[]={range};
	//����һάֱ��ͼ��ͳ��ͼ����[0 255]���صľ��ȷֲ�
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);

	//����Ҷ�ͼ���һάֱ��ͼ
	cvCalcHist(&gray_plane,gray_hist,0,0);
	//��һ��ֱ��ͼ
	cvNormalizeHist(gray_hist,1.0);

	int scale = 2;
	//����һ��һάֱ��ͼ�ġ�ͼ����������Ϊ�Ҷȼ���������Ϊ���ظ�����*scale��
	IplImage* hist_image = cvCreateImage(cvSize(hist_size*scale,hist_height),8,3);
	cvZero(hist_image);
	//ͳ��ֱ��ͼ�е����ֱ����
	float max_value = 0;
	cvGetMinMaxHistValue(gray_hist, 0,&max_value,0,0);
	
	//�ֱ�ÿ��ֱ�����ֵ���Ƶ�ͼ��
	for(int i=0;i<hist_size;i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //����i�ĸ���
		int intensity = cvRound(bin_val*hist_height/max_value);  //Ҫ���Ƶĸ߶�
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

	int hist_size = 256;    //ֱ��ͼ�ߴ�
	int hist_height = 256;
	float range[] = {0,255};  //�Ҷȼ��ķ�Χ
	float* ranges[]={range};

	//����һάֱ��ͼ��ͳ��ͼ����[0 255]���صľ��ȷֲ�
	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);

	//����Ҷ�ͼ���һάֱ��ͼ
	cvCalcHist(&gray_plane,gray_hist,0,0);
	
	for(int i=0;i<hist_size;i++)
	{
		float bin_val = cvQueryHistValue_1D(gray_hist,i); //����i�ĸ���
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

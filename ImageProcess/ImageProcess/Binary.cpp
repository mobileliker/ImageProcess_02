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
	if(i <= idx_l) return 1; // other one peak
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



int CBinary::otsuThreshold(Mat src)
{
	IplImage i_src = src;
	IplImage *p_src = &i_src;
	const int GrayScale = 256;
	int width = p_src->width;
	int height = p_src->height;
	int pixelCount[GrayScale];
	float pixelPro[GrayScale];
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)p_src->imageData;

	for(i = 0; i < GrayScale; i++)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	//统计灰度级中每个像素在整幅图像中的个数
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			pixelCount[(int)data[i * width + j]]++;
		}
	}
	
	//计算每个像素在整幅图像中的比例
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}

	//遍历灰度级[0,255]
	float w0, w1, u0tmp, u1tmp, u0, u1, u, 
			deltaTmp, deltaMax = 0;
	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   //背景部分
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   //前景部分
			{
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}
		u0 = u0tmp / w0;
		u1 = u1tmp / w1;
		u = u0tmp + u1tmp;
		deltaTmp = 
			w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
		if(deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	return threshold;
}

int CBinary::otsuThreshold(Mat src, Mat mark)
{
	IplImage i_src = src;
	IplImage *p_src = &i_src;
	const int GrayScale = 256;
	int width = p_src->width;
	int height = p_src->height;
	int pixelCount[GrayScale];
	float pixelPro[GrayScale];
	int i, j, pixelSum = width * height, threshold = 0;
	uchar* data = (uchar*)p_src->imageData;

	for(i = 0; i < GrayScale; i++)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	//统计灰度级中每个像素在整幅图像中的个数
	for(i = 0; i < height; i++)
	{
		for(j = 0;j < width;j++)
		{
			if(mark.at<uchar>(i, j) != 0)	pixelCount[(int)data[i * width + j]]++;
		}
	}
	
	//计算每个像素在整幅图像中的比例
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (float)pixelCount[i] / pixelSum;
	}

	//遍历灰度级[0,255]
	float w0, w1, u0tmp, u1tmp, u0, u1, u, 
			deltaTmp, deltaMax = 0;
	for(i = 0; i < GrayScale; i++)
	{
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
		for(j = 0; j < GrayScale; j++)
		{
			if(j <= i)   //背景部分
			{
				w0 += pixelPro[j];
				u0tmp += j * pixelPro[j];
			}
			else   //前景部分
			{
				w1 += pixelPro[j];
				u1tmp += j * pixelPro[j];
			}
		}
		u0 = u0tmp / w0;
		u1 = u1tmp / w1;
		u = u0tmp + u1tmp;
		deltaTmp = 
			w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
		if(deltaTmp > deltaMax)
		{
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	return threshold;
}

int CBinary::OTSU(Mat src, Mat &dst)
{
	threshold(src, dst, 170, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_otsu.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

int CBinary::OTSU(Mat src, Mat mark, Mat &dst)
{
	int threshold_value = otsuThreshold(src, mark);
	threshold(src, dst, threshold_value, 255, CV_THRESH_BINARY_INV);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_otsu_mark.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}

typedef enum {back,object} entropy_state;

double caculateCurrentEntropy(CvHistogram * Histogram1,int cur_threshold,entropy_state state)
{

	int start,end;
	int i;

	if(state == back)
	{
		start = 0;end = cur_threshold;
	}
	else
	{
		start = cur_threshold;end = 256;
	}
	int total = 0;
	for(i=start;i<end;i++)
	{
		total += (int)cvQueryHistValue_1D(Histogram1,i);
	}
	double cur_entropy = 0.0;
	for(i=start;i<end;i++)
	{
		if((int)cvQueryHistValue_1D(Histogram1,i)==0)
		{
		continue;
		}
		double percentage = cvQueryHistValue_1D(Histogram1,i)/total;
		cur_entropy += -percentage*logf(percentage);
	}
	return cur_entropy;
}
double caculateCurrentEntropy(int * arr_hist,int cur_threshold,entropy_state state)
{

	int start,end;
	int i;

	if(state == back)
	{
		start = 0;end = cur_threshold;
	}
	else
	{
		start = cur_threshold;end = 256;
	}
	int total = 0;
	for(i=start;i<end;i++)
	{
		//total += (int)cvQueryHistValue_1D(Histogram1,i);
		total += arr_hist[i];
	}
	double cur_entropy = 0.0;
	for(i=start;i<end;i++)
	{
		//if((int)cvQueryHistValue_1D(Histogram1,i)==0)
		if(arr_hist[i]==0)
		{
		continue;
		}
		//double percentage = cvQueryHistValue_1D(Histogram1,i)/total;
		double percentage = (double)arr_hist[i]/total;
		cur_entropy += -percentage*logf(percentage);
	}
	return cur_entropy;
}

int CBinary::MaxEntropy(Mat src, Mat &dst)
{
	int HistogramBins = 256;
	float HistogramRange1[2]={0,255};
	float *HistogramRange[1]={&HistogramRange1[0]};

	IplImage i_src = src;
	IplImage i_dst = dst;
	IplImage *p_src = &i_src;
	IplImage *p_dst = &i_dst;

	CvHistogram * hist = cvCreateHist(1,&HistogramBins,CV_HIST_ARRAY,HistogramRange);
	cvCalcHist(&p_src,hist);
	double maxentropy = -1.0;
	int max_index = -1;
	for(int i=0;i<HistogramBins;i++)
	{
		double cur_entropy = caculateCurrentEntropy(hist,i,object)+
		caculateCurrentEntropy(hist,i,back);
		if(cur_entropy>maxentropy)
		{
			maxentropy = cur_entropy;
			max_index = i;
		}
	}
	threshold(src, dst, (double)max_index, 255, CV_THRESH_BINARY);
	cvReleaseHist(&hist);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_maxentropy.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}

int CBinary::MaxEntropy(Mat src, Mat mark, Mat &dst)
{	
	int HistogramBins = 256;
	float HistogramRange1[2]={0,255};
	float *HistogramRange[1]={&HistogramRange1[0]};

	IplImage i_src = src;
	IplImage i_dst = dst;
	IplImage *p_src = &i_src;
	IplImage *p_dst = &i_dst;

	//CvHistogram * hist = cvCreateHist(1,&HistogramBins,CV_HIST_ARRAY,HistogramRange);
	//cvCalcHist(&p_src,hist);
	int *arr_hist = new int[HistogramBins];
	memset(arr_hist, 0, sizeof(int) * HistogramBins);
	for(int i = 0; i < src.rows; ++i)
	{
		for(int j = 0; j < src.cols; ++j)
		{
			if(mark.at<uchar>(i, j) != 0) ++arr_hist[(int)src.at<uchar>(i, j)];
		}
	}

	double maxentropy = -1.0;
	int max_index = -1;
	for(int i=0;i<HistogramBins;i++)
	{
		//double cur_entropy = caculateCurrentEntropy(hist,i,object) + caculateCurrentEntropy(hist,i,back);
		double cur_entropy = caculateCurrentEntropy(arr_hist,i,object) + caculateCurrentEntropy(arr_hist,i,back);
		if(cur_entropy>maxentropy)
		{
			maxentropy = cur_entropy;
			max_index = i;
		}
	}
	threshold(src, dst, (double)max_index, 255, CV_THRESH_BINARY);
	
	//cvReleaseHist(&hist);
	delete [] arr_hist;

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_maxentropy.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}


/*======================================================================*/
/* 迭代法*/
/*======================================================================*/
// nMaxIter：最大迭代次数；nDiffRec：使用给定阀值确定的亮区与暗区平均灰度差异值
int DetectThreshold(IplImage*img, int nMaxIter, int& iDiffRec) //阀值分割：迭代法
{
	//图像信息
	int height = img->height;
	int width = img->width;
	int step = img->widthStep/sizeof(uchar);
	uchar *data = (uchar*)img->imageData;
	iDiffRec =0;
	int F[256]={ 0 }; //直方图数组
	int iTotalGray=0;//灰度值和
	int iTotalPixel =0;//像素数和
	byte bt;//某点的像素值
	uchar iThrehold,iNewThrehold;//阀值、新阀值
	uchar iMaxGrayValue=0,iMinGrayValue=255;//原图像中的最大灰度值和最小灰度	值
	uchar iMeanGrayValue1,iMeanGrayValue2;

	//获取(i,j)的值，存于直方图数组F
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			CvScalar scalar =cvGet2D(img,j,i);
			bt = scalar.val[0];
			if(bt<iMinGrayValue)
			{
				iMinGrayValue = bt;
			}
			if(bt>iMaxGrayValue)
			{
				iMaxGrayValue = bt;
			}
			F[bt]++;
		}
	}
	iThrehold =0;//
	iNewThrehold = (iMinGrayValue+iMaxGrayValue)/2;//初始阀值
	iDiffRec = iMaxGrayValue - iMinGrayValue;
	for(int a=0;(abs(iThrehold-iNewThrehold)>0.5)&&a<nMaxIter;a++)//迭代中止条件
	{
		iThrehold = iNewThrehold;
		//小于当前阀值部分的平均灰度值
		for(int i=iMinGrayValue;i<iThrehold;i++)
		{
			iTotalGray += F[i]*i;//F[]存储图像信息
			iTotalPixel += F[i];
		}
		iMeanGrayValue1 = (uchar)(iTotalGray/iTotalPixel);

		//大于当前阀值部分的平均灰度值
		iTotalPixel =0;
		iTotalGray =0;
		for(int j=iThrehold+1;j<iMaxGrayValue;j++)
		{
			iTotalGray += F[j]*j;//F[]存储图像信息
			iTotalPixel += F[j];
		}
		iMeanGrayValue2 = (uchar)(iTotalGray/iTotalPixel);
		iNewThrehold = (iMeanGrayValue2+iMeanGrayValue1)/2; //新阀值
		iDiffRec = abs(iMeanGrayValue2 - iMeanGrayValue1);
	}

	//cout<<"The Threshold of this Image in imgIteration is:"<<iThrehold<<endl;
	return iThrehold;
}

int CBinary::Iteration(Mat src, Mat& dst, const int nMaxIter)
{
	IplImage i_src = src;
	int iDiffRec;
	int iter_threshold = DetectThreshold(&i_src,nMaxIter,iDiffRec);

	threshold(src, dst, iter_threshold, 255, CV_THRESH_BINARY);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_iteration.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}



int CBinary::Mannal(Mat src, Mat& dst, const int mannan_threshold)
{
	threshold(src, dst, mannan_threshold, 255, CV_THRESH_BINARY);
	return 0;
}


/*int CBinary::DoubleOTSU(Mat src, Mat &dst)
{
	src.copyTo(dst);

	int i, j, k;
	int x, y;

	IplImage i_src = src;
	IplImage *p_src = &i_src;
	uchar* data = (uchar*)p_src->imageData;

	
	const int GrayScale = 256;
	int pixelCount[GrayScale];
	double pixelPro[GrayScale];
	for(i = 0; i < GrayScale; i++)
	{
		pixelCount[i] = 0;
		pixelPro[i] = 0;
	}

	int pixelSum =  p_src->width * p_src->height;

	//统计灰度级中每个像素在整幅图像中的个数
	for(i = 0; i < p_src->height; i++)
	{
		for(j = 0;j < p_src->width;j++)
		{
			pixelCount[(int)data[i *  p_src->width + j]]++;
		}
	}
	
	//计算每个像素在整幅图像中的比例
	for(i = 0; i < GrayScale; i++)
	{
		pixelPro[i] = (double)pixelCount[i] / pixelSum;
	}

	double u = 0;
	for(j = 0; j < GrayScale; ++j)
	{
		u += j * pixelPro[j];
	}
	int jend = GrayScale;

	int start,end;
	for(int i = 0;i < 2; ++i)
	{
		int jMax = 0;
		double deltaMax = -1;
		double uMax;
		for(j = 0; j < jend; ++j)
		{
			double w1 = 0;
			double u1 = 0;
			for(k = 0; k <= j; ++k)
			{
				w1 += pixelPro[k];
				u1 += k * pixelPro[k];
			}
			u1 /= w1;

			double delta = w1 * (u1 - u) * (u1 - u) / (1 - w1);

			if(delta > deltaMax)
			{
				jMax = j;
				deltaMax = delta;
				uMax = u1;
			}
		}

		if(0 == i) end = jMax;
		if(1 == i) start = jMax;
		u = uMax;
		jend = jMax;
	}

	start = 100;
	for(i = 0; i < p_src->height; i++)
	{
		for(j = 0;j < p_src->width;j++)
		{
			if(data[i * p_src->width + j] >= start && data[i * p_src->width + j] <= end) dst.at<uchar>(i , j) = 255;
			else dst.at<uchar>(i , j) = 0;
		}
	}
		
	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_binary_doubleotsu.bmp";
		imwrite(ss.str(), dst);
	}
	return 0;
}*/

int CBinary::DoubleOTSU(Mat src, Mat &dst)
{
	Mat mark;
	Mat dst1;
	src.copyTo(dst1);
	OTSU(src, mark);
	OTSU(dst1, mark, dst);	
	for(int i = 0; i < src.rows; ++i)
	{
		for(int j = 0; j < src.cols; ++j)
		{
			if(!mark.at<uchar>(i, j))   dst.at<uchar>(i, j) = 0;
		}
	}
	return 0;
}

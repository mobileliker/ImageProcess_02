#pragma once

#include "Opencv2.4.8.h"

class CBlur
{
public:
	CBlur(void);
	~CBlur(void);

	inline void setDebug(int _debug){m_debug = _debug;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;


protected:
	
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;

public:

	int Salt(Mat, Mat&, int n = 3000);
	int Gaussian(Mat, Mat&);

	int HomogeneousBlur(Mat, Mat&, int n = 3);
	int iGuassianBlur(Mat, Mat&, int n = 3);
	int iMedianBlur(Mat, Mat&, int n = 3);
	int iBilatrialBlur(Mat, Mat&, int n = 3);
	int iAdaptiveBilateralBlur(Mat, Mat&, int n = 7);
};


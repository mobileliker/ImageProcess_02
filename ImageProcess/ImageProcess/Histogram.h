#pragma once

#include "Opencv2.4.8.h"

class CHistogram
{
public:
	CHistogram(void);
	~CHistogram(void);

	inline void setDebug(int _debug){m_debug = _debug;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;


protected:
	
	//! �Ƿ�������ģʽ��0�رգ���0����
	int m_debug;
public:
	int Show(Mat, Mat&);
	int Hist(Mat src, int * arr_hist);
};


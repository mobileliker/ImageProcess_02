#pragma once

#include "Opencv2.4.8.h"

class CBinary
{
public:
	CBinary(void);
	~CBinary(void);

	inline void setDebug(int _debug){m_debug = _debug;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;


protected:
	
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;
public:
	int Mode(Mat, Mat&);
	int OTSU(Mat, Mat&);
	int MaxEntropy(Mat, Mat&);

	// nMaxIter = 0 means iterate until find the best answer.
	int Iteration(Mat, Mat&, const int nMaxIter = 10);

	int otsuThreshold(Mat src);
	int Mannal(Mat, Mat&, const int);

};


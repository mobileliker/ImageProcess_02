#pragma once

#include "Opencv2.4.8.h"

class CChannel
{
public:
	CChannel(void);
	~CChannel(void);

	inline void setDebug(int _debug){m_debug = _debug;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;


protected:
	
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;
public:
	int Gray(Mat, Mat&);
};


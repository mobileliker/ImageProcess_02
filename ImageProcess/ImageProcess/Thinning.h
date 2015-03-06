#pragma once

#include "Opencv2.4.8.h"

class CThinning
{
public:
	CThinning(void);
	~CThinning(void);

	inline void setDebug(int _debug){m_debug = _debug;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;

protected:
	
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;

public:
	int Rosenfeld(Mat, Mat&);
	int Zhang(Mat, Mat&);
	int Hilditch1(Mat, Mat&);
	int Hilditch2(Mat, Mat&);
	int Pavlidis(Mat, Mat&);
	void Pavlidis2(Mat&, Mat&);
};


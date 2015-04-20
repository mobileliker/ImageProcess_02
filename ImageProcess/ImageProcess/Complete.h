#pragma once

#include "Opencv2.4.8.h"

class CComplete
{
public:
	CComplete(void);
	~CComplete(void);
	
	inline void setDebug(int _debug){m_debug = _debug;}
	inline void setIsolateAlpha(int _isolateAlpha){m_isolateAlpha = _isolateAlpha;}
	inline void setEndpointAlpha(int _endpointAlpha) { m_endpointAlpha = _endpointAlpha; }

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;

	static const int DEFAULT_ISOLATEALPHA = 25;
	static const int DEFAULT_ISOLATEBETA = 50;
	
	static const int DEFAULT_ENDPOINTALPHA = 25;


protected:
	
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;
	int m_isolateAlpha;
	int m_isolateBeta;
	int m_endpointAlpha;

public:
	vector<Point> FindEndPoint(Mat);
	vector<Point> FindIsolatePoint(Mat);
	int CompeleteIsolatePoint(Mat, vector<Point>, Mat&);
	int CompeleteIsolatePoint2(Mat, vector<Point>, Mat&);
	int CompeleteEndPoint(Mat, vector<Point>, Mat&);
	int CompeleteEndPoint2(Mat, vector<Point>, Mat&);

	int Slope(Mat, Point, Point&);
	Mat FindVein(Mat, Point);
	double Cosine(Point, Point, Point);
};


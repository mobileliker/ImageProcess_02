#pragma once

#include "Opencv2.4.8.h"

class CComplete
{
public:
	CComplete(void);
	~CComplete(void);
	
	inline void setDebug(int _debug){m_debug = _debug;}
	inline void setIsolateAlpha(int _isolateAlpha){m_isolateAlpha = _isolateAlpha;}

	static const int DEFAULT_DEBUG = 0;
	static const int DEBUG_OPEN = 1;
	static const int DEBUG_CLOSE = 0;

	static const int DEFAULT_ISOLATEALPHA = 25;

protected:
	
	//! �Ƿ�������ģʽ��0�رգ���0����
	int m_debug;
	int m_isolateAlpha;

public:
	Vector<Point> FindEndPoint(Mat);
	Vector<Point> FindIsolatePoint(Mat);
	int CompeleteIsolatePoint(Mat, Vector<Point>, Mat&);
	int CompeleteEndPoint(Mat, Vector<Point>, Mat&);

};


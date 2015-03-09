#include "StdAfx.h"
#include "Complete.h"


CComplete::CComplete(void): m_debug(DEFAULT_DEBUG), m_isolateAlpha(DEFAULT_ISOLATEALPHA)
{
}


CComplete::~CComplete(void)
{
}

Vector<Point> CComplete::FindIsolatePoint(Mat src)
{
	int i, j, k;
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};
	Vector<Point> isolatePoints;
	
	bitwise_not(src, src);

	for(i = 1; i < src.rows - 1; ++i)
	{
		for(j = 1; j < src.cols - 1; ++j)
		{
			if(src.at<uchar>(i, j) != 0)
			{
				int sum = 0;
				for(k = 0; k < 8; ++k) sum += src.at<uchar>(i + idx_y[k], j + idx_x[k]);
				if(0 == sum)
				{
					Point point;
					point.x = j;
					point.y = i;
					isolatePoints.push_back(point);
				}
			}
		}
	}

	bitwise_not(src, src);

	if(m_debug)
	{
		Mat dst;
		src.copyTo(dst);
		for(Vector<Point>::iterator it = isolatePoints.begin(); it != isolatePoints.end(); ++it)
		{
			dst.at<uchar>(it->y, it->x) = 128;
			for(k = 0; k < 8; ++k) dst.at<uchar>(it->y + idx_y[k], it->x + idx_x[k]) = 128;
		}
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_complete_markisolatepoint.bmp";
		imwrite(ss.str(), dst);
	}

	return isolatePoints;
}

Vector<Point> CComplete::FindEndPoint(Mat src)
{	int i, j, k;
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};
	Vector<Point> endPoints;
	
	bitwise_not(src, src);

	for(i = 1; i < src.rows - 1; ++i)
	{
		for(j = 1; j < src.cols - 1; ++j)
		{
			if(src.at<uchar>(i, j) != 0)
			{
				int sum = 0;
				for(k = 0; k < 8; ++k) sum += src.at<uchar>(i + idx_y[k], j + idx_x[k]);
				if(255 == sum)
				{
					Point point;
					point.x = j;
					point.y = i;
					endPoints.push_back(point);
				}
			}
		}
	}

	bitwise_not(src, src);

	if(m_debug)
	{
		for(Vector<Point>::iterator it = endPoints.begin(); it != endPoints.end(); ++it)
		{
			src.at<uchar>(it->y, it->x) = 128;
			for(k = 0; k < 8; ++k) src.at<uchar>(it->y + idx_y[k], it->x + idx_x[k]) = 128;
		}
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_complete_markendpoint.bmp";
		imwrite(ss.str(), src);
	}

	return endPoints;
}

int CComplete::CompeleteIsolatePoint(Mat src, Vector<Point> points, Mat& dst)
{
	int alpha;
	src.copyTo(dst);

	bitwise_not(dst, dst);

	int idx_sy[] = {1, -1, -1, 1};
	int idx_sx[] = {-1, -1, 1, 1};
	int idx_dx[] = {-1, 0, 1, 0};
	int idx_dy[] = {0, 1, 0, -1};

	int x, y;
	for(Vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		for(alpha = 1; alpha <= m_isolateAlpha; ++alpha)
		{
			for(int k = 0; k < 4; ++k)
			{
				for(int d = 0; d < alpha * 2; ++d)
				{
					int sx = it->x + idx_sx[k] * alpha + idx_dx[k] * d;
					int sy = it->y + idx_sy[k] * alpha + idx_dy[k] * d;
					int value = dst.at<uchar>(sy, sx);
					if(dst.at<uchar>(sy, sx) != 0)
					{
						Point point2;
						point2.x = sx;
						point2.y = sy;
						line(dst, *it, point2, Scalar(255), 1, 8);
						goto end;
					}
				}
			}
			
		}
end:
		if(alpha > m_isolateAlpha) dst.at<uchar>(it->y, it->x) = 0;
	}

	bitwise_not(dst, dst);

	return 0;
}

int CComplete::CompeleteEndPoint(Mat src, Vector<Point> points, Mat& dst)
{
	return 0;
}

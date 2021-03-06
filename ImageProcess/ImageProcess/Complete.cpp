#include "StdAfx.h"
#include "Complete.h"
#include <fstream>

#include <queue>

CComplete::CComplete(void): m_debug(DEFAULT_DEBUG), m_isolateAlpha(DEFAULT_ISOLATEALPHA) , m_isolateBeta(DEFAULT_ISOLATEBETA), m_endpointAlpha(DEFAULT_ENDPOINTALPHA)
{
}


CComplete::~CComplete(void)
{
}

vector<Point> CComplete::FindIsolatePoint(Mat src)
{
	int i, j, k;
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};
	vector<Point> isolatePoints;
	
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
		std::ofstream outfile("tmp/debug_isolatepoint.txt");
		for(vector<Point>::iterator it = isolatePoints.begin(); it != isolatePoints.end(); ++it)
		{
			outfile << "(" << it->x << " , " << it->y << ")" << std::endl;
		}
		outfile.close();


		Mat dst;
		src.copyTo(dst);
		for(vector<Point>::iterator it = isolatePoints.begin(); it != isolatePoints.end(); ++it)
		{
			dst.at<uchar>(it->y, it->x) = 128;
			//for(k = 0; k < 8; ++k) dst.at<uchar>(it->y + idx_y[k], it->x + idx_x[k]) = 128;
			circle(dst, *it, 5, 0, -1);
		}
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_complete_markisolatepoint.bmp";
		imwrite(ss.str(), dst);

	}

	return isolatePoints;
}

vector<Point> CComplete::FindEndPoint(Mat src)
{	int i, j, k;
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};
	vector<Point> endPoints;
	
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
		Mat dst;
		src.copyTo(dst);
		for(vector<Point>::iterator it = endPoints.begin(); it != endPoints.end(); ++it)
		{
			dst.at<uchar>(it->y, it->x) = 128;
			//for(k = 0; k < 8; ++k) dst.at<uchar>(it->y + idx_y[k], it->x + idx_x[k]) = 128;
			circle(dst, *it, 5, 0, -1);
		}
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_complete_markendpoint.bmp";
		imwrite(ss.str(), dst);
	}

	return endPoints;
}

int CComplete::CompeleteIsolatePoint(Mat src, vector<Point> points, Mat& dst)
{
	int alpha;
	src.copyTo(dst);

	bitwise_not(dst, dst);

	int idx_sy[] = {1, -1, -1, 1};
	int idx_sx[] = {-1, -1, 1, 1};
	int idx_dx[] = {-1, 0, 1, 0};
	int idx_dy[] = {0, 1, 0, -1};

	int x, y;
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		for(alpha = 1; alpha <= m_isolateAlpha; ++alpha)
		{
			for(int k = 0; k < 4; ++k)
			{
				for(int d = 0; d < alpha * 2; ++d)
				{
					int sx = it->x + idx_sx[k] * alpha + idx_dx[k] * d;
					int sy = it->y + idx_sy[k] * alpha + idx_dy[k] * d;
					if(sx < 0 || sx >= dst.cols || sy < 0 || sy >= dst.rows) continue;
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

double Distance(Point p1, Point p2)
{
	return std::sqrt(1.0 * (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double Distance2(Point p1, Point p2)
{
	return 1.0 * (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}



int CComplete::CompeleteIsolatePoint2(Mat src, vector<Point> points, Mat& dst)
{

	int alpha;
	src.copyTo(dst);

	bitwise_not(dst, dst);

	int idx_sy[] = {1, -1, -1, 1};
	int idx_sx[] = {-1, -1, 1, 1};
	int idx_dy[] = {-1, 0, 1, 0};
	int idx_dx[] = {0, 1, 0, -1};

	int x, y;
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		vector<Point> dpoints;
		for(alpha = 1; alpha <= m_isolateAlpha; ++alpha)
		{
			for(int k = 0; k < 4; ++k)
			{
				for(int d = 0; d < alpha * 2; ++d)
				{
					int sx = it->x + idx_sx[k] * alpha + idx_dx[k] * d;
					int sy = it->y + idx_sy[k] * alpha + idx_dy[k] * d;
					if(sx < 0 || sx >= dst.cols || sy < 0 || sy >= dst.rows) continue;
					if(dst.at<uchar>(sy, sx) != 0)
					{
						Point point2;
						point2.x = sx;
						point2.y = sy;
						dpoints.push_back(point2);
						//line(dst, *it, point2, Scalar(255), 1, 8);
						//goto end;
					}
				}
			}
			
		}
//end:
		if(0 == dpoints.size()) 
			dst.at<uchar>(it->y, it->x) = 0;
		else
		{

			std::ofstream outfile("tmp/debug_complete_process_findpoint.txt");
			for(vector<Point>::iterator dit = dpoints.begin(); dit != dpoints.end(); ++dit)
			{
				outfile << "(" << dit->x << " , " << dit->y << ")" << std::endl;
			}
			outfile.close();


			double min_d = dst.cols + dst.rows;
			Point min_p;
			for(vector<Point>::iterator dit = dpoints.begin(); dit != dpoints.end(); ++dit)
			{
				double dis = Distance(*it, *dit);
				if(dis < min_d)
				{
					min_d = dis;
					min_p = *dit;
				}
			}
			if(min_d != dst.cols + dst.rows)
			{
				line(dst, *it, min_p, Scalar(255), 1, 8);
			}
		}
	}

	bitwise_not(dst, dst);
	return 0;
}

/*
return -1 孤立点，无法求斜率
return -2 斜率为无穷
return -3 斜率为0
return 0 正常
*/
int CComplete::Slope(Mat src, Point point, Point &dpoint)
{
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};

	int sum_x = 0;
	int sum_y = 0;

	int pre_x = point.x;
	int pre_y = point.y;
	int cur_x = point.x;
	int cur_y = point.y;

	int i;
	for(i = 0; i < 5; ++i)
	{
		int count = 0;
		int sav_x,sav_y;
		for(int k = 0; k < 8; ++k)
		{
			int sx = cur_x + idx_x[k];
			int sy = cur_y + idx_y[k];

			if(sx == pre_x && sy == pre_y) continue;

			if(src.at<uchar>(sy, sx) != 0)
			{
				++count;
				sav_x = sx;
				sav_y = sy;
			}
		}
		if(1 == count)
		{
			sum_x += sav_x;
			sum_y += sav_y;

			pre_x = cur_x;
			pre_y = cur_y;

			cur_x = sav_x;
			cur_y = sav_y;
		}
		else break;
	}

	if(0 == i)
	{
		return -1;
	}
	else
	{
		double avg_x = 1.0 * sum_x / i;
		double avg_y = 1.0 * sum_y / i;

		if(avg_x == point.x * 1.0) return -2;
		else if(avg_y == point.y * 1.0) return -3;
		else
		{
			dpoint.x = (int)avg_x;
			dpoint.y = (int)avg_y;
			return 0;
		}
	}

}

Mat CComplete::FindVein(Mat src, Point point)
{
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};

	std::queue<Point> q_point;
	q_point.push(point);
	vector<Point> dpoints;

	Mat dst = Mat::zeros(src.rows, src.cols, CV_8U);

	while(!q_point.empty())
	{
		Point p = q_point.front();
		q_point.pop();

		for(int k = 0; k < 8; ++k)
		{
			int sx = p.x + idx_x[k];
			int sy = p.y + idx_y[k];

			if(src.at<uchar>(sy, sx) != 0 && dst.at<uchar>(sy, sx) == 0)
			{
				Point p2;
				p2.x = sx;
				p2.y = sy;

				q_point.push(p2);

				dst.at<uchar>(sy, sx) = 255;
			}
		}

	}

	return dst;

}

int CComplete::CompeleteEndPoint(Mat src, vector<Point> points, Mat& dst)
{
	src.copyTo(dst);

	bitwise_not(dst, dst);


	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};
	int i, j;
	int x, y;

	vector< vector<Point>> vv_slopepoints;
	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		x = it->x;
		y = it->y;
		int next_x;
		int next_y;
		int pre_x = -1;
		int pre_y = -1;
		int sum_x = 0;
		int sum_y = 0;
		vector<Point> v_slopepoints;
		for(i = 0; i < m_endpointAlpha; ++i)
		{
			int count = 0;
			for(j = 0; j < 8; ++j)
			{
				if( y + idx_y[j] < 0 || y + idx_y[j] >= dst.rows || x + idx_x[j] < 0 || y + idx_y[j] >= dst.cols) continue;
				if(dst.at<uchar>(y + idx_y[j], x + idx_x[j]) != 0 && (y + idx_y[j] != pre_y || x + idx_x[j] != pre_x))
				{
					++count;
					next_y = y + idx_y[j];
					next_x = x + idx_x[j];
				}
			}
			if(1 == count)
			{
				Point sp;
				sp.x = next_x;
				sp.y = next_y;
				v_slopepoints.push_back(sp);

				sum_x += next_x;
				sum_y += next_y;
				pre_x = x;
				pre_y = y;
				x = next_x;
				y = next_y;
			}
			else break;
		}

		vv_slopepoints.push_back(v_slopepoints);
	}
	
	bitwise_not(dst, dst);

	if(m_debug)
	{
		std::ofstream outfile("tmp/complete_endpoint_slope.txt");
		for(i = 0; i < points.size(); ++i)
		{
			outfile << "(" << points[i].x << "," << points[i].y << "):";
			for(j = 0; j < vv_slopepoints[i].size(); ++j)
			{
				outfile << "(" << vv_slopepoints[i][j].x << "," << vv_slopepoints[i][j].y << "),";
			}
			outfile << std::endl;
		}
		outfile.close();
	}


	return 0;
}


double  CComplete::Cosine(Point p1, Point p2, Point p3)
{
	double a2 = Distance2(p1, p3);
	double b2 = Distance2(p1, p2);
	double c2 = Distance2(p2, p3);

	double res = (b2 + c2 - a2) / (2 * std::sqrt(b2) * std::sqrt(c2));

	return res;
}


int CComplete::CompeleteEndPoint2(Mat src, vector<Point> points, Mat& dst)
{
	int alpha;

	int idx_sy[] = {1, -1, -1, 1};
	int idx_sx[] = {-1, -1, 1, 1};
	int idx_dy[] = {-1, 0, 1, 0};
	int idx_dx[] = {0, 1, 0, -1};

	src.copyTo(dst);

	bitwise_not(dst, dst);

	for(vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		Point dpoint;
		int result = Slope(dst, *it, dpoint);

		Mat mark = FindVein(dst, *it);

		
		vector<Point> dpoints;
		for(alpha = 1; alpha <= m_endpointAlpha; ++alpha)
		{
			for(int k = 0; k < 4; ++k)
			{
				for(int d = 0; d < alpha * 2; ++d)
				{
					int sx = it->x + idx_sx[k] * alpha + idx_dx[k] * d;
					int sy = it->y + idx_sy[k] * alpha + idx_dy[k] * d;
					if(sx < 0 || sx >= dst.cols || sy < 0 || sy >= dst.rows) continue;
					if(dst.at<uchar>(sy, sx) != 0)
					{
						Point point2;
						point2.x = sx;
						point2.y = sy;
						dpoints.push_back(point2);
						//line(dst, *it, point2, Scalar(255), 1, 8);
						//goto end;
					}
				}
			}
			
		}
//end:
		if(0 == dpoints.size()) 
			dst.at<uchar>(it->y, it->x) = 0;
		else
		{

			/*std::ofstream outfile("tmp/debug_complete_process_findpoint.txt");
			for(vector<Point>::iterator dit = dpoints.begin(); dit != dpoints.end(); ++dit)
			{
				outfile << "(" << dit->x << " , " << dit->y << ")" << std::endl;
			}
			outfile.close();*/

			//double beta =  -0.927;
			double beta = - 1.0 / std::sqrt(2.0);
			double max_ang = beta;
			Point min_p;
			for(vector<Point>::iterator dit = dpoints.begin(); dit != dpoints.end(); ++dit)
			{
				if(mark.at<uchar>(dit->y, dit->x) != 0) continue;

				/*double dis = Distance(*it, *dit);
				if(dis < min_d)
				{
					min_d = dis;
					min_p = *dit;
				}*/

				double ang = Cosine(dpoint, *it, *dit);

				if(ang < max_ang)
				{
					max_ang = ang;
					min_p = *dit;
				}


			}
			if(max_ang != beta)
			{
				line(dst, *it, min_p, Scalar(255), 5, 8);
			}
		}
	}
	
	bitwise_not(dst, dst);

	return 0;
}

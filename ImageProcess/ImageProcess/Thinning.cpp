#include "StdAfx.h"
#include "Thinning.h"


CThinning::CThinning(void)
{
}


CThinning::~CThinning(void)
{
}

void thinnerRosenfeld(void *image, unsigned long lx, unsigned long ly)
{
    char *f, *g;
    char n[10];
    char a[5] = {0, -1, 1, 0, 0};
    char b[5] = {0, 0, 0, 1, -1};
    char nrnd, cond, n48, n26, n24, n46, n68, n82, n123, n345, n567, n781;
    short k, shori;
    unsigned long i, j;
    long ii, jj, kk, kk1, kk2, kk3, size;
    size = (long)lx * (long)ly;

    g = (char *)malloc(size);
    if(g==NULL)
    {
        return;
    }

    f = (char *)image;
    for(kk=0l; kk<size; kk++)
    {
        g[kk] = f[kk];
    }

    do
    {
        shori = 0;
        for(k=1; k<=4; k++)
        {
            for(i=1; i<lx-1; i++)
            {
                ii = i + a[k];

                for(j=1; j<ly-1; j++)
                {
                    kk = i*ly + j;

                    if(!f[kk])
                        continue;

                    jj = j + b[k];
                    kk1 = ii*ly + jj;

                    if(f[kk1])
                        continue;

                    kk1 = kk - ly -1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[3] = f[kk1];
                    n[2] = f[kk2];
                    n[1] = f[kk3];
                    kk1 = kk - 1;
                    kk3 = kk + 1;
                    n[4] = f[kk1];
                    n[8] = f[kk3];
                    kk1 = kk + ly - 1;
                    kk2 = kk1 + 1;
                    kk3 = kk2 + 1;
                    n[5] = f[kk1];
                    n[6] = f[kk2];
                    n[7] = f[kk3];

                    nrnd = n[1] + n[2] + n[3] + n[4]
                        +n[5] + n[6] + n[7] + n[8];
                    if(nrnd<=1)
                        continue;

                    cond = 0;
                    n48 = n[4] + n[8];
                    n26 = n[2] + n[6];
                    n24 = n[2] + n[4];
                    n46 = n[4] + n[6];
                    n68 = n[6] + n[8];
                    n82 = n[8] + n[2];
                    n123 = n[1] + n[2] + n[3];
                    n345 = n[3] + n[4] + n[5];
                    n567 = n[5] + n[6] + n[7];
                    n781 = n[7] + n[8] + n[1];

                    if(n[2]==1 && n48==0 && n567>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[6]==1 && n48==0 && n123>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[8]==1 && n26==0 && n345>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[4]==1 && n26==0 && n781>0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[5]==1 && n46==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[7]==1 && n68==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[1]==1 && n82==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    if(n[3]==1 && n24==0)
                    {
                        if(!cond)
                            continue;
                        g[kk] = 0;
                        shori = 1;
                        continue;
                    }

                    cond = 1;
                    if(!cond)
                        continue;
                    g[kk] = 0;
                    shori = 1;
                }
            }

            for(i=0; i<lx; i++)
            {
                for(j=0; j<ly; j++)
                {
                    kk = i*ly + j;
                    f[kk] = g[kk];
                }
            }
        }
    }while(shori);

    free(g);
} 

bool iRosenfeld(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	LPSTR lpSrc;
	int i,j;

	//建立存储区存放2值矩阵
	BYTE *image = (BYTE*)malloc(lWidth*lHeight*sizeof(BYTE));

	//给2值矩阵赋值
	for(i=0;i<lHeight;i++)
	{
		for(j=0;j<lWidth;j++)
	{
		  lpSrc=lpDIBBits+i*lWidth+j;
    
		  if(*lpSrc==0)
		  image[i*lWidth+j]=1;

	  else
			 image[i*lWidth+j]=0;
	}
	}
	   thinnerRosenfeld(image,lHeight,lWidth);

	   //将结果赋值到原图像中

	   for(i=0;i<lHeight;i++)
	   {
		 for(j=0;j<lWidth;j++)
	 {
	   lpSrc=lpDIBBits+i*lWidth+j;

		   if(image[i*lWidth+j]==1)
	   *lpSrc=(BYTE)0;

	   else
		   *lpSrc=(BYTE)255;
	 }
   
	   }


	 //清空内存
	   free(image);
	   ::GlobalUnlock ((HGLOBAL)lpDIBBits);

	return true;
}


int CThinning::Rosenfeld(Mat src, Mat &dst)
{	
	src.copyTo(dst);
	IplImage i_src = src;
	IplImage i_dst = dst;
	IplImage *p_src = &i_src;
	IplImage *p_dst = &i_dst;

	
	LPSTR data = p_dst->imageData;

	iRosenfeld(data, dst.cols, dst.rows);

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_thinning_rosenfeld.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}


void iZhang(BYTE *imgBuf,int width,int height,int interator)
{
	BYTE *tempBuf = new BYTE[width * height];

	int x = 0,y = 0;
	int i = 0;
	int flag = 0;
	
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};


	while(interator--)
	{
		BYTE p[8];
		int count = 0;

		flag = 0;

//step 1:
		//copy to tempBuf
		for(y = 0; y < height; ++y)
		{
			for(x = 0; x < width; ++x)
			{
				tempBuf[y * width + x] = imgBuf[y * width + x];
			}
		}

		for(y = 1; y < height - 1; ++y)
		{
			for(x = 1; x < width - 1; ++x)
			{
				if(tempBuf[y * width + x] == 1)
				{
					for(i = 0; i < 8; ++i) p[i] = tempBuf[(y + idx_y[i]) * width + (x + idx_x[i])];

					//2 <= p0 + p2 + .. + p7 <= 6
					count = 0;
					for(i = 0; i < 8; ++i) count += p[i];
					if(count < 2 || count > 6) continue;

					//p0->p8 01
					count = 0;
					for(i = 0; i < 8; ++i)
					{
						if(1 == (p[(i + 1) % 8] - p[i])) ++count;
					}
					if(count != 1) continue;

					//p0 * p2 * p4 = 0 && p2 * p4 * p6 = 0
					if((0 == p[0] * p[2] * p[4]) && (0 == p[2] * p[4] * p[6]))
					{
						flag = 1;
						imgBuf[y * width + x] = 0;
					}

				}
			}
		}

//step 2:
		//copy to tempBuf
		for(y = 0; y < height; ++y)
		{
			for(x = 0; x < width; ++x)
			{
				tempBuf[y * width + x] = imgBuf[y * width + x];
			}
		}

		for(y = 1; y < height - 1; ++y)
		{
			for(x = 1; x < width - 1; ++x)
			{
				if(tempBuf[y * width + x] == 1)
				{
					for(i = 0; i < 8; ++i) p[i] = tempBuf[(y + idx_y[i]) * width + (x + idx_x[i])];

					//2 <= p0 + p2 + .. + p7 <= 6
					count = 0;
					for(i = 0; i < 8; ++i) count += p[i];
					if(count < 2 || count > 6) continue;

					//p0->p8 01
					count = 0;
					for(i = 0; i < 8; ++i)
					{
						if(1 == (p[(i + 1) % 8] - p[i])) ++count;
					}
					if(count != 1) continue;

					//p0 * p2 * p6 = 0 && p0 * p4 * p6 = 0
					if((0 == p[0] * p[2] * p[6]) && (0 == p[0] * p[4] * p[6]))
					{
						flag = 1;
						imgBuf[y * width + x] = 0;
					}


				}
			}
		}


		if(flag == 0) break;
	}

	delete [] tempBuf;

}

int CThinning::Zhang(Mat src, Mat &dst)
{
	src.copyTo(dst);
	BYTE *imgBuf  = new BYTE[src.rows * src.cols];
	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(src.at<uchar>(y,x) == 0) imgBuf[y * src.cols + x] = 1;
			else imgBuf[y * src.cols + x] = 0;
		}
	}
	
	iZhang(imgBuf, src.cols, src.rows, 100);

	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(0 == imgBuf[y * src.cols + x]) dst.at<uchar>(y,x) = 255;
			else dst.at<uchar>(y,x) = 0;
		}
	}
	
	delete [] imgBuf;

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_thinning_zhang.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}


int nc8(BYTE b[])
{
	BYTE d[8];
	int i;
	int num_d = 8;
	for(i = 0; i < num_d; ++i) { if(abs(b[i]) == 1) {d[i] = 1;} else {d[i] = 0;} }
	int count = 0;
	for(i = 0; i < num_d; i += 2)
	{
		count += (d[i] - d[i] * d[(i + 1) % num_d] * d[(i + 2) % num_d]);
	}
	return count;
}
void ThinnerHilditch1(BYTE *imgBuf,int width,int height,int interator)
{

	int x,y;
	int i;
	int flag;
	
	int idx_x[] = {1,1,0,-1,-1,-1,0,1};
	int idx_y[] = {0,-1,-1,-1,0,1,1,1};
	int num_d = 8;


	while(interator--)
	{
		flag = 0;

		BYTE b[8],d[8];

		int count;
		for(y = 1; y < height - 1; ++y)
		{
			for(x = 1; x < width -1; ++x)
			{
				if(imgBuf[y * width + x] == 255)
				{
					for(i = 0; i < num_d; ++i)
					{
						if(imgBuf[(y + idx_y[i]) * width + x + idx_x[i]] == 255) b[i] = 1;
						else if(imgBuf[(y + idx_y[i]) * width + x + idx_x[i]] == 128) b[i] = -1;
						else b[i] = 0;
					}

					//2. 1-abs(b0) + 1 – abs(b2) + 1 – abs(b4) + 1 – abs(b6) >= 1
					count = 0;
					for(i = 0; i < num_d; i += 2) count += (1 - abs(b[i]));
					if(count < 1) continue;
					//if(((1 - abs(b[0])) + (1 - abs(b[2])) + (1 - abs(b[4])) + (1 - abs(b[6])) ) < 1) continue;

					//3. abs(b0)+…+abs(b7)>=2
					count = 0;
					for(i = 0; i < num_d; ++i) count += abs(b[i]);
					if(count < 2) continue;

					//4. 统计b1到b8等于1的数量，该数量值必须大于1，该条件表示不能删除端点
					count = 0;
					for(i = 0; i < num_d; ++i) if(b[i] == 1) count++;
					if(count < 1) continue;

					//5.连通性检测，使用下面的公式：
					//首先根据当前像素周围3*3域的值，记录d[9]数组，如果b[i]等于0，则d[i]=0， 
					//否则d[i]=1，最后计算 d1-d1*d2*d3+d3-d3*d4*d5+d5-d5*d6*d7+d7-d7*d8*d1是否为1，
					//为1则满足连通性，可以删除。
					if(nc8(b) != 1) continue;



					//6
					count = 0;
					for(i = 0; i < num_d; ++i)
					{
						if(b[i] != -1) count++;
						else
						{
							int temp = b[i];
							b[i] = 0;
							if(nc8(b) == 1) count++;
							b[i] = temp;
						}
					}
					if(count != 8) continue;


					imgBuf[y * width + x] = 128;
					flag++;

				}
			}
		}

		if(flag)
		{
			for(y = 0; y < height; ++y)
			{
				for(x = 0; x < width; ++x)
				{
					if(imgBuf[y * width + x] == 128) imgBuf[y * width + x] = 0;
				}
			}
		}
		else break;
	}


}

int CThinning::Hilditch1(Mat src, Mat &dst)
{
	src.copyTo(dst);
	BYTE *imgBuf  = new BYTE[src.rows * src.cols];
	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(src.at<uchar>(y,x) == 0) imgBuf[y * src.cols + x] = 1;
			else imgBuf[y * src.cols + x] = 0;
		}
	}
	
	ThinnerHilditch1(imgBuf, src.cols, src.rows, 100);

	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(0 == imgBuf[y * src.cols + x]) dst.at<uchar>(y,x) = 255;
			else dst.at<uchar>(y,x) = 0;
		}
	}
	
	delete [] imgBuf;

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_thinning_zhang.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}



void ThinnerHilditch2(BYTE *imgBuf,int width,int height,int interator)
{
	BYTE *tempBuf = new BYTE[width * height];

	int x = 0,y = 0;
	int i = 0;
	int flag = 0;
	
	int idx_x[] = {0,1,1,1,0,-1,-1,-1};
	int idx_y[] = {-1,-1,0,1,1,1,0,-1};


	while(interator--)
	{
		BYTE p[8];
		int count = 0;

		flag = 0;

		for(y = 0; y < height; ++y)
		{
			for(x = 0; x < width; ++x)
			{
				tempBuf[y * width + x] = imgBuf[y * width + x];
			}
		}

		for(y = 2; y < height - 2; ++y)
		{
			for(x = 2; x < width - 2; ++x)
			{
				if(tempBuf[y * width + x] == 1)
				{
					for(i = 0; i < 8; ++i) p[i] = tempBuf[(y + idx_y[i]) * width + (x + idx_x[i])];

					//2 <= p0 + p2 + .. + p7 <= 6
					count = 0;
					for(i = 0; i < 8; ++i) count += p[i];
					if(count < 2 || count > 6) continue;

					//p0->p8 01
					count = 0;
					for(i = 0; i < 8; ++i)
					{
						if(1 == (p[(i + 1) % 8] - p[i])) ++count;
					}
					if(count != 1) continue;

					BYTE b[8];
					int xx,yy;

					//p0.p2.p6 = 0 or A(p0)!=1
					xx = x + idx_x[0];
					yy = y + idx_y[0];
					for(i = 0; i < 8; ++i) b[i] = tempBuf[(yy + idx_y[i]) * width + (xx + idx_x[i])];
					count = 0;
					for(i = 0; i < 8; ++i)
					{
						if(1 == b[(i + 1) % 8] - b[i]) count++;
					}
					if(!((p[0] * p[2] * p[6] == 0) || (count != 1))) continue;

					//p0.p2.p4 = 0 or A(p2)!=1
					xx = x + idx_x[2];
					yy = y + idx_y[2];
					for(i = 0; i < 8; ++i) b[i] = tempBuf[(yy + idx_y[i]) * width + (xx + idx_x[i])];
					count = 0;
					for(i = 0; i < 8; ++i)
					{
						if(1 == b[(i + 1) % 8] - b[i]) count++;
					}
					if(!((p[0] * p[2] * p[4]) == 0 || (count != 1))) continue;


					imgBuf[y * width + x] = 0;
					flag++;
				}
			}
		}

		if(flag == 0) break;
	}

	delete [] tempBuf;

}


int CThinning::Hilditch2(Mat src, Mat &dst)
{
	src.copyTo(dst);
	BYTE *imgBuf  = new BYTE[src.rows * src.cols];
	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(src.at<uchar>(y,x) == 0) imgBuf[y * src.cols + x] = 1;
			else imgBuf[y * src.cols + x] = 0;
		}
	}
	
	ThinnerHilditch2(imgBuf, src.cols, src.rows, 100);

	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(0 == imgBuf[y * src.cols + x]) dst.at<uchar>(y,x) = 255;
			else dst.at<uchar>(y,x) = 0;
		}
	}
	
	delete [] imgBuf;

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_thinning_hilditch2.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}


//Pavlidis细化算法
//功能：对图象进行细化
//参数：image：代表图象的一维数组
//      lx：图象宽度
//      ly：图象高度
//      无返回值
void ThinnerPavlidis(void *image, unsigned long lx, unsigned long ly)
{
    char erase, n[8];
    char *f;
    unsigned char bdr1,bdr2,bdr4,bdr5;
    short c,k,b;
    unsigned long i,j;
    long kk,kk1,kk2,kk3;
    f = (char*)image;

    for(i=1; i<lx-1; i++)
    {
        for(j=1; j<ly-1; j++)
        {
            kk = i*ly + j;
            if(f[kk])
                f[kk] = 1;
        }
    }

    for(i=0, kk1=0, kk2=ly-1; i<lx; i++, kk1+=ly, kk2+=ly)
    {
        f[kk1]=0;
        f[kk2]=0;
    }

    for(j=0, kk=(lx-1)*ly; j<ly; j++,kk++)
    {
        f[j]=0;
        f[kk]=0;
    }

    c=5;
    erase =1;
    while(erase)
    {
        c++;
        for(i=1; i<lx-1; i++)
        {
            for(j=1; j<ly-1; j++)
            {
                kk=i*ly+j;
                if(f[kk]!=1)
                    continue;

                kk1 = kk-ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[3] = f[kk1];
                n[2] = f[kk2];
                n[1] = f[kk3];
                kk1 = kk - 1;
                kk3 = kk + 1;
                n[4] = f[kk1];
                n[0] = f[kk3];
                kk1 = kk + ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[5] = f[kk1];
                n[6] = f[kk2];
                n[7] = f[kk3];

                bdr1 =0;
                for(k=0; k<8; k++)
                {
                    if(n[k]>=1)
                        bdr1|=0x80>>k;
                }

                if((bdr1&0252)== 0252)
                    continue;
                f[kk] = 2;
                b=0;

                for(k=0; k<=7; k++)
                {
                    b+=bdr1&(0x80>>k);
                }

                if(b<=1)
                    f[kk]=3;

                if((bdr1&0160)!=0&&(bdr1&07)!=0&&(bdr1&0210)==0)
                    f[kk]=3;
                else if((bdr1&&0301)!=0&&(bdr1&034)!=0&&(bdr1&042)==0)
                    f[kk]=3;
                else if((bdr1&0202)==0 && (bdr1&01)!=0)
                    f[kk]=3;
                else if((bdr1&0240)==0 && (bdr1&0100)!=0)
                    f[kk]=3;
                else if((bdr1&050)==0 && (bdr1&020)!=0)
                    f[kk]=3;
                else if((bdr1&012)==0 && (bdr1&04)!=0)
                    f[kk]=3;
            }
        }

        for(i=1; i<lx-1; i++)
        {
            for(j=1; j<ly-1; j++)
            {
                kk = i*ly + j;
                if(!f[kk])
                    continue;

                kk1 = kk - ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[3] = f[kk1];
                n[2] = f[kk2];
                n[1] = f[kk3];
                kk1 = kk - 1;
                kk2 = kk + 1;
                n[4] = f[kk1];
                n[0] = f[kk3];
                kk1 = kk + ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[5] = f[kk1];
                n[6] = f[kk2];
                n[7] = f[kk3];
                bdr1 = bdr2 =0;

                for(k=0; k<=7; k++)
                {
                    if(n[k]>=1)
                        bdr1|=0x80>>k;
                    if(n[k]>=2)
                        bdr2|=0x80>>k;
                }

                if(bdr1==bdr2)
                {
                    f[kk] = 4;
                    continue;
                }

                if(f[kk]!=2)
                    continue;

                if((bdr2&0200)!=0 && (bdr1&010)==0 &&
                    ((bdr1&0100)!=0 &&(bdr1&001)!=0 ||
                    ((bdr1&0100)!=0 ||(bdr1 & 001)!=0) &&
                    (bdr1&060)!=0 &&(bdr1&06)!=0))
                {
                    f[kk] = 4;
                }

                else if((bdr2&040)!=0 && (bdr1&02)==0 &&
                    ((bdr1&020)!=0 && (bdr1&0100)!=0 ||
                    ((bdr1&020)!=0 || (bdr1&0100)!=0) &&
                    (bdr1&014)!=0 && (bdr1&0201)!=0))
                {
                    f[kk] = 4;
                }

                else if((bdr2&010)!=0 && (bdr1&0200)==0 &&
                    ((bdr1&04)!=0 && (bdr1&020)!=0 ||
                    ((bdr1&04)!=0 || (bdr1&020)!=0) &&
                    (bdr1&03)!=0 && (bdr1&0140)!=0))
                {
                    f[kk] = 4;
                }

                else if((bdr2&02)!=0 && (bdr1&040)==0 &&
                    ((bdr1&01)!=0 && (bdr1&04)!=0 ||
                    ((bdr1&01)!=0 || (bdr1&04)!=0) &&
                    (bdr1&0300)!=0 && (bdr1&030)!=0))
                {
                    f[kk] = 4;
                }
            }
        }

        for(i=1; i<lx-1; i++)
        {
            for(j=1; j<ly-1; j++)
            {
                kk = i*ly + j;
                if(f[kk]!=2)
                    continue;
                kk1 = kk - ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[3] = f[kk1];
                n[2] = f[kk2];
                n[1] = f[kk3];
                kk1 = kk - 1;
                kk2 = kk + 1;
                n[4] = f[kk1];
                n[0] = f[kk3];
                kk1 = kk + ly -1;
                kk2 = kk1 + 1;
                kk3 = kk2 + 1;
                n[5] = f[kk1];
                n[6] = f[kk2];
                n[7] = f[kk3];
                bdr4 = bdr5 =0;
                for(k=0; k<=7; k++)
                {
                    if(n[k]>=4)
                        bdr4|=0x80>>k;
                    if(n[k]>=5)
                        bdr5|=0x80>>k;
                }
                if((bdr4&010) == 0)
                {
                    f[kk] = 5;
                    continue;
                }
                if((bdr4&040) == 0 && bdr5 ==0)
                {
                    f[kk] = 5;
                    continue;
                }
                if(f[kk]==3||f[kk]==4)
                    f[kk] = c;
            }
        }

        erase = 0;
        for(i=1; i<lx-1; i++)
        {
            for(j=1; j<ly-1; j++)
            {
                kk = i*ly +j;
                if(f[kk]==2||f[kk] == 5)
                {
                    erase = 1;
                    f[kk] = 0;
                }
            }
        }
    }
}

int CThinning::Pavlidis(Mat src, Mat &dst)
{
	src.copyTo(dst);
	BYTE *imgBuf  = new BYTE[src.rows * src.cols];
	
	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(src.at<uchar>(y,x) == 0) imgBuf[y * src.cols + x] = 1;
			else imgBuf[y * src.cols + x] = 0;
		}
	}
	
	ThinnerPavlidis(imgBuf, src.cols, src.rows);

	for(int y = 0; y < src.rows; ++y)
	{
		for(int x = 0; x < src.cols; ++x)
		{
			if(0 == imgBuf[y * src.cols + x]) dst.at<uchar>(y,x) = 255;
			else dst.at<uchar>(y,x) = 0;
		}
	}
	
	delete [] imgBuf;

	if(m_debug)
	{
		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "tmp/debug_thinning_zhang.bmp";
		imwrite(ss.str(), dst);
	}

	return 0;
}

void CThinning::Pavlidis2(Mat& src, Mat& dst)
{
	src.copyTo(dst);
	bitwise_not(dst, dst);

    char erase, n[8];
    unsigned char bdr1,bdr2,bdr4,bdr5;
    short k,b;
    unsigned long i,j;


    int width, height;
    width=dst.cols;
    height= dst.rows;

    //把不能于0的值转化为1，便于后面处理
    for(i=0; i< height; i++)
	{
        for(j=0; j<width; j++)
		{
            if(dst.at<uchar>(i,j)!=0)
			{
                dst.at<uchar>(i,j) = 1;
			}
            //图像边框像素值为0
            if(i==0||i==(height-1)||j==0||j==(width-1))
                dst.at<uchar>(i,j) = 0;
		}
	}

    erase =1;
    width = width - 1;
    height = height - 1;
    uchar* img;
    int step = dst.step;
    while(erase) 
	{

        img = dst.data;
        //第一个循环，取得前景轮廓，轮廓用2表示
        for(i=1; i< height; i++)
		{
            img += step;
            for(j=1; j < width; j++)
			{
                uchar* p= img+j;


                if(p[0]!= 1)
                    continue;

                n[0]=p[1];
                n[1]=p[-step+1];
                n[2]=p[-step];
                n[3]=p[-step-1];
                n[4]=p[-1];
                n[5]=p[step-1];
                n[6]=p[step];
                n[7]=p[step+1];

                //bdr1是2进制表示的p0...p6p7排列，10000011,p0=1,p6=p7=1
                bdr1 =0;
                for(k=0; k<8; k++)
				{
                    if(n[k]>=1)
                        bdr1|=0x80>>k;
				}
                //内部点,p0, p2, p4, p6都是为1, 非边界点，所以继续循环
                //0xaa 10101010
                //  0   1   0   
                //  1         1
                //   0   1    0

                if((bdr1&0xaa)== 0xaa)
                    continue;
                //不是内部点，则是边界点，对于边界点，我们标记为2，是轮廓
                p[0] = 2;

                b=0;

                for(k=0; k<=7; k++)
				{
                    b+=bdr1&(0x80>>k);
				}
                //在边界点中，等于1，则是端点，等于0，则是孤立点，此时标记3
                if(b<=1 )
                    p[0] = 3;

                //此条件说明p点是中间点，如果移去会引起断裂
                // 0x70        0x7         0x88      0xc1        0x1c      0x22      0x82     0x1      0xa0     0x40     0x28    0x10       0xa      0x4
                // 0 0 0     0  1  1     1  0   0    0   0   0    1  1  0    0   0   1  0  0  1  0 0 0    0  0  0   0 0 0    1  0  0   0  0  0  1  0  1   0 1 0
                // 1    0     0      1     0       0    0        1    1      0    0        0  0      0  0    1    0      0   0    0    0      0   1      0  0     0    0    0
                // 1 1 0     0  0  0     0  0   1    0   1   1    0  0  0    1   0   1  0  0  1  0 0 0    1  0  1   0 1 0    1  0  0   0  0  0  0  0  0   0 0 0
                if((bdr1&0x70)!=0&&(bdr1&0x7)!=0&&(bdr1&0x88)==0)
                    p[0] = 3;
                else if((bdr1&&0xc1)!=0&&(bdr1&0x1c)!=0&&(bdr1&0x22)==0)
                    p[0] = 3;  
                else if((bdr1&0x82)==0 && (bdr1&0x1)!=0)
                    p[0] = 3; 
                else if((bdr1&0xa0)==0 && (bdr1&0x40)!=0)
                    p[0] = 3; 
                else if((bdr1&0x28)==0 && (bdr1&0x10)!=0)
                    p[0] = 3; 
                else if((bdr1&0xa)==0 && (bdr1&0x4)!=0)
                    p[0] = 3; 

			}
		}
        //printf("------------------------------\n");
        //PrintMat(dst);
        img = dst.data;
        for(i=1; i<height; i++)
		{
            img += step;
            for(j=1; j<width; j++)
			{
                uchar* p= img+j;

                if(p[0]== 0)
                    continue;

                n[0]=p[1];
                n[1]=p[-step+1];
                n[2]=p[-step];
                n[3]=p[-step-1];
                n[4]=p[-1];
                n[5]=p[step-1];
                n[6]=p[step];
                n[7]=p[step+1];

                bdr1 = bdr2 =0;

                //bdr1是2进制表示的当前点p的8邻域连通情况，hdr2是当前点周围轮廓点的连接情况
                for(k=0; k<=7; k++)
				{
                    if(n[k]>=1)
                        bdr1|=0x80>>k;
                    if(n[k]>=2)
                        bdr2|=0x80>>k;
				}

                //相等，就是周围全是值为2的像素，继续
                if(bdr1==bdr2)
				{
                    p[0] = 4; 
                    continue;
				}

                //p0不为2，继续
                if(p[0]!=2) continue;
                //=4都是不可删除的轮廓点
                //     0x80       0xa     0x40        0x1      0x30   0x6
                //   0 0 0      1  0 1    0  0  0    0  0  0   0 0 0   0 1 1
                //   0    0      0     0    0      0    0      1   1    0   0    0
                //   0 0 1      0  0 0    0  1  0    0  0  0   1 0 0   0 0 0

                if(   
                    (bdr2&0x80)!=0 && (bdr1&0xa)==0 &&
                //    ((bdr1&0x40)!=0 &&(bdr1&0x1)!=0 ||     ((bdr1&0x40)!=0 ||(bdr1 & 0x1)!=0) &&(bdr1&0x30)!=0 &&(bdr1&0x6)!=0 )
                    (    ((bdr1&0x40)!=0 ||(bdr1 & 0x1)!=0) &&(bdr1&0x30)!=0 &&(bdr1&0x6)!=0 )
                    )
				{
                    p[0]= 4; 
				}
                //
                else if((bdr2&0x20)!=0 && (bdr1&0x2)==0 &&
                    //((bdr1&0x10)!=0 && (bdr1&0x40)!=0 || ((bdr1&0x10)!=0 || (bdr1&0x40)!=0) &&    (bdr1&0xc)!=0 && (bdr1&0x81)!=0)
                    ( ((bdr1&0x10)!=0 || (bdr1&0x40)!=0) &&    (bdr1&0xc)!=0 && (bdr1&0x81)!=0)
                    )
				{
                    p[0]= 4;
				}

                else if((bdr2&0x8)!=0 && (bdr1&0x80)==0 &&
                    //((bdr1&0x4)!=0 && (bdr1&0x10)!=0 || ((bdr1&0x4)!=0 || (bdr1&0x10)!=0) &&(bdr1&0x3)!=0 && (bdr1&0x60)!=0)
                    ( ((bdr1&0x4)!=0 || (bdr1&0x10)!=0) &&(bdr1&0x3)!=0 && (bdr1&0x60)!=0)
                    )
				{
                    p[0]= 4;
				}

                else if((bdr2&0x2)!=0 && (bdr1&0x20)==0 &&
                    //((bdr1&0x1)!=0 && (bdr1&0x4)!=0 ||((bdr1&0x1)!=0 || (bdr1&0x4)!=0) &&(bdr1&0xc0)!=0 && (bdr1&0x18)!=0)
                    (((bdr1&0x1)!=0 || (bdr1&0x4)!=0) &&(bdr1&0xc0)!=0 && (bdr1&0x18)!=0)
                    )
				{
                    p[0]= 4;
				}
			}
		}
        //printf("------------------------------\n");
        //PrintMat(dst);
        img = dst.data;
        for(i=1; i<height; i++)
		{
            img += step;
            for(j=1; j<width; j++)
			{
                uchar* p= img+j;

                if(p[0]!= 2)
                    continue;


                n[0]=p[1];
                n[1]=p[-step+1];
                n[2]=p[-step];
                n[3]=p[-step-1];
                n[4]=p[-1];
                n[5]=p[step-1];
                n[6]=p[step];
                n[7]=p[step+1];

                bdr4 = bdr5 =0;
                for(k=0; k<=7; k++)
				{
                    if(n[k]>=4)
                        bdr4|=0x80>>k;
                    if(n[k]>=5)
                        bdr5|=0x80>>k;
				}
                //值为4和5的像素
                if((bdr4&0x8) == 0)
				{
                    p[0]=5;
                    continue;
				}
                if((bdr4&0x20) == 0 && bdr5 ==0)
				{
                    p[0]=5;
                    continue;
				}

			}
		}
        erase = 0;
        //printf("------------------------------\n");
        //PrintMat(dst);
        img = dst.data;
        for(i=1; i<height; i++)
		{
            img += step;
            for(j=1; j<width; j++)
			{
                uchar* p= img+j;
                if(p[0]==2||p[0]==5)
				{
                    erase = 1;
                    p[0] = 0;
				}
			}
		}
        //printf("------------------------------\n");
        //PrintMat(dst);
        //printf("------------------------\n");
	}

	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			if(dst.at<uchar>(i,j) != 0) dst.at<uchar>(i,j) = 255;
		}
	}
	bitwise_not(dst, dst);

}


void CThinning::Index(Mat& src, Mat& dst)
    {

	src.copyTo(dst);
	bitwise_not(dst, dst);

    //    P0 P1 P2
    //    P7    P3
    //    P6 P5 P4
    unsigned char deletemark[256] = {
        0,0,0,0,0,0,0,1,    0,0,1,1,0,0,1,1,
        0,0,0,0,0,0,0,0,    0,0,1,1,1,0,1,1,
        0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
        0,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
        0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,    1,0,0,0,1,0,1,1,
        1,0,0,0,0,0,0,0,    1,0,1,1,1,0,1,1,
        0,0,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
        0,0,0,0,0,0,0,0,    0,0,0,1,0,0,1,1,
        1,1,0,1,0,0,0,1,    0,0,0,0,0,0,0,0,
        1,1,0,1,0,0,0,1,    1,1,0,0,1,0,0,0,
        0,1,1,1,0,0,1,1,    0,0,0,1,0,0,1,1,
        0,0,0,0,0,0,0,0,    0,0,0,0,0,1,1,1,
        1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0,
        1,1,1,1,0,0,1,1,    1,1,0,0,1,1,0,0
        };//索引
    int i, j;
    int width, height;
    //之所以减1，是方便处理8邻域，防止越界
    width = src.cols -1;
    height = src.rows -1;
    int step = src.step;
    int  p0, p1, p2,p3,p4,p5,p6,p7;
    uchar* img;
    bool ifEnd;
    bool border = false; //交换删除的次序，防止从一边细化
    while(1)
        {

        border = !border;
        img = dst.data;
        for(i = 1; i < height; i++)
            {
            img += step;
            for(j =1; j<width; j++)
                {
                uchar* p = img + j;
                //如果p点是背景点,继续循环
                if(p[0]==0) continue;
                p0 = p[-step-1]>0?1:0;
                p1 = p[-step]>0?1:0;
                p2 = p[-step+1]>0?1:0;
                p3 = p[1]>0?1:0;
                p4 = p[step+1]>0?1:0;
                p5 = p[step]>0?1:0;
                p6 = p[step-1]>0?1:0;
                p7 = p[-1]>0?1:0;

                //如果sum等于0，则不是内部点，是轮廓点，设置其像素值为2
                int sum;
                sum =  p0 & p1 & p2 & p3 & p4 & p5 & p6 & p7;

                //判断是否是邻接点或孤立点,0,1分别对于那个孤立点和端点
                if(sum==0)
                    {
                    dst.at<uchar>(i,j) = 4; //满足删除条件，设置当前像素为0
                    }

                }
            }
        //printf("\n");
        //PrintMat(dst);
        //执行删除操作
        ifEnd = false;

        img = dst.data;
        for(i = 1; i < height; i++)
            {
            img += step;
            for(j =1; j<width; j+=3)
                {
                uchar* p = img + j;
                //如果p点是背景点,继续循环
                if(p[0]!=4) continue;
                p0 = p[-step-1]>0?1:0;
                p1 = p[-step]>0?1:0;
                p2 = p[-step+1]>0?1:0;
                p3 = p[1]>0?1:0;
                p4 = p[step+1]>0?1:0;
                p5 = p[step]>0?1:0;
                p6 = p[step-1]>0?1:0;
                p7 = p[-1]>0?1:0;

                p1 = p1<<1;
                p2 = p2<<2;
                p3 = p3 <<3;
                p4 = p4<<4;
                p5 = p5<<5;
                p6 = p6 <<6;
                p7 = p7 << 7;

                //求的8邻域在索引表中的索引
                int sum;
                sum = p0 | p1 | p2 | p3 | p4 | p5 | p6 | p7;

                //判断是否是邻接点或孤立点,0,1分别对于那个孤立点和端点
                if(deletemark[sum] == 1)
                    {
                    dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                    ifEnd = true;
                    }

                }
            }

        img = dst.data;
        for(i = 1; i < height; i++)
            {
            img += step;
            for(j =2; j<width; j+=3)
                {
                uchar* p = img + j;
                //如果p点是背景点,继续循环
                if(p[0]!=4) continue;
                p0 = p[-step-1]>0?1:0;
                p1 = p[-step]>0?1:0;
                p2 = p[-step+1]>0?1:0;
                p3 = p[1]>0?1:0;
                p4 = p[step+1]>0?1:0;
                p5 = p[step]>0?1:0;
                p6 = p[step-1]>0?1:0;
                p7 = p[-1]>0?1:0;

                p1 = p1<<1;
                p2 = p2<<2;
                p3 = p3 <<3;
                p4 = p4<<4;
                p5 = p5<<5;
                p6 = p6 <<6;
                p7 = p7 << 7;

                //求的8邻域在索引表中的索引
                int sum;
                sum = p0 | p1 | p2 | p3 | p4 | p5 | p6 | p7;

                //判断是否是邻接点或孤立点,0,1分别对于那个孤立点和端点
                if(deletemark[sum] == 1)
                    {
                    dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                    ifEnd = true;
                    }

                }
            }

        img = dst.data;
        for(i = 1; i < height; i++)
            {
            img += step;
            for(j =3; j<width; j+=3)
                {
                uchar* p = img + j;
                //如果p点是背景点,继续循环
                if(p[0]!=4) continue;
                p0 = p[-step-1]>0?1:0;
                p1 = p[-step]>0?1:0;
                p2 = p[-step+1]>0?1:0;
                p3 = p[1]>0?1:0;
                p4 = p[step+1]>0?1:0;
                p5 = p[step]>0?1:0;
                p6 = p[step-1]>0?1:0;
                p7 = p[-1]>0?1:0;

                p1 = p1<<1;
                p2 = p2<<2;
                p3 = p3 <<3;
                p4 = p4<<4;
                p5 = p5<<5;
                p6 = p6 <<6;
                p7 = p7 << 7;

                //求的8邻域在索引表中的索引
                int sum;
                sum = p0 | p1 | p2 | p3 | p4 | p5 | p6 | p7;

                //判断是否是邻接点或孤立点,0,1分别对于那个孤立点和端点
                if(deletemark[sum] == 1)
                    {
                    dst.at<uchar>(i,j) = 0; //满足删除条件，设置当前像素为0
                    ifEnd = true;
                    }

                }
            }

        //printf("\n");
        //PrintMat(dst);
        //printf("\n");

        //已经没有可以细化的像素了，则退出迭代
        if(!ifEnd) break;
        }

	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			if(dst.at<uchar>(i,j) != 0) dst.at<uchar>(i,j) = 255;
		}
	}
	bitwise_not(dst, dst);

    }


void CThinning::Morphology(Mat &src, Mat &dst)
{
	src.copyTo(dst);
	bitwise_not(dst, dst);

    cv::Mat skel(dst.size(), CV_8UC1, cv::Scalar(0)); 
    cv::Mat temp(dst.size(), CV_8UC1);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3)); 
    bool done; 
    do 
    { 
        cv::morphologyEx(dst, temp, cv::MORPH_OPEN, element); 
        cv::bitwise_not(temp, temp); 
        cv::bitwise_and(dst, temp, temp); 
        cv::bitwise_or(skel, temp, skel); 
        cv::erode(dst, dst, element);

        double max; 
        cv::minMaxLoc(dst, 0, &max); 
        done = (max == 0); 
    } while (!done);

    dst = skel;
	bitwise_not(dst, dst);
}

// ImageProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "ImageProcessDlg.h"
#include "afxdialogex.h"

#include "Channel.h"
#include "Histogram.h"
#include "Binary.h"

#include "InputNumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageProcessDlg dialog




CImageProcessDlg::CImageProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_res = _T("");
	m_savepath = _T("");
	m_openpath = _T("");
}

void CImageProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RES, m_res);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_savepath);
	DDX_Text(pDX, IDC_EDIT_OPENPATH, m_openpath);
}

BEGIN_MESSAGE_MAP(CImageProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_TEST_TEST, &CImageProcessDlg::OnTestTest)
	ON_COMMAND(ID_TEST_TESTOPENCV, &CImageProcessDlg::OnTestTestopencv)
	ON_COMMAND(ID_FILE_OPENIMAGE, &CImageProcessDlg::OnFileOpenimage)
	ON_COMMAND(ID_CHANNEL_GARY, &CImageProcessDlg::OnChannelGary)
	ON_COMMAND(ID_HISTOGRAM_SHOW, &CImageProcessDlg::OnHistogramShow)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CImageProcessDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CImageProcessDlg::OnBnClickedButtonSave)
	ON_COMMAND(ID_CHANNEL_GRAYB, &CImageProcessDlg::OnChannelGrayb)
	ON_COMMAND(ID_HISTOGRAM_SHOWB, &CImageProcessDlg::OnHistogramShowb)
	ON_COMMAND(ID_HISTOGRAM_HIST, &CImageProcessDlg::OnHistogramHist)
	ON_COMMAND(ID_BINARY_MODE, &CImageProcessDlg::OnBinaryMode)
	ON_COMMAND(ID_FILE_OPENGRAYIMAGE, &CImageProcessDlg::OnFileOpengrayimage)
	ON_COMMAND(ID_BINARY_MODEB, &CImageProcessDlg::OnBinaryModeb)
	ON_COMMAND(ID_BINARY_OTSU, &CImageProcessDlg::OnBinaryOtsu)
	ON_COMMAND(ID_BINARY_OTSUB, &CImageProcessDlg::OnBinaryOtsub)
	ON_COMMAND(ID_BINARY_MAXENTROPY, &CImageProcessDlg::OnBinaryMaxentropy)
	ON_COMMAND(ID_BINARY_ITERATION, &CImageProcessDlg::OnBinaryIteration)
	ON_COMMAND(ID_BINARY_MANNAL, &CImageProcessDlg::OnBinaryMannal)
END_MESSAGE_MAP()


// CImageProcessDlg message handlers

BOOL CImageProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageProcessDlg::OnTestTest()
{
	MessageBox("Test");
}


void CImageProcessDlg::DrawPicToHDC(IplImage * img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}

void CImageProcessDlg::OnTestTestopencv()
{
	Mat mat = imread("test/Lena.png", 1);
	imshow("Test", mat);
}

void CImageProcessDlg::OnFileOpenimage()
{
	// 设置过滤器   
    TCHAR szFilter[] = _T("Image File(*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All File(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();  
		//MessageBox(strFilePath);

		m_src = imread(strFilePath.GetBuffer(0), 1);
		ShowCurImage(m_src);
    }   
}

void CImageProcessDlg::OnFileOpengrayimage()
{	
	// 设置过滤器   
    TCHAR szFilter[] = _T("Image File(*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All File(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();  
		//MessageBox(strFilePath);

		m_src = imread(strFilePath.GetBuffer(0), 0);
		ShowCurImage(m_src);
    }   
}


void CImageProcessDlg::OnChannelGary()
{
	CChannel channel;
	channel.setDebug(CChannel::DEBUG_OPEN);

	channel.Gray(m_cur, m_channel);
	ShowCurImage(m_channel);
}

void CImageProcessDlg::ShowCurImage(const Mat mat)
{
	mat.copyTo(m_cur);
	IplImage img = m_cur;
	DrawPicToHDC(&img, IDC_SHOWIMAGE);
}


void CImageProcessDlg::OnHistogramShow()
{
	Mat hist;
	CHistogram histogram;
	histogram.Show(m_cur, hist);
	imshow("Histogram", hist);
}


void CImageProcessDlg::OnBnClickedButtonOpen()
{	
	TCHAR			szFolderPath[MAX_PATH] = {0};
	CString			strFolderPath = TEXT("");
		
	BROWSEINFO		sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot   = 0;
	sInfo.lpszTitle   = _T("请选择一个文件夹：");
	sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn     = NULL;

	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
		{
			strFolderPath = szFolderPath;
			m_openpath = strFolderPath;
			
			CString str_file = strFolderPath;
			
			CString res_str;
			m_images.clear();

			CString suffixs[] = {"\\*.jpg","\\*.jpeg","\\*.bmp","\\*.png"};
			for(int i = 0; i < 4; ++i)
			{
				CFileFind finder;
				CString filepathname;
				BOOL YesNo=finder.FindFile(str_file + suffixs[i]);
				while (YesNo)
				{
					YesNo=finder.FindNextFile();
					filepathname=finder.GetFilePath();
					m_images.push_back(filepathname);
				}
			}

			for(vector<CString>::size_type v_i = 0; v_i != m_images.size(); ++v_i)
			{
				res_str += m_images[v_i];
				res_str += "\r\n";
			}

			m_res = res_str;

			UpdateData(FALSE);
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}


void CImageProcessDlg::OnBnClickedButtonSave()
{	
	TCHAR			szFolderPath[MAX_PATH] = {0};
	CString			strFolderPath = TEXT("");
		
	BROWSEINFO		sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot   = 0;
	sInfo.lpszTitle   = _T("请选择一个文件夹：");
	sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn     = NULL;

	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
		{
			strFolderPath = szFolderPath;
			this->m_savepath = strFolderPath;
			
			UpdateData(FALSE);
			
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}


void CImageProcessDlg::OnChannelGrayb()
{
	CChannel channel;


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		Mat dst;

		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);
		
		Mat src = imread(str, 1);
		
		int result = channel.Gray(src, dst);

		if (result == 0)
		{
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << this->m_savepath << "\\" << name << "_gray.jpg";
			imwrite(ss.str(), dst);
		}
	}
	MessageBox("Finish");
}


void CImageProcessDlg::OnHistogramShowb()
{
	CHistogram histogram;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		Mat dst;

		string str = m_images[v_i].GetBuffer(0);
		
		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 0);
		
		int result = histogram.Show(src, dst);

		if (result == 0)
		{
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << this->m_savepath << "\\" << name << "_hist.jpg";
			imwrite(ss.str(), dst);
		}
	}
	MessageBox("Finish");
}


void CImageProcessDlg::OnHistogramHist()
{
	Mat hist;
	CHistogram histogram;
	histogram.setDebug(CHistogram::DEBUG_OPEN);

	int arr_hist[256];
	histogram.Hist(m_cur, arr_hist);

	std::ostringstream oss;
	for(int i = 0; i < 256; ++i)
	{
		oss << i << " : " << arr_hist[i] << "\r\n";

	}

	m_res = oss.str().c_str();
	
	UpdateData(FALSE);
}


void CImageProcessDlg::OnBinaryMode()
{
	CBinary binary;
	//binary.setDebug(CBinary::DEBUG_OPEN);

	binary.Mode(m_cur, m_binary);

	ShowCurImage(m_binary);
}



void CImageProcessDlg::OnBinaryModeb()
{
	CBinary binary;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		Mat dst;

		string str = m_images[v_i].GetBuffer(0);
		
		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 0);
		
		int result = binary.Mode(src, dst);

		if (result == 0)
		{
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << this->m_savepath << "\\" << name << "_gray.jpg";
			imwrite(ss.str(), dst);
		}
	}

	MessageBox("Finish");
}


void CImageProcessDlg::OnBinaryOtsu()
{	
	CBinary binary;
	//binary.setDebug(CBinary::DEBUG_OPEN);

	binary.OTSU(m_cur, m_binary);

	ShowCurImage(m_binary);
}


void CImageProcessDlg::OnBinaryOtsub()
{
	CBinary binary;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		Mat dst;

		string str = m_images[v_i].GetBuffer(0);
		
		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 0);
		
		int result = binary.OTSU(src, dst);

		if (result == 0)
		{
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << this->m_savepath << "\\" << name << "_gray.jpg";
			imwrite(ss.str(), dst);
		}
	}

	MessageBox("Finish");
}


void CImageProcessDlg::OnBinaryMaxentropy()
{
	CBinary binary;
	binary.setDebug(CBinary::DEBUG_OPEN);

	binary.MaxEntropy(m_cur, m_binary);

	ShowCurImage(m_binary);
}


void CImageProcessDlg::OnBinaryIteration()
{
	CBinary binary;
	binary.setDebug(CBinary::DEBUG_OPEN);

	binary.Iteration(m_cur, m_binary);

	ShowCurImage(m_binary);
}


void CImageProcessDlg::OnBinaryMannal()
{
	CInputNumDlg dlg;
	CBinary binary;

	dlg.m_num = binary.otsuThreshold(m_cur);

	if(dlg.DoModal())
	{
		int threshold = dlg.m_num;
		binary.Mannal(m_cur, m_binary, threshold);
		ShowCurImage(m_binary);
	}
}

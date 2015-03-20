
// ImageProcessDlg.h : header file
//

#pragma once

#include "Opencv2.4.8.h"
#include "d:\program files\opencv2.4.8\build\include\opencv2\core\core.hpp"

// CImageProcessDlg dialog
class CImageProcessDlg : public CDialogEx
{
// Construction
public:
	CImageProcessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMAGEPROCESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestTest();
	afx_msg void OnTestTestopencv();
	void DrawPicToHDC(IplImage * img, UINT ID);
	void ShowCurImage(const Mat);
	afx_msg void OnFileOpenimage();
	Mat m_src;
	Mat m_cur;
	Mat m_channel;
	Mat m_binary;
	Vector<Point> m_endPoints;
	Vector<Point> m_isolatePoints;

	afx_msg void OnChannelGary();
	afx_msg void OnHistogramShow();
	afx_msg void OnBnClickedButtonOpen();

	
	std::vector<CString>  m_images;
	CString m_res;
	afx_msg void OnBnClickedButtonSave();
	CString m_savepath;
	CString m_openpath;
	afx_msg void OnChannelGrayb();
	afx_msg void OnHistogramShowb();
	afx_msg void OnHistogramHist();
	afx_msg void OnBinaryMode();
	afx_msg void OnFileOpengrayimage();
	afx_msg void OnBinaryModeb();
	afx_msg void OnBinaryOtsu();
	afx_msg void OnBinaryOtsub();
	afx_msg void OnBinaryMaxentropy();
	afx_msg void OnBinaryIteration();
	afx_msg void OnBinaryMannal();
	afx_msg void OnBlurHomogeneous();
	afx_msg void OnBlurSalt();
	afx_msg void OnBlurGaussian();
	afx_msg void OnBlurMedian();
	afx_msg void OnBlurBilatrial();
	afx_msg void OnNoiseGussian();
	afx_msg void OnFileSaveimage();
	afx_msg void OnBlurAdaptivebilateral();
	afx_msg void OnHistogramEqual();
	afx_msg void OnHistogramEqualb();
	afx_msg void OnResize50();
	afx_msg void OnResize51();
	afx_msg void OnResizeNot();
	afx_msg void OnResizeNotb();
	afx_msg void OnBinaryMaxentropyb();
	afx_msg void OnBinaryIterationb();
	afx_msg void OnBinaryMannalb();
	afx_msg void OnThinningRosenfeld();
	afx_msg void OnThinningRosenfeldb();
	afx_msg void OnThinningZhang();
	afx_msg void OnThinningZhangb();
	afx_msg void OnThinningHilditch1();
	afx_msg void OnThinningHilditch2();
	afx_msg void OnThinningHilditch1b();
	afx_msg void OnThinningHilditch2b();
	afx_msg void OnThinningPavlidis();
	afx_msg void OnThinningIndex();
	afx_msg void OnThinningPavlidisb();
	afx_msg void OnThinningIndexb();
	afx_msg void OnThinningMorphology();
	afx_msg void OnThinningMorphologyb();
	afx_msg void OnCompleteFindendpoint();
	afx_msg void OnCompleteFindisolatepoint();
	afx_msg void OnCompleteCompleteisolatepoint();
	afx_msg void OnCompleteCompleteendpoint();
	afx_msg void OnBinaryAllauto();
	afx_msg void OnBinaryNotsu();
	afx_msg void OnBinaryMaxentropymark();
	afx_msg void OnBinaryIterationmark();
};

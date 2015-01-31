
// ImageProcessDlg.h : header file
//

#pragma once

#include "Opencv2.4.8.h"

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
};

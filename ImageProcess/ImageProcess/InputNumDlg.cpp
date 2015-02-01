// InputNumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "InputNumDlg.h"
#include "afxdialogex.h"


// CInputNumDlg 对话框

IMPLEMENT_DYNAMIC(CInputNumDlg, CDialog)

CInputNumDlg::CInputNumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputNumDlg::IDD, pParent)
{

	m_num = 0;
}

CInputNumDlg::~CInputNumDlg()
{
}

void CInputNumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_num);
}


BEGIN_MESSAGE_MAP(CInputNumDlg, CDialog)
END_MESSAGE_MAP()


// CInputNumDlg 消息处理程序

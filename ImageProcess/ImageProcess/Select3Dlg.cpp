// Select3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcess.h"
#include "Select3Dlg.h"
#include "afxdialogex.h"


// CSelect3Dlg �Ի���

IMPLEMENT_DYNAMIC(CSelect3Dlg, CDialog)

CSelect3Dlg::CSelect3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelect3Dlg::IDD, pParent)
{

	m_select = 0;
	m_str = _T("");
}

CSelect3Dlg::~CSelect3Dlg()
{
}

void CSelect3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_select);
	DDX_Text(pDX, IDC_STATIC_STR, m_str);
}


BEGIN_MESSAGE_MAP(CSelect3Dlg, CDialog)
END_MESSAGE_MAP()


// CSelect3Dlg ��Ϣ�������



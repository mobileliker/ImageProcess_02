#pragma once


// CInputNumDlg 对话框

class CInputNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputNumDlg)

public:
	CInputNumDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputNumDlg();

// 对话框数据
	enum { IDD = IDD_INPUTNUM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_num;
};

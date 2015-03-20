#pragma once


// CSelect3Dlg 对话框

class CSelect3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CSelect3Dlg)

public:
	CSelect3Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSelect3Dlg();

// 对话框数据
	enum { IDD = IDD_SELECT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_select;
	CString m_str;
};

#pragma once


// CSelect3Dlg �Ի���

class CSelect3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CSelect3Dlg)

public:
	CSelect3Dlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelect3Dlg();

// �Ի�������
	enum { IDD = IDD_SELECT3_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_select;
	CString m_str;
};

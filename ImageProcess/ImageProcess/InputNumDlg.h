#pragma once


// CInputNumDlg �Ի���

class CInputNumDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputNumDlg)

public:
	CInputNumDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputNumDlg();

// �Ի�������
	enum { IDD = IDD_INPUTNUM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_num;
};

#pragma once
#include "afxwin.h"


// CDlgTranslation �Ի���

class CDlgTranslation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTranslation)

public:
	CDlgTranslation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTranslation();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_TRANSLATION};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	int m_transH;
	int m_transV;	
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

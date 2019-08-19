#pragma once
#include "afxwin.h"


// CDlgTranslation 对话框

class CDlgTranslation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTranslation)

public:
	CDlgTranslation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTranslation();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG_TRANSLATION};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	int m_transH;
	int m_transV;	
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

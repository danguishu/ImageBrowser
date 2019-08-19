// DlgTranslation.cpp : 实现文件
//

#include "stdafx.h"
#include "gdiplus.h"
#include "DlgTranslation.h"
#include "afxdialogex.h"


// CDlgTranslation 对话框

IMPLEMENT_DYNAMIC(CDlgTranslation, CDialogEx)

CDlgTranslation::CDlgTranslation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TRANSLATION, pParent)
	, m_transH(0)
	, m_transV(0)
{
	
}

CDlgTranslation::~CDlgTranslation()
{
}

void CDlgTranslation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_transH);
	DDV_MinMaxInt(pDX, m_transH, -100, 100);
	DDX_Text(pDX, IDC_EDIT2, m_transV);
	DDV_MinMaxInt(pDX, m_transV, -100, 100);
}


BEGIN_MESSAGE_MAP(CDlgTranslation, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTranslation::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTranslation 消息处理程序


void CDlgTranslation::OnOK()
{
	//CDialogEx::OnOK();
}


void CDlgTranslation::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}


BOOL CDlgTranslation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// 如果消息是键盘按下事件，且是Entert键，执行以下代码（什么都不做，你可以自己添加想要的代码）
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

// DlgTranslation.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gdiplus.h"
#include "DlgTranslation.h"
#include "afxdialogex.h"


// CDlgTranslation �Ի���

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


// CDlgTranslation ��Ϣ�������


void CDlgTranslation::OnOK()
{
	//CDialogEx::OnOK();
}


void CDlgTranslation::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}


BOOL CDlgTranslation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// �����Ϣ�Ǽ��̰����¼�������Entert����ִ�����´��루ʲô��������������Լ������Ҫ�Ĵ��룩
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


// gdiplus.h : gdiplus Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")


// CgdiplusApp:
// �йش����ʵ�֣������ gdiplus.cpp
//

class CgdiplusApp : public CWinAppEx
{
public:
	CgdiplusApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
private:
	GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR			m_GdiplusToken;
// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CgdiplusApp theApp;

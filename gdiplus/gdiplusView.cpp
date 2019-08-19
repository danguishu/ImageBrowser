
// gdiplusView.cpp : CgdiplusView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "gdiplus.h"
#endif

#include "gdiplusDoc.h"
#include "gdiplusView.h"
#include "DlgTranslation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgdiplusView

IMPLEMENT_DYNCREATE(CgdiplusView, CView)

BEGIN_MESSAGE_MAP(CgdiplusView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CgdiplusView::OnFileOpen)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_TRANSLATION, &CgdiplusView::OnTranslation)
END_MESSAGE_MAP()

// CgdiplusView 构造/析构

CgdiplusView::CgdiplusView()
{
	// TODO: 在此处添加构造代码
	m_bWidhtOut = false;
	m_bHeightOut = false;
	m_nXX = 0;
	m_nYY = 0;
	m_nXXMax = 0;
	m_nYYMax = 0;
}

CgdiplusView::~CgdiplusView()
{
}

BOOL CgdiplusView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CgdiplusView 绘制

void CgdiplusView::OnDraw(CDC* pDC)
{
	CgdiplusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (m_tempFilePath.IsEmpty())
		return;

	Image img(m_tempFilePath);

	CRect winRect;
	GetClientRect(winRect);

	REAL x = 0.0;
	REAL y = 0.0;
	REAL width = (REAL)img.GetWidth();
	REAL height = (REAL)img.GetHeight();

	// 使图像居中
	if ((UINT)winRect.Width() >= width)
		x = (winRect.Width() - width) / 2.0f;

	if ((UINT)winRect.Height() >= height)
		y = ((UINT)winRect.Height() - height) / 2.0f;

	if ((UINT)winRect.Width() < width)
	{
		x += m_nXX;
		m_bWidhtOut = true;
		m_nXXMax = width - winRect.Width();
	}
		
	if ((UINT)winRect.Height() < height)
	{
		y += m_nYY;
		m_bHeightOut = true;
		m_nYYMax = height - winRect.Height();
	}

	CDC memDC;
	CBitmap MemBitmap;

	// 设备描述表初始化
	memDC.CreateCompatibleDC(NULL);

	// 建立与屏幕显示兼容的内存显示设备
	MemBitmap.CreateCompatibleBitmap(pDC, winRect.Width(), winRect.Height());

	// 选取空白位图
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, winRect.Width(), winRect.Height(), RGB(255, 255, 255));

	Graphics graph((&memDC)->GetSafeHdc());
	graph.DrawImage(&img, x, y, width, height);

	pDC->BitBlt(0, 0, winRect.Width(), winRect.Height(), &memDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	memDC.DeleteDC();

}


// CgdiplusView 打印

BOOL CgdiplusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CgdiplusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CgdiplusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CgdiplusView 诊断

#ifdef _DEBUG
void CgdiplusView::AssertValid() const
{
	CView::AssertValid();
}

void CgdiplusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgdiplusDoc* CgdiplusView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgdiplusDoc)));
	return (CgdiplusDoc*)m_pDocument;
}
#endif //_DEBUG


// CgdiplusView 消息处理程序


void CgdiplusView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(true, NULL, NULL,
		 		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
				L"所有支持文件(*.bmp;*.jpg)|*.bmp;*.jpg|位图文件(*.bmp)|*.bmp|JPG文件(*.jpg)||");
	 	if (dlg.DoModal() == IDOK)
	 	{
	 		//文件完整路径
			m_tempFilePath = dlg.GetPathName();
			Invalidate();
	 	}
		 
}


void CgdiplusView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_LBUTTON)
	{
		if (m_bWidhtOut)
		{
			m_nXX += point.x - m_psMove.x;
			if (m_nXX < 0 && abs(m_nXX) > m_nXXMax)
				m_nXX = -m_nXXMax;
			if (m_nXX > 0)
				m_nXX = 0;
		}

		if (m_bHeightOut)
		{
			m_nYY += point.y - m_psMove.y;
			if (m_nYY < 0 && abs(m_nYY) > m_nYYMax)
				m_nYY = -m_nYYMax;
			if (m_nYY > 0)
				m_nYY = 0;
		}

		m_psMove = point;

		Invalidate();
	}


	CView::OnMouseMove(nFlags, point);
}


void CgdiplusView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_psMove = point;
	CView::OnLButtonDown(nFlags, point);
}


BOOL CgdiplusView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bHeightOut || m_bWidhtOut)
	{
		SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		return TRUE;
	}
	else
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


BOOL CgdiplusView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CgdiplusView::OnTranslation()
{
	// TODO: 在此添加命令处理程序代码
	CDlgTranslation dlg;
	if (dlg.DoModal() != IDOK)// 显示对话框，设定旋转角度
	{
		return;
	}
	CString strTransH;
	strTransH.Format(_T("%d"), dlg.m_transH);
	MessageBox(strTransH);
	CString strTransV;
	strTransV.Format(_T("%d"), dlg.m_transV);
	MessageBox(strTransV);
}


// gdiplusView.cpp : CgdiplusView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CgdiplusView ����/����

CgdiplusView::CgdiplusView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CgdiplusView ����

void CgdiplusView::OnDraw(CDC* pDC)
{
	CgdiplusDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	if (m_tempFilePath.IsEmpty())
		return;

	Image img(m_tempFilePath);

	CRect winRect;
	GetClientRect(winRect);

	REAL x = 0.0;
	REAL y = 0.0;
	REAL width = (REAL)img.GetWidth();
	REAL height = (REAL)img.GetHeight();

	// ʹͼ�����
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

	// �豸�������ʼ��
	memDC.CreateCompatibleDC(NULL);

	// ��������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemBitmap.CreateCompatibleBitmap(pDC, winRect.Width(), winRect.Height());

	// ѡȡ�հ�λͼ
	memDC.SelectObject(MemBitmap);
	memDC.FillSolidRect(0, 0, winRect.Width(), winRect.Height(), RGB(255, 255, 255));

	Graphics graph((&memDC)->GetSafeHdc());
	graph.DrawImage(&img, x, y, width, height);

	pDC->BitBlt(0, 0, winRect.Width(), winRect.Height(), &memDC, 0, 0, SRCCOPY);

	MemBitmap.DeleteObject();
	memDC.DeleteDC();

}


// CgdiplusView ��ӡ

BOOL CgdiplusView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CgdiplusView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CgdiplusView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CgdiplusView ���

#ifdef _DEBUG
void CgdiplusView::AssertValid() const
{
	CView::AssertValid();
}

void CgdiplusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgdiplusDoc* CgdiplusView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgdiplusDoc)));
	return (CgdiplusDoc*)m_pDocument;
}
#endif //_DEBUG


// CgdiplusView ��Ϣ�������


void CgdiplusView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(true, NULL, NULL,
		 		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
				L"����֧���ļ�(*.bmp;*.jpg)|*.bmp;*.jpg|λͼ�ļ�(*.bmp)|*.bmp|JPG�ļ�(*.jpg)||");
	 	if (dlg.DoModal() == IDOK)
	 	{
	 		//�ļ�����·��
			m_tempFilePath = dlg.GetPathName();
			Invalidate();
	 	}
		 
}


void CgdiplusView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_psMove = point;
	CView::OnLButtonDown(nFlags, point);
}


BOOL CgdiplusView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}


void CgdiplusView::OnTranslation()
{
	// TODO: �ڴ���������������
	CDlgTranslation dlg;
	if (dlg.DoModal() != IDOK)// ��ʾ�Ի����趨��ת�Ƕ�
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

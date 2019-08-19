
// gdiplusView.h : CgdiplusView ��Ľӿ�
//

#pragma once


class CgdiplusView : public CView
{
protected: // �������л�����
	CgdiplusView();
	DECLARE_DYNCREATE(CgdiplusView)

// ����
public:
	CgdiplusDoc* GetDocument() const;

// ����
public:
	
private:
	bool	m_bWidhtOut;				// ��ʾͼ���Ƿ񳬳���ͼ���
	bool	m_bHeightOut;				// ��ʾͼ���Ƿ񳬳���ͼ�߶�
	CString m_tempFilePath;				//��¼ͼƬ�����ļ�·��
	CPoint	m_psMove;					//��¼����ƶ�ǰ����λ��
	int		m_nXX;						// ͼƬX�����ƫ����
	int		m_nYY;						// ͼƬY�����ƫ����
	int		m_nXXMax;					// X�������ƫ����
	int		m_nYYMax;					// Y�������ƫ����
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CgdiplusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTranslation();
};

#ifndef _DEBUG  // gdiplusView.cpp �еĵ��԰汾
inline CgdiplusDoc* CgdiplusView::GetDocument() const
   { return reinterpret_cast<CgdiplusDoc*>(m_pDocument); }
#endif


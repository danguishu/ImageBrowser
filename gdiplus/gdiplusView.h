
// gdiplusView.h : CgdiplusView 类的接口
//

#pragma once


class CgdiplusView : public CView
{
protected: // 仅从序列化创建
	CgdiplusView();
	DECLARE_DYNCREATE(CgdiplusView)

// 特性
public:
	CgdiplusDoc* GetDocument() const;

// 操作
public:
	
private:
	bool	m_bWidhtOut;				// 显示图像是否超出视图宽度
	bool	m_bHeightOut;				// 显示图像是否超出视图高度
	CString m_tempFilePath;				//记录图片所在文件路径
	CPoint	m_psMove;					//记录鼠标移动前所在位置
	int		m_nXX;						// 图片X坐标的偏移量
	int		m_nYY;						// 图片Y坐标的偏移量
	int		m_nXXMax;					// X坐标最大偏移量
	int		m_nYYMax;					// Y坐标最大偏移量
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CgdiplusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // gdiplusView.cpp 中的调试版本
inline CgdiplusDoc* CgdiplusView::GetDocument() const
   { return reinterpret_cast<CgdiplusDoc*>(m_pDocument); }
#endif



// FaceTrackTKView.h : interface of the CFaceTrackTKView class
//

#pragma once


class CFaceTrackTKView : public CView
{
protected: // create from serialization only
	CFaceTrackTKView();
	DECLARE_DYNCREATE(CFaceTrackTKView)

// Attributes
public:
	CFaceTrackTKDoc* GetDocument() const;

	void CFaceTrackTKView::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin);
	static int Bpp(cv::Mat img) { return 8 * img.channels(); }
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFaceTrackTKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FaceTrackTKView.cpp
inline CFaceTrackTKDoc* CFaceTrackTKView::GetDocument() const
   { return reinterpret_cast<CFaceTrackTKDoc*>(m_pDocument); }
#endif


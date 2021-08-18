
// FaceTrackTKView.cpp : implementation of the CFaceTrackTKView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FaceTrackTK.h"
#endif

#include "FaceTrackTKDoc.h"
#include "FaceTrackTKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFaceTrackTKView

IMPLEMENT_DYNCREATE(CFaceTrackTKView, CView)

BEGIN_MESSAGE_MAP(CFaceTrackTKView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFaceTrackTKView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFaceTrackTKView construction/destruction

CFaceTrackTKView::CFaceTrackTKView()
{
	// TODO: add construction code here

}

CFaceTrackTKView::~CFaceTrackTKView()
{
}

BOOL CFaceTrackTKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFaceTrackTKView drawing

void CFaceTrackTKView::OnDraw(CDC* pDC)
{
	//CFaceTrackTKDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: add draw code for native data here
	//CPen pen;
	//pen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));

	//CPen *oldpen = pDC->SelectObject(&pen);

	//pDC->MoveTo(0, 0);
	//pDC->LineTo(100, 150);

	//pDC->SelectObject(oldpen);


	//CFont font;
	//font.CreateFont(14, 0, 200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));

	//CFont *oldfont = pDC->SelectObject(&font);

	//int x, y;
	//pDoc->GetTextLoc(x, y);
	//pDC->TextOut(x, y, pDoc->GetText());

	//pDC->SelectObject(oldfont);

	//if (theApp.FaceTrackRunning())
	//{
	//	pDoc->GetImage();
	//	if (pDoc->m_cvImage.empty()) return;
	//	// TODO: add draw code for native data here
	//	int height = pDoc->m_cvImage.rows;
	//	int width = pDoc->m_cvImage.cols;
	//	uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
	//	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	//	FillBitmapInfo(bmi, width, height, Bpp(pDoc->m_cvImage), 0);
	//	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width,
	//		height, 0, 0, 0, height, pDoc->m_cvImage.data, bmi,
	//		DIB_RGB_COLORS);
	//}

}


// CFaceTrackTKView printing


void CFaceTrackTKView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFaceTrackTKView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceTrackTKView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceTrackTKView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFaceTrackTKView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFaceTrackTKView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFaceTrackTKView diagnostics

#ifdef _DEBUG
void CFaceTrackTKView::AssertValid() const
{
	CView::AssertValid();
}

void CFaceTrackTKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFaceTrackTKDoc* CFaceTrackTKView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceTrackTKDoc)));
	return (CFaceTrackTKDoc*)m_pDocument;
}

void CFaceTrackTKView::FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;

	if (bpp == 8)
	{
		RGBQUAD* palette = bmi->bmiColors;

		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}
#endif //_DEBUG


// CFaceTrackTKView message handlers

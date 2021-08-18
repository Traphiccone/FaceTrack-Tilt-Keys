
// FaceTrackTKDoc.cpp : implementation of the CFaceTrackTKDoc class
//

#include "stdafx.h"
#include "TextDlg.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FaceTrackTK.h"
#include <vector>
#endif

#include "FaceTrackTKDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFaceTrackTKDoc

IMPLEMENT_DYNCREATE(CFaceTrackTKDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceTrackTKDoc, CDocument)
	ON_COMMAND(ID_FILE_START, &CFaceTrackTKDoc::OnFileStart)
END_MESSAGE_MAP()


// CFaceTrackTKDoc construction/destruction

CFaceTrackTKDoc::CFaceTrackTKDoc()
{
	// TODO: add one-time construction code here
	//m_linetox = 100;
	//m_linetoy = 100;
	//m_textx = 50;
	//m_texty = 50;
	//m_leftKeyID = 'q';
	//m_leftKeyID2 = "(Optional)";
	//m_leftKeyID3 = "(Optional)";
	//m_leftKeyID4 = "(Optional)";
	//m_rightKeyID = 'e';
	//m_rightKeyID2 = "(Optional)";
	//m_rightKeyID3 = "(Optional)";
	//m_rightKeyID4 = "(Optional)";
	
	//m_pressOrderL1 = 0;
	//m_pressOrderL2 = 1;
	//m_pressOrderL3 = 2;
	//m_pressOrderL4 = 3;
	//m_pressOrderR1 = 0;
	//m_pressOrderR2 = 1;
	//m_pressOrderR3 = 2;
	//m_pressOrderR4 = 3;
}

CFaceTrackTKDoc::~CFaceTrackTKDoc()
{
}

BOOL CFaceTrackTKDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CFaceTrackTKDoc serialization

void CFaceTrackTKDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFaceTrackTKDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFaceTrackTKDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFaceTrackTKDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFaceTrackTKDoc diagnostics

#ifdef _DEBUG
void CFaceTrackTKDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceTrackTKDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFaceTrackTKDoc commands

void CFaceTrackTKDoc::OnFileStart()
{
	theApp.RunFaceTracking();
}


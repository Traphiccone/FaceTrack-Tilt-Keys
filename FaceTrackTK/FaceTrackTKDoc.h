
// FaceTrackTKDoc.h : interface of the CFaceTrackTKDoc class
//


#pragma once


class CFaceTrackTKDoc : public CDocument
{
protected: // create from serialization only
	CFaceTrackTKDoc();
	DECLARE_DYNCREATE(CFaceTrackTKDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFaceTrackTKDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

	//void GetLineTo(int &x, int &y) const { x = m_linetox;  y = m_linetoy; }
	//void GetTextLoc(int &x, int &y) const { x = m_textx;  y = m_texty; }
	//const CString &GetText() const { return m_leftKeyID; }
	void GetImage(){ m_cvImage = *theApp.GetImage(); }
	Mat m_cvImage;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

private:

	//int m_linetox;
	//int m_linetoy;
	//int m_textx;
	//int m_texty;
	//CString m_leftKeyID;
	//CString m_leftKeyID2;
	//CString m_leftKeyID3;
	//CString m_leftKeyID4;
	//CString m_rightKeyID;
	//CString m_rightKeyID2;
	//CString m_rightKeyID3;
	//CString m_rightKeyID4;
	
	//int m_pressOrderL1;
	//int m_pressOrderL2;
	//int m_pressOrderL3;
	//int m_pressOrderL4;
	//int m_pressOrderR1;
	//int m_pressOrderR2;
	//int m_pressOrderR3;
	//int m_pressOrderR4;
public:
	afx_msg void OnSettingsSetnewkeys();
	afx_msg void OnFileStart();
};

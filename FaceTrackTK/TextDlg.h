#pragma once

#include "stdafx.h"
#include "FaceTrackTK.h"
#include "TextDlg.h"
#include "afxdialogex.h"
#include "afxcmn.h"
// CTextDlg dialog

class CTextDlg : public CDialog
{
	DECLARE_DYNAMIC(CTextDlg)

public:
	CTextDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Main left keystroke
	CString m_leftKeyID;
	// Optional additional left keystrokes
	CString m_leftKeyID2;
	CString m_leftKeyID3;
	CString m_leftKeyID4;


	// Main right keystroke
	CString m_rightKeyID;
	// Optional additional right keystrokes
	CString m_rightKeyID2;
	CString m_rightKeyID3;
	CString m_rightKeyID4;
	
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnCbnSelchangeCombo1();
	// Order in which key will be pressed
	int m_pressOrderL1;
	int m_pressOrderL2;
	int m_pressOrderL3;
	int m_pressOrderL4;
	int m_pressOrderR1;
	int m_pressOrderR2;
	int m_pressOrderR3;
	int m_pressOrderR4;
	afx_msg void OnBnClickedCheck1();
	BOOL m_toggleBackL;
	BOOL m_toggleBackR;
	int m_degreeMaxBoxL;
	int m_degreeMaxBoxR;
};

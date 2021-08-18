// TextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FaceTrackTK.h"
#include "TextDlg.h"
#include "afxdialogex.h"


// CTextDlg dialog

IMPLEMENT_DYNAMIC(CTextDlg, CDialog)

CTextDlg::CTextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextDlg::IDD, pParent)
	, m_leftKeyID(_T(""))
	, m_rightKeyID(_T(""))
	, m_pressOrderL1(0)
	, m_pressOrderR1(0)
	, m_leftKeyID2(_T(""))
	, m_leftKeyID3(_T(""))
	, m_leftKeyID4(_T(""))
	, m_rightKeyID2(_T(""))
	, m_rightKeyID3(_T(""))
	, m_rightKeyID4(_T(""))
	, m_pressOrderR2(0)
	, m_pressOrderR3(0)
	, m_pressOrderR4(0)
	, m_toggleBackL(FALSE)
	, m_toggleBackR(FALSE)
	, m_degreeMaxBoxL(0)
	, m_degreeMaxBoxR(0)
{

}

CTextDlg::~CTextDlg()
{
}

void CTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LEFTKEYINPUT, m_leftKeyID);

	DDX_Text(pDX, IDC_RIGHTKEYINPUT, m_rightKeyID);
	DDX_Text(pDX, IDC_LEFTKEYINPUT2, m_leftKeyID2);
	DDX_Text(pDX, IDC_LEFTKEYINPUT3, m_leftKeyID3);
	DDX_Text(pDX, IDC_LEFTKEYINPUT4, m_leftKeyID4);
	DDX_Text(pDX, IDC_RIGHTKEYINPUT2, m_rightKeyID2);
	DDX_Text(pDX, IDC_RIGHTKEYINPUT3, m_rightKeyID3);
	DDX_Text(pDX, IDC_RIGHTKEYINPUT4, m_rightKeyID4);
	DDX_Check(pDX, IDC_CHECK1, m_toggleBackL);
	DDX_Check(pDX, IDC_CHECK2, m_toggleBackR);

	DDX_Text(pDX, IDC_EDIT1, m_degreeMaxBoxL);
	DDV_MinMaxInt(pDX, m_degreeMaxBoxL, 0, 90);
	DDX_Text(pDX, IDC_EDIT2, m_degreeMaxBoxR);
	DDV_MinMaxInt(pDX, m_degreeMaxBoxR, 0, 90);
}


BEGIN_MESSAGE_MAP(CTextDlg, CDialog)

	ON_BN_CLICKED(IDC_CHECK1, &CTextDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CTextDlg message handlers


void CTextDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CTextDlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void CTextDlg::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
}

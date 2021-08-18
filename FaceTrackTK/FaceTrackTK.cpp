// FaceTrackTK.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TextDlg.h"
#include "afxwin.h""
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "FaceTrackTK.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "FaceTrackTKDoc.h"
#include "FaceTrackTKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFaceTrackTKApp

BEGIN_MESSAGE_MAP(CFaceTrackTKApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CFaceTrackTKApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_START, &CFaceTrackTKApp::OnFileStart)
	ON_COMMAND(ID_APP_EXIT, &CFaceTrackTKApp::OnAppExit)
	ON_COMMAND(ID_FILE_SAVE, &CFaceTrackTKApp::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CFaceTrackTKApp::OnFileOpen)
	ON_COMMAND(ID_SETTINGS_DEFAULTSETTINGS, &CFaceTrackTKApp::OnSettingsDefaultsettings)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, &CFaceTrackTKApp::OnUpdateAppExit)
	ON_UPDATE_COMMAND_UI(ID_FILE_START, &CFaceTrackTKApp::OnUpdateFileStart)
	ON_COMMAND(ID_SETTINGS_EDITGENERALSETTINGS, &CFaceTrackTKApp::OnSettingsEditgeneralsettings)
END_MESSAGE_MAP()


// CFaceTrackTKApp construction

CFaceTrackTKApp::CFaceTrackTKApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("FaceTrackTK.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

// The one and only CFaceTrackTKApp object

CFaceTrackTKApp theApp;


// CFaceTrackTKApp initialization

BOOL CFaceTrackTKApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_FaceTrackTKTYPE,
		RUNTIME_CLASS(CFaceTrackTKDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CFaceTrackTKView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_FaceTrackTKTYPE))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)   // actually none
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	int screen_x_size = rect.Width();
	int screen_y_size = rect.Height();

	pMainFrame->SetWindowPos(m_pMainWnd, screen_x_size* 0.3, screen_y_size*0.3, 658, 65, SWP_NOZORDER);
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	LPCTCH mainWinName = L"FaceTrack Tilt Key Mapper";
	pMainFrame->SetWindowTextW(mainWinName);

	m_leftKeyID1 = L"Q";
	m_leftKeyID2 = "(OPTIONAL)";
	m_leftKeyID3 = "(OPTIONAL)";
	m_leftKeyID4 = "(OPTIONAL)";
	m_rightKeyID1 = L"E";
	m_rightKeyID2 = "(OPTIONAL)";
	m_rightKeyID3 = "(OPTIONAL)";
	m_rightKeyID4 = "(OPTIONAL)";
	m_toggleBackL = false;
	m_toggleBackR = false;
	m_degreeMaxBoxL = 10.0;
	m_degreeMaxBoxR = 10.0;
	SaveNewKeys();
	m_exit = false;

	TCHAR* pFileName = _T("USERSETTINGS.dat");
	CStdioFile f1;
	if (f1.Open(pFileName, CFile::modeWrite | CFile::typeText))
	{
		f1.Close();
		OnFileOpen();
	}
	OnFileStart();
	return TRUE;
}

int CFaceTrackTKApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	m_exit = true;
	OnAppExit();
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CFaceTrackTKApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CFaceTrackTKApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CFaceTrackTKApp customization load/save methods

void CFaceTrackTKApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CFaceTrackTKApp::LoadCustomState()
{
}

void CFaceTrackTKApp::SaveCustomState()
{
}

// CFaceTrackTKApp message handlers


void CFaceTrackTKApp::RunFaceTracking()
{
	CRect lpRect;

	m_faceTrackOn = true;
	m_control.Init();

	while (!m_exit)
	{
		m_pMainWnd->GetWindowRect(lpRect);
		m_menuX = lpRect.TopLeft().x;
		m_menuY = lpRect.TopLeft().y;
		m_control.SetWndPos(m_menuX, m_menuY);
		m_control.SystemControl();
		//m_image = m_control.GetImage();
	}
}


void CFaceTrackTKApp::OnFileStart()
{
	m_exit = false;
	RunFaceTracking();
}

void CFaceTrackTKApp::SaveNewKeys()
{
	if (m_keyIDs.size())
	{
		m_keyIDs[0] = (m_leftKeyID1);
		m_keyIDs[1] = (m_leftKeyID2);
		m_keyIDs[2] = (m_leftKeyID3);
		m_keyIDs[3] = (m_leftKeyID4);
		m_keyIDs[4] = (m_rightKeyID1);
		m_keyIDs[5] = (m_rightKeyID2);
		m_keyIDs[6] = (m_rightKeyID3);
		m_keyIDs[7] = (m_rightKeyID4);
	}
	else
	{
		m_keyIDs.push_back(m_leftKeyID1);
		m_keyIDs.push_back(m_leftKeyID2);
		m_keyIDs.push_back(m_leftKeyID3);
		m_keyIDs.push_back(m_leftKeyID4);
		m_keyIDs.push_back(m_rightKeyID1);
		m_keyIDs.push_back(m_rightKeyID2);
		m_keyIDs.push_back(m_rightKeyID3);
		m_keyIDs.push_back(m_rightKeyID4);
	}
	m_control.SetMaxDegrees(m_degreeMaxBoxL, m_degreeMaxBoxR);
	m_control.SetToggle(m_toggleBackL, m_toggleBackR);
	m_control.SetStringKeys(m_keyIDs);
}


void CFaceTrackTKApp::OnAppExit()
{
	m_exit = true;
	m_control.Destroy();
}



void CFaceTrackTKApp::OnSettingsEditgeneralsettings()
{

	CTextDlg dlg;

	dlg.m_leftKeyID = m_leftKeyID1;
	dlg.m_leftKeyID2 = m_leftKeyID2;
	dlg.m_leftKeyID3 = m_leftKeyID3;
	dlg.m_leftKeyID4 = m_leftKeyID4;
	dlg.m_rightKeyID = m_rightKeyID1;
	dlg.m_rightKeyID2 = m_rightKeyID2;
	dlg.m_rightKeyID3 = m_rightKeyID3;
	dlg.m_rightKeyID4 = m_rightKeyID4;
	dlg.m_toggleBackL = m_toggleBackL;
	dlg.m_toggleBackR = m_toggleBackR;

	dlg.m_degreeMaxBoxL = m_degreeMaxBoxL;
	dlg.m_degreeMaxBoxR = m_degreeMaxBoxR;
	if (dlg.DoModal() == IDOK)
	{
		m_leftKeyID1 = dlg.m_leftKeyID;
		m_leftKeyID2 = dlg.m_leftKeyID2;
		m_leftKeyID3 = dlg.m_leftKeyID3;
		m_leftKeyID4 = dlg.m_leftKeyID4;
		m_rightKeyID1 = dlg.m_rightKeyID;
		m_rightKeyID2 = dlg.m_rightKeyID2;
		m_rightKeyID3 = dlg.m_rightKeyID3;
		m_rightKeyID4 = dlg.m_rightKeyID4;
		m_toggleBackL = dlg.m_toggleBackL;
		m_toggleBackR = dlg.m_toggleBackR;
		m_degreeMaxBoxL = dlg.m_degreeMaxBoxL;
		m_degreeMaxBoxR = dlg.m_degreeMaxBoxR;
	}

	SaveNewKeys();
}

void CFaceTrackTKApp::OnFileSave()
{
	TCHAR* pFileName = _T("C:\\Program Files\\FaceTrackTK\\USERSETTINGS.dat");
	// open a file
	CStdioFile f1;
	LPCTSTR x = _T("C:\\Program Files\\FaceTrackTK\\USERSETTINGS.dat");
	f1.SetFilePath(x);
	if (!f1.Open(pFileName, CFile::modeCreate | CFile::modeWrite
		| CFile::typeText))
	{
		TRACE(_T("Unable to open file\n"));
	}
	else
	{
		f1.WriteString(L"m_leftKeyID1,");
		f1.WriteString(m_leftKeyID1);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_leftKeyID2,");
		f1.WriteString(m_leftKeyID2);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_leftKeyID3,");
		f1.WriteString(m_leftKeyID3);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_leftKeyID4,");
		f1.WriteString(m_leftKeyID4);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_rightKeyID1,");
		f1.WriteString(m_rightKeyID1);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_rightKeyID2,");
		f1.WriteString(m_rightKeyID2);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_rightKeyID3,");
		f1.WriteString(m_rightKeyID3);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_rightKeyID4,");
		f1.WriteString(m_rightKeyID4);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_toggleBackL,");
		CString cs_tbl;
		cs_tbl = m_toggleBackL ? "TRUE" : "FALSE";
		f1.WriteString(cs_tbl);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_toggleBackL,");
		CString cs_tbr;
		cs_tbr = m_toggleBackR ? "TRUE" : "FALSE";
		f1.WriteString(cs_tbr);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_degreeMaxBoxL,");
		CString degMaxStrL;
		degMaxStrL.Format(L"%d", m_degreeMaxBoxL);
		f1.WriteString(degMaxStrL);
		f1.WriteString(L"\n");
		f1.WriteString(L"m_degreeMaxBoxR,");
		CString degMaxStrR;
		degMaxStrR.Format(L"%d", m_degreeMaxBoxR);
		f1.WriteString(degMaxStrR);
		f1.WriteString(L"\n");
		f1.Close();
	}
}


void CFaceTrackTKApp::OnFileOpen()
{
	TCHAR* pFileName = _T("USERSETTINGS.dat");
	CStdioFile file;
	CStringArray aLineArray;
	CString sLine;
	int lineCnt = 0;

	CFileException ex;
	

	//if (!file.Open(nFilename, CFile::modeNoTruncate | CFile::modeRead, &ex))
	//{
	if (!file.Open(pFileName, CFile::modeRead | CFile::typeText))
	{
		cout << (LPCSTR) "error" << endl;
	}
	else
	{
		int com = 0;
		for (int x = 0; x < 12; x++)
		{
			while (file.ReadString(sLine))
			{
				com = sLine.Find(',',0);
				sLine.Delete(0, com + 1);
				aLineArray.Add(sLine);
				lineCnt++;
			}
		}
		file.Close();
	}
	if (lineCnt >= 12)
	{
		m_leftKeyID1 = aLineArray[0];
		m_leftKeyID2 = aLineArray[1];
		m_leftKeyID3 = aLineArray[2];
		m_leftKeyID4 = aLineArray[3];
		m_rightKeyID1 = aLineArray[4];
		m_rightKeyID2 = aLineArray[5];
		m_rightKeyID3 = aLineArray[6];
		m_rightKeyID4 = aLineArray[7];

		if (aLineArray[8] == "TRUE")
			m_toggleBackL = TRUE;
		else
			m_toggleBackL = FALSE;
		if (aLineArray[9] == "TRUE")
			m_toggleBackR = TRUE;
		else
			m_toggleBackR = FALSE;

		m_degreeMaxBoxL = _wtoi(aLineArray[10]);
		m_degreeMaxBoxR = _wtoi(aLineArray[11]);
		SaveNewKeys();
	}
}


void CFaceTrackTKApp::OnSettingsDefaultsettings()
{
	m_leftKeyID1 = L"Q";
	m_leftKeyID2 = "(OPTIONAL)";
	m_leftKeyID3 = "(OPTIONAL)";
	m_leftKeyID4 = "(OPTIONAL)";
	m_rightKeyID1 = L"E";
	m_rightKeyID2 = "(OPTIONAL)";
	m_rightKeyID3 = "(OPTIONAL)";
	m_rightKeyID4 = "(OPTIONAL)";
	m_toggleBackL = false;
	m_toggleBackR = false;
	m_degreeMaxBoxL = 10.0;
	m_degreeMaxBoxR = 10.0;
	SaveNewKeys();
}


void CFaceTrackTKApp::OnUpdateAppExit(CCmdUI *pCmdUI)
{
	if (m_exit)
	{
		pCmdUI->Enable(0);
		(ID_FILE_START, &CFaceTrackTKApp::OnUpdateFileStart);
	}
	else
	{
		pCmdUI->Enable();
		(ID_FILE_START, &CFaceTrackTKApp::OnUpdateFileStart);
	}
}


void CFaceTrackTKApp::OnUpdateFileStart(CCmdUI *pCmdUI)
{
	if (!m_exit)
	{
		pCmdUI->Enable(0);
		(ID_FILE_START, &CFaceTrackTKApp::OnUpdateAppExit);
	}
	else
	{
		pCmdUI->Enable();
		(ID_FILE_START, &CFaceTrackTKApp::OnUpdateAppExit);
	}
}


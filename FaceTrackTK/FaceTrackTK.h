
// FaceTrackTK.h : main header file for the FaceTrackTK application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "stdafx.h"
#include <vector>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <afxwin.h>
#include <stdlib.h>
#include <afx.h>


#define WINVER 0x0500
#include <windows.h>
#include "resource.h"       // main symbols
#include "Controller.h"
#include "Keyboard.h"
#include "ImageProcess.h"
#include "msxml2.h"


// CFaceTrackTKApp:
// See FaceTrackTK.cpp for the implementation of this class
//

class CFaceTrackTKApp : public CWinAppEx
{
public:
	CFaceTrackTKApp();
	virtual ~CFaceTrackTKApp()
	{
		m_exit = true;
	}

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	void SaveNewKeys();
	void RunFaceTracking();
	bool FaceTrackRunning(){ return m_faceTrackOn; }
	void MainWndExiting(){ m_exit = true; }
	Mat *GetImage(){ return m_image; }

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
private:
	CController m_control;
	std::vector<CString> m_keyIDs;
	//std::vector<int> m_pressOrder;
	bool m_faceTrackOn = false;
	//Mat m_displayMat;
	Mat * m_image;

	CString m_leftKeyID1;
	CString m_leftKeyID2;
	CString m_leftKeyID3;
	CString m_leftKeyID4;
	CString m_rightKeyID1;
	CString m_rightKeyID2;
	CString m_rightKeyID3;
	CString m_rightKeyID4;
	BOOL m_toggleBackL;
	BOOL m_toggleBackR;
	int m_degreeMaxBoxL;
	int m_degreeMaxBoxR;
	int m_menuX = 0;
	int m_menuY = 0;
	BOOL m_exit;
	CString nFilename;


public:
	afx_msg void OnSettingsGeneral();
	afx_msg void OnFileStart();
	//afx_msg void OnUpdateSettingsShowtrackingwindow(CCmdUI *pCmdUI);
	//afx_msg void OnSettingsShowtrackingwindow();
	afx_msg void OnAppExit();

	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnSettingsDefaultsettings();
	afx_msg void OnUpdateAppExit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileStart(CCmdUI *pCmdUI);
	afx_msg void OnSettingsEditgeneralsettings();
};

extern CFaceTrackTKApp theApp;

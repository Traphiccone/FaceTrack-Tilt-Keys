#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <afxwin.h>
#include "resource.h"

#define WINVER 0x0500
#include <windows.h>
#include "ImageProcess.h"
#include "Keyboard.h"

#pragma once
class CController
{
public:
	CController();
	virtual ~CController();

	enum States {
		Center, Left, Right, LeanLeft,
		LeftToCenter, LeanRight, RightToCenter};

	void Init();
	void SystemControl();
	void SetState(States state);
	void SetWndPos(int x, int y){ mImage.SetWndPos(x, y); }
	void Service();
	//Mat GetImage2(){ return mImage.GetDisplayFrame2(); }
	//Mat *GetImage(){ return mImage.GetImage(); }
	void SetStringKeys(std::vector<CString> keys){ mKeys.SetStringKeys(keys); }
	void SetToggle(BOOL left, BOOL right){ m_toggleBackL = left, m_toggleBackR = right; }
	void SetMaxDegrees(int left, int right){ mLeftMax = -left, mRightMax = right; }
	//void SetTrackWin(BOOL onoff){ mImage.SetTrackWin(onoff); }
	void Destroy(){ mImage.Destroy(); }

private:
	CImageProcess mImage;
	Mat m_diplayMat;
	CKeyboard mKeys;
	std::vector<CString> m_keyIDs;
	double mEyeSlope = 0.0;
	States mState = Center;
	BOOL m_toggleBackL;
	BOOL m_toggleBackR;
	BOOL m_exit = false;
	int mLeftMax = -10; 
	int mRightMax = 10;
};


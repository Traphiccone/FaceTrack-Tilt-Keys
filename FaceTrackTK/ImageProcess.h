#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>

#define WINVER 0x0500
#include <windows.h>

using namespace std;
using namespace cv;

#pragma once
class CImageProcess
{
public:
	CImageProcess();
	virtual ~CImageProcess();

	void Init();
	void ProcessImage();
	double GetSlope(){ return mEyeSlope; }
	double GetDegrees(){ return mDegrees; }
	double SlopeToDegrees(double slope);
	double DegreesToSlope(double deg);
	void CalcDegRotate();
	void RapidFindFace();
	//Mat GetDisplayFrame2(){ return mDisplayFrame; }
	//Mat *GetImage(){ return mDisplayableFrame; }
	void SetWndPos(int x, int y){ m_windowLocX = x, m_windowLocY = y + 60; }
	//void SetTrackWin(BOOL onoff){ m_trackWindow = onoff; }
	void Destroy(){ destroyWindow(mWindowName); }
	
private:
	string mWindowName = "Tracking Window";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	
	double mY2 = 0.0;
	double mY1 = 0.0;
	double mX2 = 0.0;
	double mX1 = 0.0;
	double mEyeSlope = 0.0;
	double mDegrees = 0.0;
	double mDegRotate = 0.0;
	double mDegRotSave = 0.0;

	int mFaceLostCnt = 0;
	int mFaceFindAtmpt = 0;

	int m_windowLocX = 0;
	int m_windowLocY = 0;
	//setup image files used in the capture process
	Mat * mDisplayableFrame;
	Mat mDisplayFrame;
	Mat captureFrame;
	Mat grayscaleFrame;
	Mat imgRotated;
	Mat matRotation;
	Mat mReverseRotation;
	VideoCapture mCap;
	//BOOL m_trackWindow;
	BOOL m_destroyed = false;
};


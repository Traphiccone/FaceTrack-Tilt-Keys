#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

#include "ImageProcess.h"



CImageProcess::CImageProcess()
{
	//use the haarcascade_frontalface_alt.xml library
	if (!face_cascade.load("haarcascade_frontalface_alt.xml")) {
		printf("Unable to load face classifier  XML");
	}
	if (!eyes_cascade.load("haarcascade_eye_tree_eyeglasses.xml")) {
		printf("Unable to load eye classifier  XML");
	}
}


CImageProcess::~CImageProcess()
{
}

void CImageProcess::Init()
{
		//create a window to present the results
	
	CRect rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	int screen_x_size = rect.Width();
	int screen_y_size = rect.Height();


	//namedWindow(mWindowName, 1 );
	//moveWindow(mWindowName, screen_x_size* 0.3, screen_y_size*0.3 + 60);

	mCap.open(-1);
}

void CImageProcess::ProcessImage()
{
	//Check if a face was foundon the last iteration
	if (mFaceLostCnt > 0)
		RapidFindFace();
	//capture a new image frame
	mCap >> captureFrame;

	matRotation = getRotationMatrix2D(Point(320, 240),mDegRotate, 1);
	mReverseRotation = getRotationMatrix2D(Point(320, 240), -mDegRotate, 1);
	warpAffine(captureFrame, imgRotated, matRotation, captureFrame.size(), INTER_LINEAR, 0, Scalar());


	//convert captured image to gray scale and equalize
	cvtColor(imgRotated, grayscaleFrame, CV_BGR2GRAY);
	equalizeHist(grayscaleFrame, grayscaleFrame);

	//create a vector array to store the face found
	std::vector<Rect> faces;

	//find faces and store them in the vector array
	face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 1, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(100, 100));

	//draw a rectangle for all found faces in the vector array on the original image
	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(imgRotated, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 4, 8, 0);

		Mat faceROI = grayscaleFrame(faces[i]);

		//-- Detect eyes
		std::vector<Rect> eyes;
		std::vector<Point> eyePoints;
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < eyes.size(); j++)
		{
			if (j == 2)
				break;
			Point center(faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5);
			eyePoints.push_back(center);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(imgRotated, center, radius, Scalar(255, 0, 0), 4, 8, 0);

		}

		if (eyePoints.size() > 1)
		{
			mY2 = eyePoints[1].y;
			mY1 = eyePoints[0].y;
			mX2 = eyePoints[1].x;
			mX1 = eyePoints[0].x;
			mEyeSlope = (-1.0 * ((mY2 - mY1) / (mX2 - mX1))) -DegreesToSlope(mDegRotate);


			//mEyeSlope = ((eyePoints[1].y) - (eyePoints[0].y)) / ((eyePoints[1].x) - (eyePoints[0].x));
		}

		if (mFaceLostCnt)
		{
			mFaceLostCnt = 0;
			mFaceFindAtmpt = 0;
		}
	}

	if (faces.size() == 0)
	{
		mDegRotSave = mDegRotate;
		mFaceLostCnt++;
	}
	//Service(eyeSlope);
	//print the output


	

	warpAffine(imgRotated, mDisplayFrame, mReverseRotation, captureFrame.size(), INTER_LINEAR, 0, Scalar());

	char str[200];
	sprintf_s(str, "Slope of Eye Plane: %f", mEyeSlope);
	putText(mDisplayFrame, str, cvPoint(30, 30),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);

	mDegrees = SlopeToDegrees(mEyeSlope);

	char str2[200];
	sprintf_s(str2, "Degrees of Eye Plane: %f", mDegrees);
	putText(mDisplayFrame, str2, cvPoint(30, 70),
		FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);


	imshow(mWindowName, mDisplayFrame);
	moveWindow(mWindowName, m_windowLocX, m_windowLocY);

	//mDisplayableFrame = &mDisplayFrame;
	//This is required to display properly for some reason
	waitKey(33);
	CalcDegRotate(); //Calculate possible offset for next image
}

double CImageProcess::SlopeToDegrees(double slope)
{
	return atan(mEyeSlope) * 180.0 / 3.14159265;
}

double CImageProcess::DegreesToSlope(double deg)
{
	return tan(deg * 3.14159265 / 180.0);
}

void CImageProcess::CalcDegRotate()
{
	mDegRotate = mDegrees * -0.9; //0.9 is the leveling factor
}

void CImageProcess::RapidFindFace()
{
	if (mDegrees < 0)
	{
		mDegRotate = 40 - (mFaceFindAtmpt * 10);
	}
	else if (mDegrees > 0)
	{
		mDegRotate = -40 + (mFaceFindAtmpt * 10);
	}
	else
	{
		mDegRotate = 0.0;
	}
	mFaceFindAtmpt++;
}
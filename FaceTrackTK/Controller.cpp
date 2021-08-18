/**
* \file Controller.h
*
* \author Tyler Lux
* Main controller application 
*
*/
#include "stdafx.h"
#include "Controller.h"

using namespace std;
using namespace cv;

CController::CController()
{

}


CController::~CController()
{
}

void CController::Init()
{
	mImage.Init(); 
}

void CController::SystemControl()
{
	mImage.ProcessImage();
	Service();
}

void CController::Service()
{
	//0x51 = 'Q'  0x45 = 'E'
	switch (mState)
	{
	case Center://  T                     F
		if ((mImage.GetDegrees() <= mRightMax) && (mImage.GetDegrees() >= mLeftMax))
			break;
		else if (mImage.GetDegrees() > mRightMax)
		{
			SetState(LeanRight);
		}
		else if (mImage.GetDegrees() < mLeftMax)
		{
			SetState(LeanLeft);
		}
		break;

	case Left:
		if (mImage.GetDegrees() < mLeftMax)
		{
			//KeyQ();
			break;
		}
		else if (mImage.GetDegrees() >= mLeftMax)
			SetState(LeftToCenter);
		break;

	case Right:
		if (mImage.GetDegrees() > mRightMax)
		{
			//KeyE();
			break;
		}
		else if (mImage.GetDegrees() <= mRightMax)
			SetState(RightToCenter);
		break;

	case LeanLeft:
		mKeys.KeyL();
		SetState(Left);
		break;

	case LeanRight:
		mKeys.KeyR();
		SetState(Right);
		break;

	case LeftToCenter:
		if (m_toggleBackL)
			mKeys.KeyL();
		SetState(Center);
		break;

	case RightToCenter:
		if (m_toggleBackR)
			mKeys.KeyR();
		SetState(Center);
		break;

	default:
		break;
	}
}

/** Set a state
* \param state The new state to set
*/
void CController::SetState(States state)
{
	mState = state;
	//mStateTime = 0;
	// Entry activities for states
	switch (mState)
	{
	case Center:
		mState = Center;
		break;

	case Left:
		mState = Left;
		break;

	case Right:
		mState = Right;
		break;

	case LeanLeft:
		mState = LeanLeft;
		Service();
		break;

	case LeftToCenter:
		mState = LeftToCenter;
		break;

	case LeanRight:
		mState = LeanRight;
		Service();
		break;

	case RightToCenter:
		mState = RightToCenter;
		break;

	default:
		break;
	}
}


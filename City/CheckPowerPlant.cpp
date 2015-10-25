/**
 * \file CheckPowerPlant.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include <stack>
#include "CheckPowerPlant.h"

using namespace std;

CCheckPowerPlant::CCheckPowerPlant()
{
}


CCheckPowerPlant::~CCheckPowerPlant()
{
}

void CCheckPowerPlant::VisitPower(CTilePower* power)
{
	mTotalPowerProduction += power->GetPowerPruducton();
	mType = power->GetPowerType();

	if (mType == CTilePower::POWERPLANT || mType == CTilePower::SOLARSTATION)
	{
		mIsPowerPlant = true;
	}
	else
	{
		mIsPowerPlant = false;
	}
}
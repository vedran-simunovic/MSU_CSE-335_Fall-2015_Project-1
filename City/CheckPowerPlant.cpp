/**
 * \file CheckPowerPlant.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include <stack>
#include "CheckPowerPlant.h"

using namespace std;

/**
 * 		  Constructor
 */
CCheckPowerPlant::CCheckPowerPlant()
{
}


/**
 * 		  Destructor
 */
CCheckPowerPlant::~CCheckPowerPlant()
{
}


/** Visits a power tile, ups the total production, sets the type, sets if is power plant or not
 * 
 * \param power tile
 */
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
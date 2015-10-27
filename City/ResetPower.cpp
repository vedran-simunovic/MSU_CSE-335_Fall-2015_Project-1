/**
 * \file ResetPower.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "ResetPower.h"
#include "TilePower.h"

/**Constructor
*
*/
CResetPower::CResetPower()
{
}

/** Destructor
*
*/
CResetPower::~CResetPower()
{
}


/** Visits a power tile, resets it
 * 
 * \param power tile
 */
void CResetPower::VisitPower(CTilePower* power)
{
	power->Reset();
}
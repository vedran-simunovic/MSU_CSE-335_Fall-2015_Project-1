/**
 * \file FindGrid.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "FindGrid.h"
#include "TilePower.h"


/** Constructor
 * 
 */
CFindGrid::CFindGrid()
{
}

/** Destructor
*
*/
CFindGrid::~CFindGrid()
{
}


/**
 * find the adjacent grid tile
 * \param power the power tile we are visiting
 */
void CFindGrid::VisitPower(CTilePower* power)
{
	if (power->CheckConnected())
	{
		mAdjacentConnected = true;
	}
	
}


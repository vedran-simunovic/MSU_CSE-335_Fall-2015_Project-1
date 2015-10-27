/**
 * \file FindGrid.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "FindGrid.h"
#include "TilePower.h"


CFindGrid::CFindGrid()
{
}


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


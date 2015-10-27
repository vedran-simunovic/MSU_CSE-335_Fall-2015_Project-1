/**
 * \file FindGrid.cpp
 *
 * \author Helena Narowski
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

/** Checks if connected, sets member variable mAdjacentConnected if so
* Sets member variable to true if power tile is connected
*/
void CFindGrid::VisitPower(CTilePower* power)
{
	if (power->CheckConnected())
	{
		mAdjacentConnected = true;
	}
	
}


/**
 * \file CoalCounter.cpp
 *
 * \author Vedran Simunovic
 */

#include "stdafx.h"
#include "CoalCounter.h"
#include "TileCoalmine.h"

/**
* Constructor
*/
CCoalCounter::CCoalCounter()
{
}

/**
* Destructor
*/
CCoalCounter::~CCoalCounter()
{
}

/**
* The visit coal mine function is used by the visitor
* \param coalmine The coalmine that is visited by the visitor
*/
void CCoalCounter::VisitCoalmine(CTileCoalmine *coalmine)
{
	mTotalCoal += coalmine->GetProduction();
}

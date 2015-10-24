/**
* \file CoalCounter.cpp
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*/

#include "stdafx.h"
#include "OreCounter.h"
#include "TileOremine.h"

COreCounter::COreCounter()
{
}


COreCounter::~COreCounter()
{
}

/**
* The visit coal mine function is used by the visitor
* \param coalmine The coalmine that is visited by the visitor
*/
void COreCounter::VisitOremine(CTileOremine *oremine)
{
	mTotalOre += oremine->GetProduction();
}

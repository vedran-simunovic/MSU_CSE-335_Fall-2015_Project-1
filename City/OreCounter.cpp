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
* The visit ore mine function is used by the visitor
* \param oremine The oremine that is visited by the visitor
*/
void COreCounter::VisitOremine(CTileOremine *oremine)
{
	mTotalOre += oremine->GetProduction();
}

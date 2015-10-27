#include "stdafx.h"
#include "FindGrid.h"
#include "TilePower.h"


CFindGrid::CFindGrid()
{
}


CFindGrid::~CFindGrid()
{
}

void CFindGrid::VisitPower(CTilePower* power)
{
	if (power->CheckConnected())
	{
		mAdjacentConnected = true;
	}
	
}


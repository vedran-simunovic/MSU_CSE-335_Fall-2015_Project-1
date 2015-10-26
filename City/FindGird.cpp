#include "stdafx.h"
#include "FindGird.h"
#include "TilePower.h"


CFindGird::CFindGird()
{
}


CFindGird::~CFindGird()
{
}

void CFindGird::VisitPower(CTilePower* power)
{
	if (power->CheckConnected())
	{
		mAdjacentConnected = true;
	}
	
}


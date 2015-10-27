/**
 * \file ResetPower.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "ResetPower.h"
#include "TilePower.h"


CResetPower::CResetPower()
{
}


CResetPower::~CResetPower()
{
}

void CResetPower::VisitPower(CTilePower* power)
{
	power->Reset();
}
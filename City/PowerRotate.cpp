/**
 * \file PowerRotate.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "PowerRotate.h"
#include "TilePower.h"


CPowerRotate::CPowerRotate()
{
}


CPowerRotate::~CPowerRotate()
{
}


/**
 * Visit power to rotate image
 * \param power 
 */
void CPowerRotate::VisitPower(CTilePower *power)
{
	power->RotateImage();
}
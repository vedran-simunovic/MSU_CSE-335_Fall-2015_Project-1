/**
 * \file PowerRotate.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 */

#include "stdafx.h"
#include "PowerRotate.h"
#include "TilePower.h"

/**Constructor
*
*/
CPowerRotate::CPowerRotate()
{
}

/**Destructor
*
*/
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
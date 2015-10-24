/**
 * \file PowerRotate.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * visitor for rotate image
 */

#pragma once
#include "TileVisitor.h"
#include "TilePower.h"


/** Concrete visitor to rotate power tile
 * rotates the power file
 */
class CPowerRotate :
	public CTileVisitor
{
public:
	CPowerRotate();
	virtual ~CPowerRotate();

	void VisitPower(CTilePower *power);

};


/**
 * \file PowerRotate.h
 *
 * \author Nan Du
 *
 * visitor for rotate image
 */

#pragma once
#include "TileVisitor.h"
#include "TilePower.h"
class CPowerRotate :
	public CTileVisitor
{
public:
	CPowerRotate();
	virtual ~CPowerRotate();

	void VisitPower(CTilePower *power);

};


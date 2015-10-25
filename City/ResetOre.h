/**
* \file ResetOre.h
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*
*/

#pragma once
#include "TileVisitor.h"

/**
* ResetOre is a concrete visitor
* that resets the production and
* duration values of the Oremine
* of interest back to 0.
*/
class CResetOre :
	public CTileVisitor
{
public:
	CResetOre();
	~CResetOre();

	void VisitOremine(CTileOremine *Oremine);
};


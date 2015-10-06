/**
 * \file Trump.h
 *
 * \author Vedran Simunovic
 *
 * Trump concrete visitor
 */

#pragma once
#include "TileVisitor.h"
/**
 * This class implements the Trump visitor
 * It changes the trump setting for the coalmine
 * of interest.
 */
class CTrump :
	public CTileVisitor
{
public:
	CTrump();
	~CTrump();

	
	void VisitCoalmine(CTileCoalmine *coalmine);
};


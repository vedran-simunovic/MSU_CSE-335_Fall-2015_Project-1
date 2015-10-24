/**
 * \file ResetCoal.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 * 
 */

#pragma once
#include "TileVisitor.h"

/**
 * ResetCoal is a concrete visitor
 * that resets the production and
 * duration values of the coalmine
 * of interest back to 0.
 */
class CResetCoal :
	public CTileVisitor
{
public:
	CResetCoal();
	~CResetCoal();

	void VisitCoalmine(CTileCoalmine *coalmine);
};


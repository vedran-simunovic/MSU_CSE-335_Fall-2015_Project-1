/**
* \file TileCount.h
*
* \author Vedran Simunovic
*
* Tile counter concrete visitor
*/

#pragma once
#include "TileVisitor.h"

/**
* This implements the tile counter
* concrete visitor.
*/
class CTileCount :
	public CTileVisitor
{
public:
	CTileCount();
	virtual ~CTileCount();

	/** Get the number of tiles
	* \returns Number of tiles */
	int GetNumTiles() const { return mNumTiles; }

	void VisitTiles();

private:
	/// Buildings counter
	int mNumTiles = 0;
};


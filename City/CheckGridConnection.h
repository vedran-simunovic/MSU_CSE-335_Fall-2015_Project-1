/**
 * \file CheckGridConnection.h
 *
 * \author Nan Du
 *
 * visitor class for check connection of grid to powerplant
 */

#pragma once
#include "TileVisitor.h"


/**
 * visitor class for check connection of grid to powerplant
 */
class CCheckGridConnection :
	public CTileVisitor
{
public:
	CCheckGridConnection();
	virtual ~CCheckGridConnection();

	/** Visit a CTilePower object
	* \param power we are visiting */
	virtual void VisitPower(CTilePower* power) override;

	/** Test the tile if the tile already been visited
	* \return mSkipForVisited whether we need skip this tile for DFS */
	bool NeedSkip() { return mSkipForVisited; }

private:
	bool mSkipForVisited = false;	///< whether need to skip
};


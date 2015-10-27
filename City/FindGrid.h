/**
 * \file FindGrid.h
 *
 * \author Nan Du
 *
 * visitor class for find the grid tile adjacent to tile
 */

#pragma once
#include "TileVisitor.h"


/**
 *  visitor class for find the grid tile adjacent to tile
 */
class CFindGrid :
	public CTileVisitor
{
public:
	CFindGrid();
	virtual ~CFindGrid();

	void VisitPower(CTilePower* power) override;

	/** test if the tile has a adjacent power tiles connected to the power plant
	* \return mAdjacentConnected whether the tile has a adjacent power tiles connected to the power plant */
	bool IsConnected() { return mAdjacentConnected; }

private:
	bool mAdjacentConnected = false;	///< whether the tile has a adjacent power tiles connected to the power plant
};


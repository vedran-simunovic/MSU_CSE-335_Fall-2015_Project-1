/**
 * \file BuildingCounter.h
 *
 * \author Vedran Simunovic
 *
 * Building counter concrete visitor
 */

#pragma once
#include "TileVisitor.h"

/**
 * This implements the building counter
 * concrete visitor.
 */
class CBuildingCounter :
	public CTileVisitor
{
public:
	CBuildingCounter();
	~CBuildingCounter();


	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	void VisitBuilding(CTileBuilding *building);

private:
	/// Buildings counter
	int mNumBuildings = 0;
};


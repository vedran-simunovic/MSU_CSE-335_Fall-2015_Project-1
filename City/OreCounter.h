/**
 * \file OreCounter.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * Ore Counter Concrete visitor
 */

#pragma once
#include "TileVisitor.h"
/**
* This classs implements the coal
* counter concrete visitor. It goes to
* all of the coalmines and counts the total
* coal production.
*/
class COreCounter :
	public CTileVisitor
{
public:
	COreCounter();
	~COreCounter();

	void VisitOremine(CTileOremine *oremine);

	/** Returns the amount of coal that is in the coalmine
	* \returns mTotalCoal This is the amount of coal in that 1 particular coalmine */
	double GetTotalProduction() { return mTotalOre; }

private:
	/// Total coal that the concrete visitor has counted so far
	double mTotalOre = 0;
};



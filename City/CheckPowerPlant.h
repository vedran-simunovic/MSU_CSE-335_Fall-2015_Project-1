/**
 * \file CheckPowerPlant.h
 *
 * \author Nan Du
 *
 * power plant visitor
 */

#pragma once
#include <memory>
#include <vector>
#include "TileVisitor.h"
#include "TilePower.h"


/**
 * power plant visitor
 */
class CCheckPowerPlant :
	public CTileVisitor
{
public:
	CCheckPowerPlant();
	virtual ~CCheckPowerPlant();

	void VisitPower(CTilePower* power) override;

	/** Test the tile if the tile is power plant
	* \return whether this is power plant tile */
	bool CheckPowerPlant() { return mIsPowerPlant; }

	/** get the power production of whole city
	* \return mTotalPowerProduction total production or power plant */
	int GetProduction() { return mTotalPowerProduction; }

private:
	int mTotalPowerProduction = 0;	///< total power production

	CTilePower::PowerType mType;	///< power tile type

	bool mIsPowerPlant = false;		///< if the tile is power plant
};


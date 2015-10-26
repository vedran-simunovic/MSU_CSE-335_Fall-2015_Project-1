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

class CCheckPowerPlant :
	public CTileVisitor
{
public:
	CCheckPowerPlant();
	virtual ~CCheckPowerPlant();

	void VisitPower(CTilePower* power) override;

	bool CheckPowerPlant() { return mIsPowerPlant; }

	int GetProduction() { return mTotalPowerProduction; }

private:
	int mTotalPowerProduction = 0;

	CTilePower::PowerType mType;

	bool mIsPowerPlant = false;
};


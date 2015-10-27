/**
 * \file ResetPower.h
 *
 * \author Nan Du
 *
 * class for reset power tile connection status
 */

#pragma once
#include "TileVisitor.h"

/**
 * class for reset power tile connection status
 */
class CResetPower :
	public CTileVisitor
{
public:
	CResetPower();
	virtual ~CResetPower();

	/** Visit a CTilePower object
	* \param power we are visiting */
	void VisitPower(CTilePower* power) override;

};

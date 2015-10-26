#pragma once
#include "TileVisitor.h"
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

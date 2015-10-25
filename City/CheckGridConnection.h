#pragma once
#include "TileVisitor.h"
class CCheckGridConnection :
	public CTileVisitor
{
public:
	CCheckGridConnection();
	virtual ~CCheckGridConnection();

	/** Visit a CTilePower object
	* \param power we are visiting */
	virtual void VisitPower(CTilePower* power) override;

	bool NeedSkip() { return mSkipForVisited; }

private:
	bool mSkipForVisited = false;
};


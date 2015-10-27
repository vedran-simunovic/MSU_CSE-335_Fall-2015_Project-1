#pragma once
#include "TileVisitor.h"
class CFindGrid :
	public CTileVisitor
{
public:
	CFindGrid();
	virtual ~CFindGrid();

	void VisitPower(CTilePower* power) override;

	bool IsConnected() { return mAdjacentConnected; }

private:
	bool mAdjacentConnected = false;
};


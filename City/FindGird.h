#pragma once
#include "TileVisitor.h"
class CFindGird :
	public CTileVisitor
{
public:
	CFindGird();
	virtual ~CFindGird();

	void VisitPower(CTilePower* power) override;

	bool IsConnected() { return mAdjacentConnected; }

private:
	bool mAdjacentConnected = false;
};


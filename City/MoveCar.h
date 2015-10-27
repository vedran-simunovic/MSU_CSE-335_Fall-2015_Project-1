/**
 * \file MoveCar.h
 *
 * \author Helena Narowski
 *
 * 
 */

#pragma once

#include <utility>

#include "TileVisitor.h"
/**
 * 
 */
class CMoveCar :
	public CTileVisitor
{
public:
	CMoveCar();
	virtual ~CMoveCar();

	void VisitTrans(CTileTransportation *trans);

	//int GetKey() { return mKey; }
	//void SetKey(int key) { mKey = key; }

	bool CheckIfValidRoad(CTileTransportation *trans);
	bool CheckValidFlat(CTileTransportation *trans);
	//bool CheckValidCurved(CTileTransportation *trans);

	//std::pair<int,int> GetCoordinates() { return mCoordinates; }

	//void SetCoordinates(int x, int y) { mCoordinates = std::make_pair(x, y); }

private:
	//int mKey = 0;
	//std::pair<int, int> mCoordinates;
	bool mValid = false;

};


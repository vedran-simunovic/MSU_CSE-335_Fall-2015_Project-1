/**
 * \file TransConnect.h
 *
 * \author Helena Narowski
 *
 * 
 */

#pragma once
#include "TileVisitor.h"

/**
 * 
 */
class CTransConnect :
	public CTileVisitor
{
public:
	/// The possible transportation tile types
	enum TransTileTypeConnect
	{
		NONE = 0,///< No current zoning
		PLAIN = 1, /// Plain tile
		FLAT = 2, /// Flat tile
		CURVED = 3, /// Curved tile
		INCLINED = 4, /// Inclined tile
		ELEVATED = 5, /// Elevated tile
	};	 ///< Transportation levels

	CTransConnect();
	virtual ~CTransConnect();

	void VisitTrans(CTileTransportation *trans);

	//bool CheckIfValidRoad(CTileTransportation *trans);
	//bool CheckValidFlat(CTileTransportation *trans);
	//bool CheckValidCurved(CTileTransportation *trans);

	int GetRotation() { return mRotation; }
	void SetRotation(int rot) { mRotation = rot; }

	//int GetDirection() { return mDirection; }
	//void SetDirection(int direction) { mDirection = direction; }

	TransTileTypeConnect GetType() { return mTransTileTypeConnect; }
	void SetType(int type) { mTransTileTypeConnect = (TransTileTypeConnect)type; }

private:
	int mRotation = 0;
	//int mDirection = 0; //0 = left, 1 = right, 2 = up, 3 = down (arrow keys)
	TransTileTypeConnect mTransTileTypeConnect = NONE;

};


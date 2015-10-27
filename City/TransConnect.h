/**
 * \file TransConnect.h
 *
 * \author Helena Narowski
 *
 * Implements the connect visitor
 */

#pragma once
#include "TileVisitor.h"

/**
 * Connect visitor concrete visitor implementation
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

	/** Gets the rotation of the road
	* \returns mRotation The amount rotated */
	int GetRotation() { return mRotation; }

	/** Sets the rotation of the road
	* \param rot The amount to be rotated */
	void SetRotation(int rot) { mRotation = rot; }

	//int GetDirection() { return mDirection; }
	//void SetDirection(int direction) { mDirection = direction; }

	/** Gets the type of the tile
	* \returns mTransTileTypeConnect The type of the tile connected */
	TransTileTypeConnect GetType() { return mTransTileTypeConnect; }

	/** Sets the type of the tile
	* \param type The type of the tile to connected */
	void SetType(int type) { mTransTileTypeConnect = (TransTileTypeConnect)type; }

private:
	int mRotation = 0; ///< The amount the tile is rotated
	//int mDirection = 0; //0 = left, 1 = right, 2 = up, 3 = down (arrow keys)
	TransTileTypeConnect mTransTileTypeConnect = NONE; ///< The type of the connected tile

};


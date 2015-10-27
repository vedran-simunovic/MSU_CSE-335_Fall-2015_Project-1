/**
 * \file MoveCar.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "MoveCar.h"
#include "TileTransportation.h"


/** Constructor
 * 
 */
CMoveCar::CMoveCar()
{
}


/** Destructor
 * 
 */
CMoveCar::~CMoveCar()
{
}


/** moves the car
* The visit car function is used by the visitor
* \param trans The Car that is visited by the visitor
*/
void CMoveCar::VisitTrans(CTileTransportation *trans)
{

	CheckIfValidRoad(trans);

}


/** Checks if the trans tile is a valid road connection to the other tile
*
* \param trans
* \returns
*/
bool CMoveCar::CheckIfValidRoad(CTileTransportation *trans)
{
	CTileTransportation::TransTileType transTileType = trans->GetTransType();

	if (transTileType == CTileTransportation::FLAT)
	{
		return CheckValidFlat(trans);
	}
	//else if (transTileType == CTileTransportation::CURVED)
	//{
	//	return CheckValidCurved(trans);
	//}
	//else if (transTileType == CTileTransportation::INCLINED)
	//{
	//	return CheckValidInclined(trans);
	//}
	//else if (transTileType == CTileTransportation::PLAIN)
	//{
	//	return CheckValidPlain(trans);
	//}
	//else if (transTileType == CTileTransportation::ELEVATED)
	//{
	//	return CheckValidElevated(trans);
	//}

	//return true;
}


/** Checks if the flat road is valid road
 * 
 * \param trans tile to check validity
 * \returns  true if valid false if not
 */
bool CMoveCar::CheckValidFlat(CTileTransportation *trans)
{
	/// this has the trans tile information of the one we're ON, and the one we're passing in is the one we want to move to.
	//bool valid = false;
	//int currentTileRot = this->GetRotation();
	//int requestedDirection = this->GetDirection();
	//if (currentTileRot == 0) // Flat has two rotations, 0 is sideways, 1 is up and down
	//{// can only move left and right
	//	if (requestedDirection == 2 || requestedDirection == 3)
	//	{
	//		return false; /// Cant move up or down (2 or 3)
	//	}
	//	else if (requestedDirection == 0) /// left
	//	{
	//		if (trans->GetTransType() == FLAT && trans->GetRotationPos() == 1) //1 is left and right for flat
	//		{
	//			valid = true;
	//		}
	//		else if (trans->GetTransType() == CURVED && trans->GetRotationPos() == 2)
	//		{
	//			valid = true;
	//		}
	//		else if (trans->GetTransType() == INCLINED && trans->GetRotationPos() == 3)
	//		{
	//			valid = true;
	//		}
	//		/// Can only move to road_cd, road_bd(itself, flat), and elevated roadrampa_db

	//	}
	//	else if (requestedDirection == 1) /// right
	//	{
	//		if (trans->GetTransType() == FLAT && trans->GetRotationPos() == 0) //1 is left and right for flat
	//		{
	//			valid = true;
	//		}
	//		else if (trans->GetTransType() == CURVED && trans->GetRotationPos() == 1)
	//		{
	//			valid = true;
	//		}
	//		else if (trans->GetTransType() == INCLINED && trans->GetRotationPos() == 1)
	//		{
	//			valid = true;
	//		}
	//		/// Can only move to road_cd, road_bd(itself, flat), and elevated roadrampa_db

	//	}
	//}
	return false;
}


/**
 * \file TransConnect.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "TransConnect.h"
#include "TileTransportation.h"


/**
 * 
 */
CTransConnect::CTransConnect()
{
}


/**
 * 
 */
CTransConnect::~CTransConnect()
{
}


/** Visit a CTileTransportation object
* \param trans Transportation we are visiting */
void CTransConnect::VisitTrans(CTileTransportation *trans)
{
	this->SetRotation(trans->GetRotationPos());
	this->SetType(int(trans->GetTransType()));
}

/**
 * 
 * \param trans 
 * \returns 
 */
bool CTransConnect::CheckIfValidRoad(CTileTransportation *trans) 
{
	CTileTransportation::TransTileType transTileType = trans->GetTransType(); 

	if (transTileType == CTileTransportation::FLAT)
	{
		return CheckValidFlat(trans);
	}
	else if (transTileType == CTileTransportation::CURVED)
	{
		return CheckValidCurved(trans);
	}
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

	return false;
}

bool CTransConnect::CheckValidFlat(CTileTransportation *trans)
{
	return false;
}

bool CTransConnect::CheckValidCurved(CTileTransportation *trans)
{
	return false;
}
/**
 * \file TransRotate.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "TransRotate.h"
#include "TileTransportation.h"


CTransRotate::CTransRotate()
{
}


CTransRotate::~CTransRotate()
{
}


/** Visit a CTileTransportation object
* \param trans Transportation we are visiting */
void CTransRotate::VisitTrans(CTileTransportation *trans)
{
	trans->IncrementRotationPos();

	CTileTransportation::TransTileType transTileType = trans->GetTransType();
	if (transTileType == CTileTransportation::FLAT)
	{
		RotateFlatTile(trans);
	}
	else if (transTileType == CTileTransportation::CURVED)
	{
		RotateCurvedTile(trans);
	}
	else if (transTileType == CTileTransportation::INCLINED)
	{
		RotateInclinedTile(trans);
	}
	else if (transTileType == CTileTransportation::PLAIN)
	{
		RotatePlainTile(trans);
	}
	else if (transTileType == CTileTransportation::ELEVATED)
	{
		RotateElevatedTile(trans);
	}
	// TODO: Rotate the tile 90  degrees or 120 degrees
}

void CTransRotate::RotateFlatTile(CTileTransportation *trans)
{
	int rotation = trans->GetRotationPos();

	switch (rotation)
	{
	case 0:
		trans->SetImage(L"road_ac.png");
		break;
	case 1:
		trans->SetImage(L"road_bd.png");
		break;
	}

}

void CTransRotate::RotateCurvedTile(CTileTransportation *trans)
{
	int rotation = trans->GetRotationPos();

	switch (rotation)
	{
	case 0:
		trans->SetImage(L"road_ab.png");
		break;
	case 1:
		trans->SetImage(L"road_bc.png");
		break;
	case 2:
		trans->SetImage(L"road_cd.png");
		break;
	case 3:
		trans->SetImage(L"road_ad.png");
		break;
	}
}

void CTransRotate::RotatePlainTile(CTileTransportation *trans)
{
	int rotation = trans->GetRotationPos();

	switch (rotation)
	{
	case 0:
		trans->SetImage(L"roadint_abc.png");
		break;
	case 1:
		trans->SetImage(L"roadint_abd.png");
		break;
	case 2:
		trans->SetImage(L"roadint_acd.png");
		break;
	case 3:
		trans->SetImage(L"roadint_bcd.png");
		break;
		/// There is also a fifth image for this. Will have to implement.
	}
}

void CTransRotate::RotateElevatedTile(CTileTransportation *trans)
{
	/// Also will have to implement the elevated with grass, and elevated with a middle cement thing.
	int rotation = trans->GetRotationPos();

	switch (rotation)
	{
	case 0:
		trans->SetImage(L"roadbridge_ac.png");
		break;
	case 1:
		trans->SetImage(L"roadbridge_bd.png");
		break;
	}
}

void CTransRotate::RotateInclinedTile(CTileTransportation *trans)
{
	int rotation = trans->GetRotationPos();

	switch (rotation)
	{
	case 0:
		trans->SetImage(L"roadrampa_ac.png");
		break;
	case 1:
		trans->SetImage(L"roadrampa_bd.png");
		break;
	case 2:
		trans->SetImage(L"roadrampa_ca.png");
		break;
	case 3:
		trans->SetImage(L"roadrampa_db.png");
		break;
	}
}
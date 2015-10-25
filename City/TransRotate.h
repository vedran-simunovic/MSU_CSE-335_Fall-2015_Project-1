/**
 * \file TransRotate.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * 
 */

#pragma once

#include "TileVisitor.h"


/** This implements the rotation of a transportation tile
 * concrete visitorss
 */
class CTransRotate:
	public CTileVisitor
{
public:
	CTransRotate();
	virtual ~CTransRotate();

	void VisitTrans(CTileTransportation *trans);
	
	void RotateFlatTile(CTileTransportation *trans);
	
	void RotateInclinedTile(CTileTransportation *trans);
	
	void RotateCurvedTile(CTileTransportation *trans);

	void RotatePlainTile(CTileTransportation *trans);

	void RotateElevatedTile(CTileTransportation *trans);


};


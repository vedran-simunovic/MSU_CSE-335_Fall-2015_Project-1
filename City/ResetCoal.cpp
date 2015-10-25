/**
 * \file ResetCoal.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 */

#include "stdafx.h"
#include "ResetCoal.h"
#include "TileCoalmine.h"

using namespace std;

/// Image when the coalmine is empty
const wstring EmptyImage = L"coalmine-empty.png";

/// Image when the coalmine promoted production is empty
const wstring EmptyPromotedImage = L"coalmine-emptyp.png";


/**
 * Constructor
 */
CResetCoal::CResetCoal()
{
}


/**
 * Destructor
 */
CResetCoal::~CResetCoal()
{
}

/**
 * The visit coal mine function is used by the visitor
 * \param coalmine The coalmine that is visited by the visitor
 */
void CResetCoal::VisitCoalmine(CTileCoalmine *coalmine)
{
	coalmine->SetDuration(0);
	coalmine->SetProduction(0);

	if (coalmine->GetTrump() != CTileCoalmine::SECOND_TRUMP)
	{
		if (coalmine->GetPromotionLevel() == CTileCoalmine::LEVEL_1)
			coalmine->SetImage(EmptyImage);
		else if (coalmine->GetPromotionLevel() == CTileCoalmine::LEVEL_2)
			coalmine->SetImage(EmptyPromotedImage);	
	}
}


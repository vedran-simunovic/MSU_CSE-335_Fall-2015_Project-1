/**
 * \file ResetCoal.cpp
 *
 * \author Vedran Simunovic
 */

#include "stdafx.h"
#include "ResetCoal.h"
#include "TileCoalmine.h"

using namespace std;

/// Image when the coalmine is empty
const wstring EmptyImage = L"coalmine-empty.png";


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
		coalmine->SetImage(EmptyImage);
}


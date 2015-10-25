/**
 * \file Trump.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 */

#include "stdafx.h"
#include "Trump.h"
#include "TileCoalmine.h"

/**
* Constructor
*/
CTrump::CTrump()
{
}

/**
* Destructor
*/
CTrump::~CTrump()
{
}

/** Visit a coalmine object
* \param coalmine Coalmine we are visiting */
void CTrump::VisitCoalmine(CTileCoalmine *coalmine)
{
	if (coalmine->GetTrump() == CTileCoalmine::FIRST_TRUMP)
	{
		coalmine->SetTrump(CTileCoalmine::SECOND_TRUMP);
	}

	if (coalmine->GetTrump() == CTileCoalmine::NO_TRUMP)
	{
		coalmine->SetTrump(CTileCoalmine::FIRST_TRUMP);
	}
}

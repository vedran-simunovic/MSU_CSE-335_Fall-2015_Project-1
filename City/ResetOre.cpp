/**
* \file ResetOre.cpp
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*/

#include "stdafx.h"
#include "ResetOre.h"
#include "TileOremine.h"

using namespace std;

/// Image when oremine starts. Oremine Step 1
const wstring Oremine1 = L"oremine1.png";

/// Image when promoted oremine starts. Oremine Step 1
const wstring OreminePromoted1 = L"oremine1p.png";


/**
* Constructor
*/
CResetOre::CResetOre()
{
}

/**
* Destructor
*/
CResetOre::~CResetOre()
{
}

/**
* The visit Ore mine function is used by the visitor
* \param oremine The Oremine that is visited by the visitor
*/
void CResetOre::VisitOremine(CTileOremine *oremine)
{
	oremine->SetProduction(0);
}
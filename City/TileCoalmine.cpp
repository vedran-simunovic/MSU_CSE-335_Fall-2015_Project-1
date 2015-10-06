/**
 * \file TileCoalmine.cpp
 *
 * \author Vedran Simunovic
 */

#include "stdafx.h"
#include "TileCoalmine.h"

using namespace std;
using namespace Gdiplus;

/// Image when the coalmine production is empty
const wstring EmptyImage = L"coalmine-empty.png";

/// Image when the coalmine production is low
const wstring LowProductionImage = L"coalmine-low.png";

/// Time to reach low production level in seconds
const double LowProductionTime = 5;

/// Tons of coal at low production level
const double LowProduction = 1;

/// Image when the coalmine production is Medium
const wstring MediumProductionImage = L"coalmine-med.png";

/// Time to reach Medium production level in seconds
const double MediumProductionTime = 6;

/// Tons of coal at Medium production level
const double MediumProduction = 2.5;

/// Image when the coalmine production is Full
const wstring FullProductionImage = L"coalmine-full.png";

/// Time to reach Full production level in seconds
const double FullProductionTime = 4;

/// Tons of coal at Full production level
const double FullProduction = 4;

/// Image when the coalmine is destroyed
const wstring DestroyedImage = L"burnt_land.png";

/** Constructor
* \param city The city this is a member of
*/
CTileCoalmine::CTileCoalmine(CCity *city) : CTile(city)
{
    SetImage(EmptyImage);
}

/**
* \brief Destructor
*/
CTileCoalmine::~CTileCoalmine()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileCoalmine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"coalmine");

    return itemNode;
}


/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileCoalmine::Update(double elapsed)
{
	CTile::Update(elapsed);

	SetDuration(GetDuration() + elapsed);

	// Double the production speed
	if (GetTrump() == FIRST_TRUMP)
	{
		SetTrumpScale();
	}


	if (GetTrump() != SECOND_TRUMP)
	{
		if (GetProduction() == 0 && GetDuration() >= LowProductionTime/GetTrumpScale())
		{
			// Don't redraw every time this is true
			if (GetProduction() != LowProduction)
				SetImage(LowProductionImage);

			SetProduction(LowProduction);
			SetDuration(0);
		}

		if (GetProduction() == LowProduction && GetDuration() >= MediumProductionTime/GetTrumpScale())
		{
			if (GetProduction() != MediumProduction)
				SetImage(MediumProductionImage);

			SetProduction(MediumProduction);
			SetDuration(0);
		}

		if (GetProduction() == MediumProduction && GetDuration() >= FullProductionTime/GetTrumpScale())
		{
			if (GetProduction() != FullProduction)
				SetImage(FullProductionImage);

			SetProduction(FullProduction);
			SetDuration(0);
		}
	}
	else
	{
		SetImage(DestroyedImage);

		SetProduction(0);
		SetDuration(0);
	}
}

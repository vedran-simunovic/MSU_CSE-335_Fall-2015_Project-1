/**
 * \file TilePower.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "TilePower.h"

using namespace std;
using namespace Gdiplus;

/// Image for grid
const wstring GridImage1 = L"power_ac.png";

/// Image for L-shapr grid
const wstring LGridImage1 = L"power_ab.png";

/// Image for T-shape grid
const wstring TGridImage1 = L"power_abc.png";

/// Image for X-shape grid
const wstring XGridImage = L"power_abcd.png";

/// Image for substation
const wstring SubstationImage = L"substation.png";

/// Image for power plant 
const wstring PowerPlantEmptyImage = L"powercoal0.png";

/// Image for solar station
const wstring SolarStationImage = L"powerssolar.png";

static wstring gridimages[] = {
	L"power_ac.png",     // 0
	L"power_bd.png",      // 1
	L"power_ac.png",      // 2
	L"power_bd.png"      // 3
};

static wstring lgridimages[] = {
	L"power_ab.png",     // 0
	L"power_bc.png",      // 1
	L"power_cd.png",      // 2
	L"power_ad.png"      // 3
};

static wstring tgridimages[] = {
	L"power_abc.png",     // 0
	L"power_bcd.png",      // 1
	L"power_acd.png",      // 2
	L"power_abd.png"      // 3
};

CTilePower::CTilePower(CCity *city, PowerType type) : CTile(city)
{
	mPowerType = type;

	switch (type)
	{
	case(GRID) : {
		SetImage(GridImage1);
		break;
	}
	case(LGRID) : {
		SetImage(LGridImage1);
		break;
	}
	case(TGRID) : {
		SetImage(TGridImage1);
		break;
	}
	case(XGRID) : {
		SetImage(XGridImage);
		break;
	}
	case(SUBSTATION) : {
		SetImage(SubstationImage);
		break;
	}
	case(POWERPLANT) : {
		SetImage(PowerPlantEmptyImage);
		break;
	}
	case(SOLARSTATION) : {
		SetImage(SolarStationImage);
		break;
	}
	}
}


CTilePower::~CTilePower()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTilePower::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"power");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTilePower::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
}


/**
 * Roateta image based on the type of power tile
 * \param type 
 */
void CTilePower::RotateImage()
{
	PowerType type = GetPowerType();
	switch (type)
	{
	case(GRID) : {
		if (mPowerDirection != NORTH){
			mPowerDirection = PowerDirection(mPowerDirection + 1);
			SetImage(gridimages[mPowerDirection]);
		}
		else{
			mPowerDirection = EAST;
			SetImage(GridImage1);
		}


		break;
	}
	case(LGRID) : {
		if (mPowerDirection != NORTH){
			mPowerDirection = PowerDirection(mPowerDirection + 1);
			SetImage(lgridimages[mPowerDirection]);
		}
		else{
			mPowerDirection = EAST;
			SetImage(LGridImage1);
		}


		break;
	}
	case(TGRID) : {
		if (mPowerDirection != NORTH){
			mPowerDirection = PowerDirection(mPowerDirection + 1);
			SetImage(tgridimages[mPowerDirection]);
		}
		else{
			mPowerDirection = EAST;
			SetImage(TGridImage1);
		}


		break;
	}
	}
}
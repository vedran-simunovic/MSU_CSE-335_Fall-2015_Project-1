/**
 * \file TilePower.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
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

/// Image for X-shape grid
const wstring SparkXGridImage = L"powerspark_abcd.png";

/// Image for substation
const wstring SubstationImage = L"substation.png";

/// Image for power plant 
const wstring PowerPlantEmptyImage = L"powercoal0.png";

/// Image for solar station
const wstring SolarStationImage = L"powerssolar.png";

/// Image for grid in differnt direction
static wstring gridimages[] = {
	L"power_ac.png",     // 0
	L"power_bd.png",      // 1
	L"power_ac.png",      // 2
	L"power_bd.png"      // 3
};

/// Image for lgrid in differnt direction
static wstring lgridimages[] = {
	L"power_ab.png",     // 0
	L"power_bc.png",      // 1
	L"power_cd.png",      // 2
	L"power_ad.png"      // 3
};

/// Image for tgrid in differnt direction
static wstring tgridimages[] = {
	L"power_abc.png",     // 0
	L"power_bcd.png",      // 1
	L"power_acd.png",      // 2
	L"power_abd.png"      // 3
};

/// Image for grid in differnt direction
static wstring sparkgridimages[] = {
	L"powerspark_ac.png",     // 0
	L"powerspark_bd.png",      // 1
	L"powerspark_ac.png",      // 2
	L"powerspark_bd.png"      // 3
};

/// Image for lgrid in differnt direction
static wstring sparklgridimages[] = {
	L"powerspark_ab.png",     // 0
	L"powerspark_bc.png",      // 1
	L"powerspark_cd.png",      // 2
	L"powerspark_ad.png"      // 3
};

/// Image for tgrid in differnt direction
static wstring sparktgridimages[] = {
	L"powerspark_abc.png",     // 0
	L"powerspark_bcd.png",      // 1
	L"powerspark_acd.png",      // 2
	L"powerspark_abd.png"      // 3
};


/**
 * constructor for tile power
 * \param city the city to hold this tile
 * \param type type of power tile
 */
CTilePower::CTilePower(CCity *city, PowerType type) : CTile(city)
{
	mPowerType = type;

	switch (type)
	{
	case(GRID) : {
		SetImage(GridImage1);
		mFile = GridImage1;
		break;
	}
	case(LGRID) : {
		SetImage(LGridImage1);
		mFile = LGridImage1;
		break;
	}
	case(TGRID) : {
		SetImage(TGridImage1);
		mFile = TGridImage1;
		break;
	}
	case(XGRID) : {
		SetImage(XGridImage);
		mFile = XGridImage;
		break;
	}
	case(SUBSTATION) : {
		SetImage(SubstationImage);
		mFile = SubstationImage;
		break;
	}
	case(POWERPLANT) : {
		SetImage(PowerPlantEmptyImage);
		mFile = PowerPlantEmptyImage;

		mPowerProduction = 20;
		mConnected = true;
		break;
	}
	case(SOLARSTATION) : {
		SetImage(SolarStationImage);
		mFile = SolarStationImage;
		mPowerProduction = 10;
		mConnected = true;
		break;
	}
	}
}


/**
 * destructor
 */
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
	itemNode->SetAttribute(L"power_tile_type", (int)GetPowerType());
	itemNode->SetAttribute(L"connected", (int)CheckConnected());
	itemNode->SetAttribute(L"power_direction", (int)GetPowerDirection());
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

	SetPowerType((CTilePower::PowerType)node->GetAttributeIntValue(L"power_tile_type", 0));
	SetConnection((bool)node->GetAttributeIntValue(L"connected", 0));
	SetPowerDirection((CTilePower::PowerDirection)node->GetAttributeIntValue(L"power_direction", 0));
	SetImage(node->GetAttributeValue(L"file", L""));
}


/**
 * Roateta image based on the type of power tile
 */
void CTilePower::RotateImage()
{
	PowerType type = GetPowerType();
	switch (type)
	{
		case(GRID) : 
		{
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
		case(LGRID) : 
		{
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
		case(TGRID) : 
		{
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

void CTilePower::SetConnection(bool connect) 
{ 
	mConnected = connect; 

	PowerType type = GetPowerType();

	if (mConnected)
	{
		switch (type)
		{
			case(GRID) :
			{

				SetImage(sparkgridimages[mPowerDirection]);
				break;
			}
			case(LGRID) :
			{
				SetImage(sparklgridimages[mPowerDirection]);
				break;
			}
			case(TGRID) :
			{
				SetImage(sparktgridimages[mPowerDirection]);
				break;
			}
			case(XGRID) :
			{
				SetImage(SparkXGridImage);
				break;
			}
		}
	}
}

void CTilePower::Reset()
{
	mConnected = false;
	SetVisited(false);
	PowerType type = GetPowerType();

	switch (type)
	{
		case(GRID) :
		{

			SetImage(gridimages[mPowerDirection]);
			break;
		}
		case(LGRID) :
		{
			SetImage(lgridimages[mPowerDirection]);
			break;
		}
		case(TGRID) :
		{
			SetImage(tgridimages[mPowerDirection]);
			break;
		}
		case(XGRID) :
		{
			SetImage(XGridImage);
			break;
		}
		case(POWERPLANT) :
		{
			mConnected = true;
			break;
		}
		case(SOLARSTATION) :
		{
			mConnected = true;
			break;
		}
	}
}
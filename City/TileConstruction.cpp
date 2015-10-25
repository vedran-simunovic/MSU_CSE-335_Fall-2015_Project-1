/**
* \file TileConstruction.cpp
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*
*/
#include "stdafx.h"
#include "TileConstruction.h"
#include "TilePropertiesDlg.h"

using namespace std;
using namespace Gdiplus;

/// Image when we load the potential construction site, clearing step 0
const wstring Clearing0 = L"grass1.png";

/// Image when clearing starts. Clearing Step 1
const wstring Clearing1 = L"clearing1.png";

/// Clearing Step 2
const wstring Clearing2 = L"clearing2.png";

/// Clearing Step 3
const wstring Clearing3 = L"clearing3.png";

/// Clearing Step 4
const wstring Clearing4 = L"clearing4.png";

/// Clearing Step 5
const wstring Clearing5 = L"clearing5.png";

/// Clearing Step 6
const wstring Clearing6 = L"clearing6.png";

/// Clearing Step 7
const wstring Clearing7 = L"clearing7.png";

/// Clearing Step 8
const wstring Clearing8 = L"clearing8.png";

/// Clearing transition rate
const double ClearingRate = 2; // seconds

/// How much we offset drawing the tile to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the tile above the center
const int OffsetDown = 32;

//For Spartan Stadium
/// How much we offset drawing the tile to the left of the center for the stadium
const int OffsetLeftStadium = OffsetLeft * 2;

/// How much we offset drawing the tile above the center for the stadium
const int OffsetDownStadium = OffsetDown * 2;

/** The directory were the images are stored */
const wstring ImagesDirectory = L"images/";



/** Constructor
* \param city The city this is a member of
*/
CTileConstruction::CTileConstruction(CCity *city) : CTile(city)
{
	// Default image drawn
	mFile = Clearing0;
	SetImage(Clearing0);

	// Immediately set the zoning because we will not be able to change
	// it later due to the feature that when we double click on a construction
	// tile, it actually starts the construction process.
	SetZoning(CTile::CONSTRUCTIONAL);

}

/**
* \brief Destructor
*/
CTileConstruction::~CTileConstruction()
{
}


/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileConstruction::Update(double elapsed)
{
	CTile::Update(elapsed);

	// Error check, reset the duration so overflow
	// and program crash does not occur
	if (mDuration < 0 || mDuration > 100)
		mDuration = 0;

	mDuration = mDuration + elapsed;

	// If construction is loaded with a non default image,
	// then the clear flag should be true
	if (GetClearingLevel() != CLEARING_0)
		SetClearFlag();
	
	// Start clearing sequence?
	//if (GetStatus() == NOT_COMPLETE && GetClearFlag() == true)
	if (mStartConstruction == false)
	{
		// Go to Clearing Step 1
		if (GetClearingLevel() == CLEARING_0 && mDuration > ClearingRate)
		{
			mFile = Clearing1;
			SetImage(Clearing1);
			SetClearingLevel(CLEARING_1);
			mDuration = 0;
		}

		// Go to Clearing Step 2
		if (GetClearingLevel() == CLEARING_1 && mDuration > ClearingRate)
		{
			mFile = Clearing2;
			SetImage(Clearing2);
			SetClearingLevel(CLEARING_2);
			mDuration = 0;
		}

		// Go to Clearing Step 3
		if (GetClearingLevel() == CLEARING_2 && mDuration > ClearingRate)
		{
			mFile = Clearing3;
			SetImage(Clearing3);
			SetClearingLevel(CLEARING_3);
			mDuration = 0;
		}

		// Go to Clearing Step 4
		if (GetClearingLevel() == CLEARING_3 && mDuration > ClearingRate)
		{
			mFile = Clearing4;
			SetImage(Clearing4);
			SetClearingLevel(CLEARING_4);
			mDuration = 0;
		}

		// Go to Clearing Step 5
		if (GetClearingLevel() == CLEARING_4 && mDuration > ClearingRate)
		{
			mFile = Clearing5;
			SetImage(Clearing5);
			SetClearingLevel(CLEARING_5);
			mDuration = 0;
		}

		// Go to Clearing Step 6
		if (GetClearingLevel() == CLEARING_5 && mDuration > ClearingRate)
		{
			mFile = Clearing6;
			SetImage(Clearing6);
			SetClearingLevel(CLEARING_6);
			mDuration = 0;
		}

		// Go to Clearing Step 7
		if (GetClearingLevel() == CLEARING_6 && mDuration > ClearingRate)
		{
			mFile = Clearing7;
			SetImage(Clearing7);
			SetClearingLevel(CLEARING_7);
			mDuration = 0;
		}

		// Go to Clearing Step 8
		if (GetClearingLevel() == CLEARING_7 && mDuration > ClearingRate)
		{
			mFile = Clearing8;
			SetImage(Clearing8);
			SetClearingLevel(CLEARING_8);
			mDuration = 0;
		}

		// Stop clearing
		if (GetClearingLevel() == CLEARING_8 && mDuration > ClearingRate)
		{
			SetStartFlag(true);
		}	
	} // end clearing sequence
}


/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileConstruction::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);
	itemNode->SetAttribute(L"clearing_state", (int)GetClearingLevel());
	return itemNode;
}

/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileConstruction::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetClearingLevel((CTileConstruction::Clearing)node->GetAttributeIntValue(L"clearing_state", 0));
}
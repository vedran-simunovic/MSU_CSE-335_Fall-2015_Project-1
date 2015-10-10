/**
* \file TileConstruction.cpp
*
* \author Vedran Simunovic
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

/// Stadium
const wstring Stadium = L"stadium.png";

/// Image when oremine starts. Oremine Step 1
const wstring Oremine1 = L"oremine1.png";

/// Oremine Step 2
const wstring Oremine2 = L"oremine2.png";

/// Oremine Step 3
const wstring Oremine3 = L"oremine3.png";

/// Oremine Step 4
const wstring Oremine4 = L"oremine4.png";

/// Oremine Step 5
const wstring Oremine5 = L"oremine5.png";

/// Oremine Step 6
const wstring Oremine6 = L"oremine6.png";

/// Oremine Step 7
const wstring Oremine7 = L"oremine7.png";

/// Oremine Step 8
const wstring Oremine8 = L"oremine8.png";

/// Clearing transition rate
const double ClearingRate = 2; // seconds

/// Oremine transition rate
const double OremineRate = 0.5; // seconds


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

	// Error check
	if (GetDuration() < 0)
		SetDuration(0);

	SetDuration(GetDuration() + elapsed);

	// If construction is loaded with a non default image,
	// then the clear flag should be true
	if (GetClearingLevel() != CLEARING_0)
		SetClearFlag();
	
	// Start clearing sequence?
	if (GetStatus() == NOT_COMPLETE && GetClearFlag() == true)
	{
		// Go to Clearing Step 1
		if (GetClearingLevel() == CLEARING_0 && GetDuration() > ClearingRate)
		{
			mFile = Clearing1;
			SetImage(Clearing1);
			SetClearingLevel(CLEARING_1);
			SetDuration(0);
		}

		// Go to Clearing Step 2
		if (GetClearingLevel() == CLEARING_1 && GetDuration() > ClearingRate)
		{
			mFile = Clearing2;
			SetImage(Clearing2);
			SetClearingLevel(CLEARING_2);
			SetDuration(0);
		}

		// Go to Clearing Step 3
		if (GetClearingLevel() == CLEARING_2 && GetDuration() > ClearingRate)
		{
			mFile = Clearing3;
			SetImage(Clearing3);
			SetClearingLevel(CLEARING_3);
			SetDuration(0);
		}

		// Go to Clearing Step 4
		if (GetClearingLevel() == CLEARING_3 && GetDuration() > ClearingRate)
		{
			mFile = Clearing4;
			SetImage(Clearing4);
			SetClearingLevel(CLEARING_4);
			SetDuration(0);
		}

		// Go to Clearing Step 5
		if (GetClearingLevel() == CLEARING_4 && GetDuration() > ClearingRate)
		{
			mFile = Clearing5;
			SetImage(Clearing5);
			SetClearingLevel(CLEARING_5);
			SetDuration(0);
		}

		// Go to Clearing Step 6
		if (GetClearingLevel() == CLEARING_5 && GetDuration() > ClearingRate)
		{
			mFile = Clearing6;
			SetImage(Clearing6);
			SetClearingLevel(CLEARING_6);
			SetDuration(0);
		}

		// Go to Clearing Step 7
		if (GetClearingLevel() == CLEARING_6 && GetDuration() > ClearingRate)
		{
			mFile = Clearing7;
			SetImage(Clearing7);
			SetClearingLevel(CLEARING_7);
			SetDuration(0);
		}

		// Go to Clearing Step 8
		if (GetClearingLevel() == CLEARING_7 && GetDuration() > ClearingRate)
		{
			mFile = Clearing8;
			SetImage(Clearing8);
			SetClearingLevel(CLEARING_8);
			SetDuration(0);
		}

		// Construct the random construction
		if (GetClearingLevel() == CLEARING_8 && GetDuration() > ClearingRate)
		{
			// Take the floating point "mDuration" and move the decimal over
			// This will move the decimal over by 8 places
			unsigned long long int random = GetDuration() * 100000000;

			// Test if that number is even or odd. This is the randomness
			if (random % 2 == 0)
				SetStatus(STADIUM);
			else
				SetStatus(OREMINE);

			SetDuration(0);
		}
	} // end clearing sequence

	if (GetStatus() == STADIUM)
	{
		mFile = Stadium;
		SetImage(Stadium);

		// Set duration to 0,
		// Otherwise duration will overflow at some point causing a crash in the program
		SetDuration(0);
	}

	// Start oremine sequence
	if (GetStatus() == OREMINE)
	{
		if (GetOremineLevel() == OREMINE_1 && GetDuration() > OremineRate)
		{
			mFile = Oremine1;

			SetImage(Oremine1);

			SetOremineLevel(OREMINE_2);

			SetRisingFlag(true);

			SetDuration(0);
		}
		
		if (GetOremineLevel() == OREMINE_2 && GetDuration() > OremineRate)
		{
			mFile = Oremine2;

			SetImage(Oremine2);

			if(GetRisingFlag() == true)
				SetOremineLevel(OREMINE_3);
			else
				SetOremineLevel(OREMINE_1);	

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_3 && GetDuration() > OremineRate)
		{
			mFile = Oremine3;

			SetImage(Oremine3);

			if (GetRisingFlag() == true)
				SetOremineLevel(OREMINE_4);
			else
				SetOremineLevel(OREMINE_2);

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_4 && GetDuration() > OremineRate)
		{
			mFile = Oremine4;

			SetImage(Oremine4);

			if (GetRisingFlag() == true)
				SetOremineLevel(OREMINE_5);
			else
				SetOremineLevel(OREMINE_3);

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_5 && GetDuration() > OremineRate)
		{
			mFile = Oremine5;

			SetImage(Oremine5);

			if (GetRisingFlag() == true)
				SetOremineLevel(OREMINE_6);
			else
				SetOremineLevel(OREMINE_4);

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_6 && GetDuration() > OremineRate)
		{
			mFile = Oremine6;

			SetImage(Oremine6);

			if (GetRisingFlag() == true)
				SetOremineLevel(OREMINE_7);
			else
				SetOremineLevel(OREMINE_5);

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_7 && GetDuration() > OremineRate)
		{
			mFile = Oremine7;

			SetImage(Oremine7);

			if (GetRisingFlag() == true)
				SetOremineLevel(OREMINE_8);
			else
				SetOremineLevel(OREMINE_6);

			SetDuration(0);
		}

		if (GetOremineLevel() == OREMINE_8 && GetDuration() > OremineRate)
		{
			mFile = Oremine8;

			SetImage(Oremine8);
			
			SetOremineLevel(OREMINE_7);

			SetRisingFlag(false);

			SetDuration(0);
		}
	} //end oremine state machine
		


}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileConstruction::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"construction");
	itemNode->SetAttribute(L"construction_state", (int)GetStatus());
	itemNode->SetAttribute(L"oremine_state", (int)GetOremineLevel());
	itemNode->SetAttribute(L"clearing_state", (int)GetClearingLevel());
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileConstruction::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	mX = node->GetAttributeIntValue(L"x", 0);
	mY = node->GetAttributeIntValue(L"y", 0);
	SetStatus((CTileConstruction::ConstructionStatus)node->GetAttributeIntValue(L"construction_state", 0));
	SetOremineLevel((CTileConstruction::OremineLevel)node->GetAttributeIntValue(L"oremine_state", 0));
	SetClearingLevel((CTileConstruction::Clearing)node->GetAttributeIntValue(L"clearing_state", 0));
	SetImage(node->GetAttributeValue(L"file", L""));
}


/**
* \brief Draw our tile
* \param graphics The graphics context to draw on
*/
void CTileConstruction::Draw(Gdiplus::Graphics *graphics, double offsetX, double offsetY)
{
	
	wstring filename = ImagesDirectory + mFile;
	auto mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mItemImage != nullptr)
	{
		int wid = mItemImage->GetWidth();
		int hit = mItemImage->GetHeight();

		graphics->DrawImage(mItemImage.get(),
			mX - OffsetLeft + offsetX, mY + OffsetDown - hit + offsetY,
			wid, hit);
	}

}


/** \brief Draw a border around the tile
* \param graphics The graphics context to draw on
* \param pen The pen to use to draw with
*/
void CTileConstruction::DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen)
{
	if (GetStatus() == STADIUM)
	{
		Point points[] = { { mX - OffsetLeftStadium + OffsetLeft, mY - OffsetDown }, { mX + OffsetLeft, mY - OffsetDownStadium - OffsetDown }, { mX + OffsetLeftStadium + OffsetLeft, mY - OffsetDown }, { mX + OffsetLeft, mY + OffsetDownStadium - OffsetDown }, { mX - OffsetLeftStadium + OffsetLeft, mY - OffsetDown } };

		graphics->DrawLines(pen, points, 5);
	}
	else
	{
		Point points[] = { { mX - OffsetLeft, mY }, { mX, mY - OffsetDown }, { mX + OffsetLeft, mY }, { mX, mY + OffsetDown }, { mX - OffsetLeft, mY } };

		graphics->DrawLines(pen, points, 5);
	}
}

void CTileConstruction::SetLocation(int x, int y)
{
	CTile::SetLocation(x, y);
	mX = x; 
	mY = y;
}
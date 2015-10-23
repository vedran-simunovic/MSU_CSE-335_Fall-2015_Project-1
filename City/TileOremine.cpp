/**
* \file TileOremine.cpp
*
* \author Vedran Simunovic
*/
#include "stdafx.h"
#include "TileOremine.h"

using namespace std;
using namespace Gdiplus;

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

/// Oremine transition rate
const double OremineRate = 0.5; // seconds

/** The directory were the images are stored */
const wstring ImagesDirectory = L"images/";

/// How much we offset drawing the tile to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the tile above the center
const int OffsetDown = 32;

/**
 * Constructor
 * \param city Passes the city object
 */
CTileOremine::CTileOremine(CCity *city) : CTileConstruction(city)
{
}


/**
 * Destructor
 */
CTileOremine::~CTileOremine()
{
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileOremine::Update(double elapsed)
{
	if(GetClearFlag() == true && mStartConstruction == false)
		CTileConstruction::Update(elapsed);

	// Error check
	if (mDuration < 0)
		mDuration = 0;

	mDuration = mDuration + elapsed;

	// Start oremine sequence
	if (mStartConstruction == true && mPowerOverlap == true)
	{
		if (mOremineLevel == OREMINE_1 && mDuration > OremineRate)
		{
			mFile = Oremine1;

			SetImage(Oremine1);

			SetOremineLevel(OREMINE_2);

			mRising = true;

			mDuration = 0;
		}
		
		if (mOremineLevel == OREMINE_2 && mDuration > OremineRate)
		{
			mFile = Oremine2;

			SetImage(Oremine2);

			if (mRising == true)
				SetOremineLevel(OREMINE_3);
			else
				SetOremineLevel(OREMINE_1);

			mDuration = 0;
		}

		if (mOremineLevel == OREMINE_3 && mDuration > OremineRate)
		{
			mFile = Oremine3;

			SetImage(Oremine3);

			if (mRising == true)
				SetOremineLevel(OREMINE_4);
			else
				SetOremineLevel(OREMINE_2);

			mDuration = 0;
		}

		if (mOremineLevel== OREMINE_4 && mDuration > OremineRate)
		{
			mFile = Oremine4;

			SetImage(Oremine4);

			if (mRising == true)
				SetOremineLevel(OREMINE_5);
			else
				SetOremineLevel(OREMINE_3);

			mDuration = 0;
		}

		if (mOremineLevel == OREMINE_5 && mDuration > OremineRate)
		{
			mFile = Oremine5;

			SetImage(Oremine5);

			if (mRising == true)
				SetOremineLevel(OREMINE_6);
			else
				SetOremineLevel(OREMINE_4);

			mDuration = 0;
		}

		if (mOremineLevel == OREMINE_6 && mDuration > OremineRate)
		{
			mFile = Oremine6;

			SetImage(Oremine6);
	
			if (mRising == true)
				SetOremineLevel(OREMINE_7);
			else
				SetOremineLevel(OREMINE_5);

			mDuration = 0;
		}

		if (mOremineLevel == OREMINE_7 && mDuration > OremineRate)
		{
			mFile = Oremine7;

			SetImage(Oremine7);
			
			if (mRising == true)
				SetOremineLevel(OREMINE_8);
			else
				SetOremineLevel(OREMINE_6);

			mDuration = 0;
		}

		if (mOremineLevel == OREMINE_8 && mDuration > OremineRate)
		{
			mFile = Oremine8;

			SetImage(Oremine8);

			SetOremineLevel(OREMINE_7);
			
			mRising = false;

			mDuration = 0;
		}
	} //end oremine state machine
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileOremine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTileConstruction::XmlSave(node);
	itemNode->SetAttribute(L"file", GetFile());
	itemNode->SetAttribute(L"type", L"oremine");
	itemNode->SetAttribute(L"oremine_state", (int)GetOremineLevel());

	if (mStartClearing == true)
		itemNode->SetAttribute(L"startClearing", L"true");
	else
		itemNode->SetAttribute(L"startClearing", L"false");

	if (mStartConstruction == true)
		itemNode->SetAttribute(L"startConstruction", L"true");
	else
		itemNode->SetAttribute(L"startConstruction", L"false");

	if (mRising == true)
		itemNode->SetAttribute(L"rising", L"true");
	else
		itemNode->SetAttribute(L"rising", L"false");

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileOremine::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileConstruction::XmlLoad(node);
	mStartClearing = node->GetAttributeBoolValue(L"startClearing", L"");
	mStartConstruction = node->GetAttributeBoolValue(L"startConstruction", L"");
	mRising = node->GetAttributeBoolValue(L"rising", L"");
	SetOremineLevel((CTileOremine::OremineAnimation)node->GetAttributeIntValue(L"oremine_state", 0));
	SetImage(node->GetAttributeValue(L"file", L""));
}

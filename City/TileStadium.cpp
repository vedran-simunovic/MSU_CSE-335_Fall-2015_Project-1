/**
* \file TileStadium.cpp
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*/

#include "stdafx.h"
#include "TileStadium.h"

using namespace std;
using namespace Gdiplus;

/// Stadium
const wstring Stadium = L"stadium.png";

/** The directory were the images are stored */
const wstring ImagesDirectory = L"images/";

/// How much we offset drawing the tile to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the tile above the center
const int OffsetDown = 32;

//For Spartan Stadium
/// How much we offset drawing the tile to the left of the center for the stadium
const int OffsetLeftStadium = OffsetLeft * 2;

/// How much we offset drawing the tile above the center for the stadium
const int OffsetDownStadium = OffsetDown * 2;

/**
* Constructor
* \param city Passes the city object
*/
CTileStadium::CTileStadium(CCity *city) : CTileConstruction(city)
{
	
}

/**
* Destructor
*/
CTileStadium::~CTileStadium()
{

}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileStadium::Update(double elapsed)
{
	if (mStartClearing == true && mStartConstruction == false)
		CTileConstruction::Update(elapsed);

	if (mStartConstruction == true && mStartClearing == true)
	{
		mFile = Stadium;
		SetImage(Stadium);
		mStartClearing = false;
	}
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileStadium::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTileConstruction::XmlSave(node);
	itemNode->SetAttribute(L"file", GetFile());
	itemNode->SetAttribute(L"type", L"stadium");

	if (mStartClearing == true)
		itemNode->SetAttribute(L"startClearing", L"true");
	else
		itemNode->SetAttribute(L"startClearing", L"false");

	if (mStartConstruction == true)
		itemNode->SetAttribute(L"startConstruction", L"true");
	else
		itemNode->SetAttribute(L"startConstruction", L"false");

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileStadium::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileConstruction::XmlLoad(node);
	mStartClearing = node->GetAttributeBoolValue(L"startClearing", L"");
	mStartConstruction = node->GetAttributeBoolValue(L"startConstruction", L"");
	mX = node->GetAttributeIntValue(L"x", 0);
	mY = node->GetAttributeIntValue(L"y", 0);
	SetImage(node->GetAttributeValue(L"file", L""));
}

/**
 *\brief Draw a border around the tile 
 * \param graphics he graphics context to draw on
 * \param pen The pen to use to draw with
 * \param scrollOffsetX offset on X axis for scrollling
 * \param scrollOffsetY offset on Y axis for scrollling
 * \param scale scale of drawing
 */
void CTileStadium::DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen, int scrollOffsetX, int scrollOffsetY, double scale)
{
	int mXOffset = scale*mX + scrollOffsetX;
	int mYOffset = scale*mY + scrollOffsetY;
	int OffsetLeftScaled = scale*OffsetLeft;
	int OffsetDownScaled = scale*OffsetDown;
	int OffsetLeftStadiumScaled = OffsetLeftStadium;
	int OffsetDownStadiumScaled = OffsetDownStadium;


	Point points[] = { { mXOffset - OffsetLeftStadiumScaled + OffsetLeftScaled, mYOffset - OffsetDownScaled }, { mXOffset + OffsetLeftScaled, mYOffset -

		OffsetDownStadiumScaled - OffsetDownScaled }, { mXOffset + OffsetLeftStadiumScaled + OffsetLeftScaled, mYOffset - OffsetDownScaled }, { mXOffset + OffsetLeftScaled, mYOffset +

		OffsetDownStadiumScaled - OffsetDownScaled }, { mXOffset - OffsetLeftStadiumScaled + OffsetLeftScaled, mYOffset - OffsetDownScaled } };
	graphics->DrawLines(pen, points, 5);

}


/** Sets the location of the construction
 * 
 * \param x coordinate
 * \param y coordinate
 */
void CTileStadium::SetLocation(int x, int y)
{
	CTileConstruction::SetLocation(x, y);
	mX = x;
	mY = y;
}
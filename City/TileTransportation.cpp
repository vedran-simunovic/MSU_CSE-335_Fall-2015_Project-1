/**
 * \file TileTransportation.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "TileTransportation.h"

using namespace std;
using namespace Gdiplus;

/// Image for curved road
const wstring CurvedImage1 = L"road_ab.png";

/// Image for flat
const wstring FlatImage1 = L"road_ac.png";

/// Image for elevated
const wstring ElevatedImage1 = L"roadbridge_ac.png";

/// Image for inclined
const wstring InclinedImage1 = L"roadrampa_ac.png";

/// Image for plain
const wstring PlainImage1 = L"roadint_abc.png";

/** Constructor
* \param city The city this is a member of
*/
CTileTransportation::CTileTransportation(CCity *city, TransTileType type) : CTile(city)
{
	SetAdjacencies(false, false, false, false);

	mTransType = type;

	switch (type)
	{
	case(PLAIN) : {
		SetImage(PlainImage1);
		SetTransType(CTileTransportation::PLAIN);
		mFile = PlainImage1;
		break;
	}
	case(FLAT) : {
		SetImage(FlatImage1);
		SetTransType(CTileTransportation::FLAT);
		mFile = FlatImage1;
		break;
	}
	case(CURVED) : {
		SetImage(CurvedImage1);
		SetTransType(CTileTransportation::CURVED);
		mFile = CurvedImage1;
		break;
	}
	case(INCLINED) : {
		SetImage(InclinedImage1);
		SetTransType(CTileTransportation::INCLINED);
		mFile = InclinedImage1;
		break;
	}
	case(ELEVATED) : {
		SetImage(ElevatedImage1);
		SetTransType(CTileTransportation::ELEVATED);
		mFile = ElevatedImage1;
		break;
	}
	}
}


/**
* \brief Destructor
*/
CTileTransportation::~CTileTransportation()
{

}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Pointer to the crated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileTransportation::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"transportation");
	itemNode->SetAttribute(L"rotation", GetRotationPos());
	itemNode->SetAttribute(L"trans_tile_type", (int)GetTransType());
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}

/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileTransportation::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);

	SetTransTileType((CTileTransportation::TransTileType)node->GetAttributeIntValue(L"trans_tile_type", 0));
	SetRotationPos(node->GetAttributeIntValue(L"rotation", 0));

	SetImage(node->GetAttributeValue(L"file", L""));
}


/**
* \brief Indicate the road tiles adjacent to this one
*
* The road time image chosen is dependent on the tiles around
* it. This is where the adjacency of road tiles is indicated.
*
* \param ul True if road tile to upper left
* \param ur True if road tile to upper right
* \param ll True if road tile to lower left
* \param lr True if road tile to lower right
*/
void CTileTransportation::SetAdjacencies(bool ul, bool ur, bool ll, bool lr)
{
	// Create the adjacency code
	int code = (ul ? 1 : 0) | (ur ? 2 : 0) | (ll ? 4 : 0) | (lr ? 8 : 0);
	if (mCurrentAdj == code)
	{
		// We are already set. Do nothing
		return;
	}

	static wstring files[] = {
		L"roadlr.png",      // 0
		L"roadlr.png",      // 1
		L"roadud.png",      // 2
		L"roadlu.png",      // 3
		L"roadud.png",      // 4
		L"roadld.png",      // 5
		L"roadud.png",      // 6
		L"roadlud.png",     // 7
		L"roadlr.png",      // 8
		L"roadlr.png",      // 9
		L"roadur.png",      // 10
		L"roadlur.png",     // 11
		L"roaddr.png",      // 12
		L"roadldr.png",     // 13
		L"roadudr.png",     // 14
		L"roadludr.png"    // 15
	};

	// Select the appropriate image
	mCurrentAdj = code;
	SetImage(files[code]);
}

void CTileTransportation::IncrementRotationPos()
{
	if (GetTransType() == CURVED || GetTransType() == INCLINED || GetTransType() == PLAIN)
	{
		if (mRotationPos < 3)
		{
			mRotationPos++;
		}
		else
		{
			mRotationPos = 0;
		}
	}
	else if (GetTransType() == FLAT || GetTransType() == ELEVATED)
	{
		if (mRotationPos < 1)
		{
			mRotationPos++;
		}
		else
		{
			mRotationPos = 0;
		}
	}
}
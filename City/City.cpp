/**
 * \file City.cpp
 *
 * \author Vedran Simunovic
 */

#include "stdafx.h"
#include <algorithm>
#include <cmath>

#include "City.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "TileConstruction.h"
#include "TileTransportation.h"
#include "TilePower.h"

using namespace std;
using namespace xmlnode;

/**
* Constructor
*/
CCity::CCity()
{
}

/**
* Destructor
*/
CCity::~CCity()
{
}


/** \brief Draw the city
* \param graphics The GDI+ graphics context to draw on
*/
void CCity::OnDraw(Gdiplus::Graphics *graphics, double offsetX, double offsetY)
{
    for (auto item : mTiles)
    {
        item->Draw(graphics, offsetX, offsetY);
    }
}


/** \brief Add a tile to the city
* \param tile New tile to add
*/
void CCity::Add(std::shared_ptr<CTile> tile)
{
    mTiles.push_back(tile);
}



/** \brief Test an x,y click location to see if it clicked
* on some item in the city.
* \param x X location
* \param y Y location
* \returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<CTile> CCity::HitTest(int x, int y, double offsetX, double offsetY)
{
    for (auto i = mTiles.rbegin(); i != mTiles.rend(); i++)
    {
        if ((*i)->HitTest(x, y, offsetX, offsetY))
        {
            return *i;
        }
    }

    return  nullptr;
}


/** \brief Move an item to the front of the list of items.
*
* Removes item from the list and adds it to the end so it
* will display last.
* \param item The item to move
*/
void CCity::MoveToFront(std::shared_ptr<CTile> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }

    mTiles.push_back(item);
}


/** \brief Delete an item from the aquarium
*
* \param item The item to delete.
*/
void CCity::DeleteItem(std::shared_ptr<CTile> item)
{
    auto loc = find(::begin(mTiles), ::end(mTiles), item);
    if (loc != ::end(mTiles))
    {
        mTiles.erase(loc);
    }
}


/** \brief Handle updates for animation
* \param elapsed The time since the last update
*/
void CCity::Update(double elapsed)
{
    for (auto item : mTiles)
    {
        item->Update(elapsed);
    }
}

/** \brief Save the city as a .city XML file.
*
* Open an XML file and stream the city data to it.
*
* \param filename The filename of the file to save the city to
*/
void CCity::Save(const std::wstring &filename)
{
    //
    // Create an XML document
    //
    auto root = CXmlNode::CreateDocument(L"city");

    // Iterate over all items and save them
    for (auto item : mTiles)
    {
        item->XmlSave(root);
    }

    try
    {
        root->Save(filename);
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}


/** \brief Load the city from a .city XML file.
*
* Opens the XML file and reads the nodes, creating items as appropriate.
*
* \param filename The filename of the file to load the city from.
*/
void CCity::Load(const std::wstring &filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Clear();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"tile")
            {
                XmlTile(node);
            }
        }

        //
        // All loaded, ensure all sorted
        //
        SortTiles();
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}



/**
* \brief Handle a tile node.
* \param node Pointer to XML node we are handling
*/
void CCity::XmlTile(const std::shared_ptr<CXmlNode> &node)
{
    // A pointer for the item we are loading
    shared_ptr<CTile> tile;

    // We have an item. What type?
    wstring type = node->GetAttributeValue(L"type", L"");
    if (type == L"landscape")
    {
        tile = make_shared<CTileLandscape>(this);
    }
    else if (type == L"building")
    {
        tile = make_shared<CTileBuilding>(this);
    }
    else if (type == L"road")
    {
        tile = make_shared<CTileRoad>(this);
    }
    else if (type == L"coalmine")
    {
        tile = make_shared<CTileCoalmine>(this);
    }
	else if (type == L"construction")
	{
		tile = make_shared<CTileConstruction>(this);
	}
	else if (type == L"transportation")
	{
		tile = make_shared<CTileTransportation>(this, CTileTransportation::NONE);
	}
	else if (type == L"power")
	{
		tile = make_shared<CTilePower>(this, CTilePower::NONE);
	}

    if (tile != nullptr)
    {
        tile->XmlLoad(node);
        Add(tile);
    }
}




/**
* \brief Clear the city data.
*
* Deletes all known items in the city.
*/
void CCity::Clear()
{
    mTiles.clear();
}




/**
 * \brief Ensure the tiles are in the correct drawing order.
 *
 * This draws bottom to top so the tiles can overlapp.
 * Also builds the adjacency support since this is called whenever
 * the city is reorganized.
 */
void CCity::SortTiles()
{
    // sort using a lambda expression 
    sort(::begin(mTiles), ::end(mTiles), 
        [](const shared_ptr<CTile> &a, const shared_ptr<CTile> &b) {
        if (a->GetY() < b->GetY())
            return true;

        if (a->GetY() > b->GetY())
            return false;

        return a->GetX() > b->GetX();
    });

    BuildAdjacencies();
}


/**
 * \brief Build support for fast adjacency testing.
 *
 * This builds a map of the grid locations of every tile, so we can
 * just look them up.
 */
void CCity::BuildAdjacencies()
{
    mAdjacency.clear();
    for (auto tile : mTiles)
    {
        mAdjacency[pair<int, int>(tile->GetX() / GridSpacing, 
            tile->GetY() / GridSpacing)] = tile;
    }
}



/**
 * \brief Get any adjacent tile.
 * 
 * Given a tile in the city, this determines if there is another
 * tile adjacent to it. The parameters dx, dy determine which direction
 * to look. 
 *
 * The values for specific adjacencies (dx, dy, and direction):
 *    - -1 -1 Upper left
 *    - 1 -1 Upper right
 *    - -1 1 Lower left
 *    - 1 1 Lower right
 * 
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CTile> CCity::GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy)
{
    return GetAdjacent(tile.get(), dx, dy);
}

/**
 * \brief Get any adjacent tile.
 * 
 * Identical to the other version, except this version accepts a
 * regular pointer instead of a shared_ptr. This allows the function
 * to be called from CTile, which only knows itself as a pointer.
 * 
 * \param tile Tile to test
 * \param dx Left/right determination, -1=left, 1=right
 * \param dy Up/Down determination, -1=up, 1=down
 * \returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CTile> CCity::GetAdjacent(CTile *tile, int dx, int dy)
{
    int atX = tile->GetX() / GridSpacing + dx * 2;
    int atY = tile->GetY() / GridSpacing + dy;

    auto adj = mAdjacency.find(pair<int, int>(atX, atY));
    if (adj != mAdjacency.end())
    {
        // We found it
        return adj->second;
    }

    //int atX = tile->GetX() + dx * GridSpacing * 2;
    //int atY = tile->GetY() + dy * GridSpacing;

    //for (auto testTile : mTiles)
    //{
    //    if (testTile->GetX() == atX &&
    //        testTile->GetY() == atY)
    //    {
    //        return testTile;
    //    }
    //}

    // If nothing found
    return nullptr;
}


//pass in the zoning
// make for loop to go through the entire thing. 
// go through for loop until you find the first zoning
// if no zoning found, the end result will be that begin() == end()
// iterator++ should only go to the next zoning...so this implementation will be in iter++ as well.

/** Get an iterator for the beginning of the collection
* \returns ZoningIter object at first zoning tile position of interest*/
CCity::ZoningIter CCity::ZoningIterSupport::begin()
{
	int startPosition = 0;

	for (auto i : mCity->mTiles)
	{
		if (mCity->mTiles[startPosition]->GetZoning() == mZoning)
		{
			return ZoningIter(mCity, startPosition, mZoning);
		}

		startPosition++;
	}
	
	//startPosition would now be equal to the position
	//of the last element by default. Since we are at this
	//point, that means the last position's element was not
	// of the correct zoning. The start position should then
	// be the equivalent of mTile->size() or just another
	// startPosition++ since if we increment by 1 once more,
	// we will be in that position

	//Correct zoning not found, so just make begin same as end.

	startPosition = mCity->mTiles.size();

	return ZoningIter(mCity, startPosition, mZoning);
}


/** Increment the iterator to the next tile of interest.
*   if no more tiles of interest are left, then increment to last element.
* \returns Reference to this iterator */
const CCity::ZoningIter & CCity::ZoningIter::operator ++ ()
{
	// This will basically only start to compare the mPos position
	// after the "mPos"-th position in the vector. There is no reason
	// to compare the previous elements of the vector because the goal is
	// to obtain the next position of the tile that actually is of the type
	// that we are looking for.
	int index = 0;
	
	for (auto i : mCity->mTiles)
	{
		if (index > mPos)
		{
			if (mCity->mTiles[index]->GetZoning() == mZoning)
			{
				mPos = index;
				return *this;
			}
		}

		index++;
	}

	// no more of those zonings objects in the mTiles vector
	mPos = mCity->mTiles.size();
	return *this;
}

/** Accept a visitor for the collection
* \param visitor The visitor for the collection
*/
void CCity::Accept(CTileVisitor *visitor)
{
	for (auto tile : mTiles)
	{
		tile->Accept(visitor);
	}
}

/** Count the number of tiles
* \param visitor The visitor for the collection
*/
int CCity::CountTiles()
{
	return mTiles.size();
}

int CCity::CountPartialOverlapping(double widT, double hitT)
{
	int totalOverlaps = 0;

	double iX;
	double iY;

	double jX;
	double jY;

	double centerX;
	double centerY;

	bool increment = false;

	for (auto tile : mTiles)
	{
		iX = tile->GetX();
		iY = tile->GetY();

		for (auto tile : mTiles)
		{
			centerX= tile->GetX();
			centerY = tile->GetY();

			//increment = false;

			jX = centerX - 64;
			jY = centerY;
			//Left Corner
			if ( abs(iX-jX) + 2*abs(iY-jY) <= 64 )
				increment = true;

			jX = centerX + 64;
			jY = centerY;
			//Right Corner
			if (abs(iX - jX) + 2 * abs(iY - jY) <= 64)
				increment = true;

			jX = centerX;
			jY = centerY + 32;
			//Top Corner
			if (abs(iX - jX) + 2 * abs(iY - jY) <= 64)
				increment = true;

			jX = centerX;
			jY = centerY - 32;
			//Bottom Corner
			if (abs(iX - jX) + 2 * abs(iY - jY) <= 64)
				increment = true;

			//Vedran's equation for a square

			//Nan's Equations for a diamond
			/*
			jX = centerX;
			jY = centerY - 32;
			//Bottom Corner
			if (jY - 0.5*jX - iY + 32 + 0.5*jX < 0 && jY - 0.5*jX - iY - 32 + 0.5*jX < 0 && jY + 0.5*jX - 0.5*iX - iY - 32 < 0 && jY + 0.5*jX - 0.5*iX - iY + 32 < 0)
				increment = true;
			
			jX = centerX - 64;
			jY = centerY;
			//Left Corner
			if (jY - 0.5*jX - iY + 32 + 0.5*jX < 0 && jY - 0.5*jX - iY - 32 + 0.5*jX < 0 && jY + 0.5*jX - 0.5*iX - iY - 32 < 0 && jY + 0.5*jX - 0.5*iX - iY + 32 < 0)
				increment = true;

			jX = centerX + 64;
			jY = centerY;
			//Right Corner
			if (jY - 0.5*jX - iY + 32 + 0.5*jX < 0 && jY - 0.5*jX - iY - 32 + 0.5*jX < 0 && jY + 0.5*jX - 0.5*iX - iY - 32 < 0 && jY + 0.5*jX - 0.5*iX - iY + 32 < 0)
				increment = true;

			jX = centerX;
			jY = centerY + 32;
			//Top Corner
			if (jY - 0.5*jX - iY + 32 + 0.5*jX < 0 && jY - 0.5*jX - iY - 32 + 0.5*jX < 0 && jY + 0.5*jX - 0.5*iX - iY - 32 < 0 && jY + 0.5*jX - 0.5*iX - iY + 32 < 0)
				increment = true;

			jX = centerX;
			jY = centerY - 32;
			//Bottom Corner
			if (jY - 0.5*jX - iY + 32 + 0.5*jX < 0 && jY - 0.5*jX - iY - 32 + 0.5*jX < 0 && jY + 0.5*jX - 0.5*iX - iY - 32 < 0 && jY + 0.5*jX - 0.5*iX - iY + 32 < 0)
				increment = true;
			*/

			if (increment == true)
				totalOverlaps++;

			increment = false;
		}
	}
	//return (totalOverlaps - mTiles.size()) / 2;
	return totalOverlaps;
	//x > trashcanTopLeftCornerX && x < trashcanTopLeftCornerX + widT
	//	&& y > trashcanTopLeftCornerY && y < trashcanTopLeftCornerY + hitT;

	// Take total overlaps
	// subtract the number of tiles from that number, i.e. getSize
	// divide that number by 2, to get the total overlaps and or
}

int CCity::CountFullyOverlapping(double widthOfScreen, double heightOfScreen)
{
	int totalOverlaps = 0;

	double centerXi;
	double centerYi;

	double centerXj;
	double centerYj;

	bool increment = false;

	for (auto tile : mTiles)
	{
		centerXi = tile->GetX();
		centerYi = tile->GetY();

		for (auto tile : mTiles)
		{
			centerXj = tile->GetX();
			centerYj = tile->GetY();

			if (centerXi == centerXj && centerYi == centerYj)
				increment = true;

			if (increment == true)
				totalOverlaps++;

			increment = false;
		}
	}
	return (totalOverlaps - mTiles.size()) / 2;
	//return totalOverlaps;
}
/**
 * \file City.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 */

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <stack>

#include "City.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "TileConstruction.h"
#include "TileTransportation.h"
#include "TileCar.h"
#include "TilePower.h"
#include "TileOremine.h"
#include "TileStadium.h"
#include "TileBank.h"
#include "CheckPowerPlant.h"
#include "CheckGridConnection.h"
#include "ResetPower.h"

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
* \param offsetX offset for x location
* \param offsetY offset for y location
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



/**\brief Test an x,y click location to see if it clicked
* on some item in the city.
 * \param x X location
 * \param y y location
 * \param offsetX offset for x location
 * \param offsetY offset for y location
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


/**
 * Finds the car
 * \returns this If the car is found
 */
std::shared_ptr<CTile> CCity::FindCar()
{
	for (auto i = mTiles.rbegin(); i != mTiles.rend(); i++)
	{
		if ((*i)->GetZoning() == CTile::CAR)
		{
			return *i;
		}
	}
	return  nullptr;
}


/**
 * Returns the tile that is under the car
 * \returns this The tile which is under the car
 */
std::shared_ptr<CTile> CCity::FindTransTileUnderCar()
{
	double centerXj;
	double centerYj;

	int i = 0;	///counter for iterating over mTiles
	int j = 0;	///counter for iterating over mTiles

	auto tileCar = this->FindCar();

	int carX = tileCar->GetX();
	int carY = tileCar->GetY();
	
	for (auto tile : mTiles)
	{
		j++;

		if (tile != tileCar)
		{

			centerXj = tile->GetX();
			centerYj = tile->GetY();

			if (carX == centerXj && carY == centerYj)
			{
				return tile;
			}
		}
	}
	return nullptr;
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
	else if (type == L"stadium")
	{
		tile = make_shared<CTileStadium>(this);
	}
	else if (type == L"oremine")
	{
		tile = make_shared<CTileOremine>(this);
	}
	else if (type == L"transportation")
	{
		tile = make_shared<CTileTransportation>(this, CTileTransportation::NONE);
	}
	else if (type == L"power")
	{
		tile = make_shared<CTilePower>(this, CTilePower::NONE);
	}
	else if (type == L"bank")
	{
		tile = make_shared<CTileBank>(this);
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

//std::shared_ptr<CTileTransportation> CCity::GetAdjacentTrans(std::shared_ptr<CTile> tile, int dx, int dy)
//{
//	return GetAdjacentTrans(tile.get(), dx, dy);
//}

//std::shared_ptr<CTileTransportation> CCity::GetAdjacentTrans(CTile *tile, int dx, int dy)
//{
//	int atX = tile->GetX() / GridSpacing + dx * 2;
//	int atY = tile->GetY() / GridSpacing + dy;
//
//	auto adj = mAdjacencyTrans.find(pair<int, int>(atX, atY));
//	if (adj != mAdjacencyTrans.end())
//	{
//		// We found it
//		return adj->second;
//	}
//
//	return nullptr;
//}

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
* \return Number of tiles
*/
int CCity::CountTiles()
{
	return mTiles.size();
}


/**
 * calculate how many tile are partially overlapping
 * \returns number of the tils overlapping with others
 */
int CCity::CountPartialOverlapping()
{
	int totalOverlaps = 0;

	double iX;
	double iY;

	double jX;
	double jY;

	double centerX;
	double centerY;

	bool increment = false;

	int i = 0;
	int j = 0;

	for (auto tile : mTiles)
	{
		i++;

		iX = tile->GetX();
		iY = tile->GetY();

		j = 0;

		for (auto tile : mTiles)
		{
			j++;
			
			if (j != i){
				centerX = tile->GetX();
				centerY = tile->GetY();

				//increment = false;

				jX = centerX - 64;
				jY = centerY;
				//Left Corner
				if (abs(iX - jX) + 2 * abs(iY - jY) < 64)
					increment = true;

				jX = centerX + 64;
				jY = centerY;
				//Right Corner
				if (abs(iX - jX) + 2 * abs(iY - jY) < 64)
					increment = true;

				jX = centerX;
				jY = centerY + 32;
				//Top Corner
				if (abs(iX - jX) + 2 * abs(iY - jY) < 64)
					increment = true;

				jX = centerX;
				jY = centerY - 32;
				//Bottom Corner
				if (abs(iX - jX) + 2 * abs(iY - jY) < 64)
					increment = true;
			}

			if (increment == true){
				totalOverlaps++;
				break;
			}
			increment = false;
		}
	}

	return totalOverlaps;

}


/**
 * calculate how many tile are fully overlapping
 * \returns number of the tils fully overlapping with others
 */
int CCity::CountFullyOverlapping()
{
	int totalOverlaps = 0;

	double centerXi;
	double centerYi;

	double centerXj;
	double centerYj;

	int i = 0;	///counter for iterating over mTiles
	int j = 0;	///counter for iterating over mTiles

	for (auto tile : mTiles)
	{
		i++;

		centerXi = tile->GetX();
		centerYi = tile->GetY();

		j = 0;

		for (auto tile : mTiles)
		{
			j++;

			if (i != j)
			{

				centerXj = tile->GetX();
				centerYj = tile->GetY();

				if (centerXi == centerXj && centerYi == centerYj)
				{
					totalOverlaps++;
					break;
				}
			}
		}
	}
	return totalOverlaps;
	//return totalOverlaps;
}


/**
 * connect grid in city
 */
void CCity::ConnectGrid()
{
	ResetGrid();

	CCheckPowerPlant visitor;
	CCheckGridConnection gridvisitor;
	for (auto tile : mTiles)
	{
	
		tile->Accept(&visitor);

		if (visitor.CheckPowerPlant())
		{
			std::stack<std::shared_ptr<CTile>> unvisited;
			std::shared_ptr<CTile> current;
			std::shared_ptr<CTile> upleft;
			std::shared_ptr<CTile> upright;
			std::shared_ptr<CTile> lowleft;
			std::shared_ptr<CTile> lowright;

			unvisited.push(tile);


			///tile->Accept(&gridvisitor);

			while (!unvisited.empty())
			{
				upleft = nullptr;
				upright = nullptr;
				lowleft = nullptr;
				lowright = nullptr;
				current = nullptr;

				current = (unvisited.top()); //当前应该访问的
				unvisited.pop();

				bool skipForCurrent = current->IsVisited();
				current->Accept(&gridvisitor);
				
				if (!skipForCurrent)
				{

					if (current->GetAdjacent(-1, -1) != nullptr){
						upleft = current->GetAdjacent(-1, -1);
						if (!upleft->IsVisited())
							unvisited.push(upleft);
					}
					if (current->GetAdjacent(1, -1) != nullptr){
						upright = current->GetAdjacent(1, -1);
						if (!upright->IsVisited())
							unvisited.push(upright);
					}
					if (current->GetAdjacent(-1, 1) != nullptr){
						lowleft = current->GetAdjacent(-1, 1);
						if (!lowleft->IsVisited())
							unvisited.push(lowleft);
					}
					if (current->GetAdjacent(1, 1) != nullptr){
						lowright = current->GetAdjacent(1, 1);
						if (!lowright->IsVisited())
							unvisited.push(lowright);
					}
				}

				///current->Accept(&gridvisitor);


			}
		}
	}

	mTotalPowerProduct = visitor.GetProduction();

}


/**
 * 	reset all grid to not connect status
 */
void CCity::ResetGrid()
{
	CResetPower resetvisitor;
	for (auto tile : mTiles)
	{
		tile->Accept(&resetvisitor);
	}
}
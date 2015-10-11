/**
* \file TileStadium.cpp
*
* \author Vedran Simunovic
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



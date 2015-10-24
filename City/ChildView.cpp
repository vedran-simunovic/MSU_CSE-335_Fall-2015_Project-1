/**
 * \file ChildView.cpp
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 */

#include "stdafx.h"
#include <sstream>
#include <math.h>

#include "DoubleBufferDC.h"
#include "CityApp.h"
#include "ChildView.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "TileConstruction.h"
#include "BuildingCounter.h"
#include "CoalCounter.h"
#include "OreCounter.h"
#include "ResetCoal.h"
#include "ResetOre.h"
#include "Trump.h"
#include "TransRotate.h"
#include "TileTransportation.h"
#include "PowerRotate.h"
#include "TileCar.h"
#include "TileStadium.h"
#include "TileOremine.h"
#include "TileBank.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 100;


/// Initial tile X location
const int InitialX = CCity::GridSpacing * 5;

/// Initial tile Y location
const int InitialY = CCity::GridSpacing * 3;

/// Margin of trashcan from side and bottom in pixels
const int TrashcanMargin = 5;

/// Margin of wallet from side and bottom in pixels
const int WalletMargin = 2;

/// Margin of inventory from side and bottom in pixels
const int InventoryMargin = 2;

/// Margin of inventory space from the wallet
const int InventoryMarginSpace = 20;

/// Margin of trashcan from side and bottom in pixels
const int ScrollMarginTop = 0;

/// Margin of trashcan from side and bottom in pixels
const int ScrollMarginRight = 0;

/// The number of pixels for one item on power tool bar
const int PowerToolbarRegion = 64;

/**
 * Constructor
 */
CChildView::CChildView()
{
    srand((unsigned int)time(nullptr));

	// Load the trash can image
    mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
    if (mTrashcan->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/trashcan.png");
    }

	// load power tool bar image
	mPowerToolbar = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/toolbar-power.png"));
	if (mPowerToolbar->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/toolbar-power.png");
	}

	
	// Load scrolling menu
	mScroll = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
	if (mScroll->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/nav1.png");
	}

	// Load the wallet image
	mWallet = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/wallet.png"));
	if (mWallet->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/wallet.png");
	}
	
	// Load the inventory image
	mInventory = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/inventory.png"));
	if (mInventory->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/inventory.png");
	}
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

/// \cond
// This doxygen switch tells it to ignore this block of code
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
    ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
    ON_COMMAND(ID_BUILDINGS_FARMHOUSE, &CChildView::OnBuildingsFarmhouse)
    ON_COMMAND(ID_LANDSCAPING_GRASS, &CChildView::OnLandscapingGrass)
    ON_COMMAND(ID_LANDSCAPING_SPARTYSTATUE, &CChildView::OnLandscapingSpartystatue)
    ON_COMMAND(ID_BUILDINGS_BLACKSMITHSHOP, &CChildView::OnBuildingsBlacksmithshop)
    ON_COMMAND(ID_LANDSCAPING_TALLGRASS, &CChildView::OnLandscapingTallgrass)
    ON_COMMAND(ID_BUILDINGS_BROWNHOUSE, &CChildView::OnBuildingsBrownhouse)
    ON_COMMAND(ID_BUILDINGS_YELLOWHOUSE, &CChildView::OnBuildingsYellowhouse)
    ON_COMMAND(ID_BUILDINGS_F, &CChildView::OnBuildingsF)
    ON_COMMAND(ID_BUILDINGS_HOSPITAL, &CChildView::OnBuildingsHospital)
    ON_COMMAND(ID_BUILDINGS_MARKET, &CChildView::OnBuildingsMarket)
    ON_COMMAND(ID_BUILDINGS_CONDOS, &CChildView::OnBuildingsCondos)
    ON_COMMAND(ID_LANDSCAPING_TREE, &CChildView::OnLandscapingTree)
    ON_COMMAND(ID_LANDSCAPING_TREES, &CChildView::OnLandscapingTrees)
    ON_COMMAND(ID_LANDSCAPING_BIGTREES, &CChildView::OnLandscapingBigtrees)
    ON_COMMAND(ID_LANDSCAPING_ROAD, &CChildView::OnLandscapingRoad)
    ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_BORDER_NONE, &CChildView::OnBorderNone)
	ON_COMMAND(ID_BORDER_RESIDENTIAL, &CChildView::OnBorderResidential)
	ON_COMMAND(ID_BORDER_INDUSTRIAL, &CChildView::OnBorderIndustrial)
	ON_COMMAND(ID_BORDER_AGRICULTURAL, &CChildView::OnBorderAgricultural)
	ON_UPDATE_COMMAND_UI(ID_BORDER_NONE, &CChildView::OnUpdateBorderNone)
	ON_UPDATE_COMMAND_UI(ID_BORDER_RESIDENTIAL, &CChildView::OnUpdateBorderResidential)
	ON_UPDATE_COMMAND_UI(ID_BORDER_INDUSTRIAL, &CChildView::OnUpdateBorderIndustrial)
	ON_UPDATE_COMMAND_UI(ID_BORDER_AGRICULTURAL, &CChildView::OnUpdateBorderAgricultural)
	ON_COMMAND(ID_BUILDINGS_COUNT, &CChildView::OnBuildingsCount)
	ON_COMMAND(ID_POWER_BUILD, &CChildView::OnPowerBuild)
	ON_UPDATE_COMMAND_UI(ID_POWER_BUILD, &CChildView::OnUpdatePowerBuild)
	ON_COMMAND(ID_TRANSPORTATION_CURVEDROAD, &CChildView::OnTransportationCurvedroad)
	ON_COMMAND(ID_TRANSPORTATION_ROAD, &CChildView::OnTransportationRoad)
	ON_COMMAND(ID_TRANSPORTATION_ELEVATEDROAD, &CChildView::OnTransportationElevatedroad)
	ON_COMMAND(ID_TRANSPORTATION_INCLINEDROAD, &CChildView::OnTransportationInclinedroad)
	ON_COMMAND(ID_TRANSPORTATION_PLAINROAD, &CChildView::OnTransportationPlainroad)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	
	

	ON_COMMAND(ID_CONSTRUCTION_GRASSSITE, &CChildView::OnConstructionGrasssite)
	ON_COMMAND(ID_BORDER_CONSTRUCTION, &CChildView::OnBorderConstruction)
	ON_UPDATE_COMMAND_UI(ID_BORDER_CONSTRUCTION, &CChildView::OnUpdateBorderConstruction)
	ON_COMMAND(ID_BORDER_TRANSPORTATION, &CChildView::OnBorderTransportation)
	ON_COMMAND(ID_BORDER_POWER, &CChildView::OnBorderPower)
	ON_UPDATE_COMMAND_UI(ID_BORDER_TRANSPORTATION, &CChildView::OnUpdateBorderTransportation)
	ON_UPDATE_COMMAND_UI(ID_BORDER_POWER, &CChildView::OnUpdateBorderPower)
	ON_COMMAND(ID_TILESINFO_TILESINCITY, &CChildView::OnTilesinfoTilesincity)
	ON_COMMAND(ID_TRANSPORTATION_CAR, &CChildView::OnTransportationCar)
	ON_COMMAND(ID_TILESINFO_PARTIALLYOVERLAPPING, &CChildView::OnTilesinfoPartiallyoverlapping)
	ON_COMMAND(ID_TILESINFO_FULLYOVERLAPPING, &CChildView::OnTilesinfoFullyoverlapping)
	ON_COMMAND(ID_TRANSPORTATION_VEHICLEMODE, &CChildView::OnTransportationVehiclemode)
	ON_UPDATE_COMMAND_UI(ID_TRANSPORTATION_VEHICLEMODE, &CChildView::OnUpdateTransportationVehiclemode)
	ON_COMMAND(ID_COALMINE_CREATECOALMINE, &CChildView::OnCoalmineCreatecoalmine)
	ON_COMMAND(ID_COALMINE_TRUMP, &CChildView::OnCoalmineTrump)
	ON_UPDATE_COMMAND_UI(ID_COALMINE_TRUMP, &CChildView::OnUpdateCoalmineTrump)
	ON_COMMAND(ID_COALMINE_HAULCOLE, &CChildView::OnCoalmineHaulcole)
	ON_COMMAND(ID_BANK_CREATEBANK, &CChildView::OnBankCreatebank)
	ON_COMMAND(ID_OREMINE_BUYOREMINE, &CChildView::OnOremineBuyoremine)
	ON_COMMAND(ID_BORDER_CAR, &CChildView::OnBorderCar)
	ON_COMMAND(ID_BORDER_BUSINESS, &CChildView::OnBorderBusiness)
	ON_UPDATE_COMMAND_UI(ID_BORDER_CAR, &CChildView::OnUpdateBorderCar)
	ON_UPDATE_COMMAND_UI(ID_BORDER_BUSINESS, &CChildView::OnUpdateBorderBusiness)
	ON_COMMAND(ID_OREMINE_HAULORE, &CChildView::OnOremineHaulore)
END_MESSAGE_MAP()
/// \endcond




/** 
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** 
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);
    graphics.Clear(Color(0, 0, 0));

    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);
    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;

    mCity.Update(elapsed);

    // Get the size of the window
    CRect rect;
    GetClientRect(&rect);

    /*
     * Draw the trash can
     */
    
    // Bottom minus image size minus margin is top of the image
    mTrashcanTop = rect.Height() - mTrashcan->GetHeight() - TrashcanMargin;
    mTrashcanRight = TrashcanMargin + mTrashcan->GetWidth();

    graphics.DrawImage(mTrashcan.get(), TrashcanMargin, mTrashcanTop,
        mTrashcan->GetWidth(), mTrashcan->GetHeight());

    /*
     * Actually Draw the city
     */
	graphics.SetPageUnit(UnitPixel);
	graphics.SetPageScale(mScale);
	mCity.OnDraw(&graphics, mScrollOffsetX/mScale, mScrollOffsetY/mScale);

	// Draw scrolling menu
	graphics.SetPageScale(1);

	mScrollTop = ScrollMarginTop;
	mScrollLeft = rect.Width() - mScroll->GetWidth() - ScrollMarginRight;

	graphics.DrawImage(mScroll.get(), mScrollLeft, mScrollTop,
		mScroll->GetWidth(), mScroll->GetHeight());

	if (mPowerActivate){
		// Bottom minus image size minus margin is top of the image
		mPowerToolbarTop = rect.Height() - mPowerToolbar->GetHeight();
		mPowerToolbarLeft = rect.Width() - mPowerToolbar->GetWidth();

		graphics.DrawImage(mPowerToolbar.get(), mPowerToolbarLeft, mPowerToolbarTop,
			mPowerToolbar->GetWidth(), mPowerToolbar->GetHeight());
	}

	/*
	* Draw the wallet
	*/
	mWalletTop = WalletMargin;
	mWalletRight = WalletMargin + mWallet->GetWidth();

	graphics.DrawImage(mWallet.get(), WalletMargin, mWalletTop,
		mWallet->GetWidth(), mWallet->GetHeight());

	/*
	* Draw the inventory
	*/
	mInventoryTop = mWallet->GetHeight() + InventoryMargin + InventoryMarginSpace;
	mInventoryRight = InventoryMargin + mInventory->GetWidth();

	graphics.DrawImage(mInventory.get(), InventoryMargin, mInventoryTop,
		mInventory->GetWidth(), mInventory->GetHeight());

	Pen pen(Color::Green, 2);

	// draw box over all of the tiles
	
	//if (!mNoneCheck && !mAgriculturalCheck && !mIndustrialCheck && !mResidentialCheck)
	/*
	for (auto tile : mCity)
	{
		tile->DrawBorder(&graphics, &pen);
	}*/

	

	// draw box only over the tile elements selected.


	for (auto tile : mCity.GetZoning(mZoning))		
	{
		tile->DrawBorder(&graphics, &pen, mScrollOffsetX, mScrollOffsetY, mScale);
	}
	
	/*else
	{
		// if no checkmarks, then don't draw a green border
		Invalidate();
	}*/
}


/**
* \brief Erase the background prior to drawing.
*
* We return true so this does nothing. This prevents the flicker
* of a repaint of white before actual drawing.
*
* \param pDC A device context to draw on
* \returns TRUE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // This disabled the default background erase
    return TRUE;
}

/** 
* \brief Handle a left button double-click on a tile
* \param nFlags Mouse flags
* \param point Where we clicked
*/
void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	auto tile = mCity.HitTest(point.x, point.y, mScrollOffsetX, mScrollOffsetY);
    if (tile != nullptr) 
    {
		/// If the double clicked tile is a transportation tile, we need to rotate it.
		if (tile->GetZoning() == CTile::TRANSPORTATION)
		{
			CTransRotate visitor;

			tile->Accept(&visitor);
		}else if(tile->GetZoning() == CTile::CONSTRUCTIONAL)
		{
			// Starts off the clearing process if the tile in constructional
			tile->SetClearFlag();
			Invalidate();
		}
		else if (tile->GetZoning() == CTile::BUSINESS)
		{// PROMOTE THE TILE
			
			wstringstream str;


			if (mTotalMoney < mPromotionPrice)
			{
				str << L"You do not have enough money to promote this tile.\n\n" <<
					"Your current total money is: $" << mTotalMoney <<
					"\nThe cost of the tile promotion is: $" << mPromotionPrice;
				AfxMessageBox(str.str().c_str());
			}
			else
			{
				

				mTotalMoney = mTotalMoney - mPromotionPrice;

				tile->Promote();
				Invalidate();

				str << L"Tile Promoted!\n\nA silver star on the tile will indicate the promotion in the next production step!";
				AfxMessageBox(str.str().c_str());
			}
			
		}
		else
		{
        // We double-clicked on a tile
        // Bring up the tile editing dialog box
		tile->PropertiesDlg();
			Invalidate();
		}
    }

}





/** \brief Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// test if the point at the power tool bar when tool bar activate
	if (mPowerActivate == true && (point.x > mPowerToolbarLeft && point.y > mPowerToolbarTop)){
		double relPointPosX = point.x - mPowerToolbarLeft;
		int clickRegion = int(floor(relPointPosX / PowerToolbarRegion));

		switch (clickRegion)
		{
		case 1:{
			AddPower(CTilePower::LGRID);
			break;
		}
			   // 
		case 2:{
			AddPower(CTilePower::GRID);
			break;
		}

		case 3:{
			AddPower(CTilePower::TGRID);
			break;
		}

		case 4:{
			AddPower(CTilePower::XGRID);
			break;
		}

		case 5:{
			AddPower(CTilePower::SUBSTATION);
			break;
		}

		case 6:{
			AddPower(CTilePower::POWERPLANT);
			break;
		}

		case 7:{
			AddPower(CTilePower::SOLARSTATION);
			break;
		}

		}
	}



	if (point.x > mScrollLeft + 44 && point.y < mScroll->GetHeight())
	{
		if (mScrollActivate == false)
		{
			mScroll = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav2.png"));
			mScrollActivate = true;
		}
		else
		{
			mScroll = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
			mScrollActivate = false;
		}
	}

	if (point.x < mScrollLeft + 44 && point.x > mScrollLeft && point.y < mScroll->GetHeight() / 2)
	{
		if (mScale <= 4)
			mScale = mScale * 2;
	}

	if (point.x < mScrollLeft + 44 && point.x > mScrollLeft && point.y > mScroll->GetHeight() / 2 && point.y < mScroll->GetHeight())
	{
		if (mScale >= 0.25)
			mScale = mScale / 2;
	}

	if (mScrollActivate)
	{
		mStartX = point.x;
		mStartY = point.y;

	}
	else {
		mGrabbedItem = mCity.HitTest(point.x / mScale, point.y / mScale, mScrollOffsetX / mScale, mScrollOffsetY / mScale);
		if (mGrabbedItem != nullptr)
		{
			if (!mTrumpCheck)
			{
				// We grabbed something
				// Move it to the front
				mCity.MoveToFront(mGrabbedItem);
				Invalidate();
			}
			else
			{
				// Instantiate the visitor
				CTrump visitor;

				// Send to JUST this one time
				mGrabbedItem->Accept(&visitor);

				// Clear this since we don't want to then drag
				mGrabbedItem = false;
			}
		}
	}


	if (point.x < mWallet->GetWidth() + WalletMargin && point.y < mWallet->GetHeight() + WalletMargin)
	{
		wstringstream str;
		if (mTotalMoney < mGameObjectiveMoney)
		{
			str << L"~~~~~Become a Millionaire~~~~~\n\nYou have $" << mTotalMoney <<
				endl << endl <<
				"To win the game, you need to have more than $" <<
				mGameObjectiveMoney << ".\n\nYou are " << mTotalMoney / (mGameObjectiveMoney+1) * 100 <<
				"% done with the game!.";
		}
		else
		{
			str << L"You have won the game!\n\n\nCongratulations!!!!!!!!";
		}

		AfxMessageBox(str.str().c_str());
	}

	if (point.x < mInventory->GetWidth() + InventoryMargin && point.y < mWallet->GetHeight() + WalletMargin + mInventory->GetHeight() + InventoryMarginSpace && point.y > mWallet->GetHeight() + WalletMargin + InventoryMarginSpace)
	{
		wstringstream str;
		str << L"~~~~~ Building Prices ~~~~~\n\n" <<
			"\nBusiness Tiles:"
			"\n   Coalmine Price: $" << mCoalminePrice <<
			"\n   Oremine Price: $" << mOreminePrice <<
			"\n   Promote the business tile: $" << mPromotionPrice <<
			endl << endl <<
			"\nAll Other Tiles: $" << mOtherTilesPrice;
		AfxMessageBox(str.str().c_str());
	}


		
}

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    OnMouseMove(nFlags, point);

}

/** \brief Called when any key is pressed
* \param nChar is the key that was pressed
* \param 
*/
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int cool = 0;
	/// Check if vehicle mode is on
	auto tileCar = mCity.FindCar();
	if (mVehicleMode && tileCar != nullptr)
	{
		/// We need to find the car tile
		/// Iterate through all tiles in the city, return the car tile
		if (nChar == 37) /// Left
		{

			auto adjacentTile = mCity.GetAdjacent(tileCar, -1, 1); /// Checking lower left
			///tileCar->SetLocation(x + 50, y + 50);
			if (adjacentTile != nullptr)
			{
				tileCar->SetLocation(adjacentTile->GetX(), adjacentTile->GetY());
			}
		}
		else if (nChar == 38) /// Up 
		{
			auto adjacentTile = mCity.GetAdjacent(tileCar, -1, -1); /// Checking upper left
			///tileCar->SetLocation(x + 50, y + 50);
			if (adjacentTile != nullptr)
			{
				tileCar->SetLocation(adjacentTile->GetX(), adjacentTile->GetY());
			}
		}
		else if (nChar == 39) /// Right
		{
			cool = 3;
		}
		else if (nChar == 40)
		{
			cool = 4;
		}/// Down

		Invalidate();
		/// Find car, move it to the CENTER of the adjacent tile.
	}

}

/** \brief Called when any key is pressed
* \param nChar is the key that was pressed
* \param
*/
void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mScrollActivate) 
	{
		if (nFlags & MK_LBUTTON)
		{
			mScrollOffsetX = point.x - mStartX + mOriginOffsetX;
			mScrollOffsetY = point.y - mStartY + mOriginOffsetY;
			
		}
		else
		{
			mOriginOffsetX = mScrollOffsetX;
			mOriginOffsetY = mScrollOffsetY;
		}



	}
	else
	{
		if (mGrabbedItem != nullptr && mGrabbedItem->GetZoning() != CTile::CAR)
		{
			// If an item is being moved, we only continue to 
			// move it while the left button is down.
			if (nFlags & MK_LBUTTON)
			{
				mGrabbedItem->SetLocation((point.x - mScrollOffsetX) / mScale, (point.y - mScrollOffsetY) / mScale);
			}
			else
			{
				// When the left button is released we release
				// the item. If we release it on the trashcan,
				// delete it.
				if (point.x < mTrashcanRight && point.y > mTrashcanTop)
				{
					// We have clicked on the trash can
					mCity.DeleteItem(mGrabbedItem);
				}
				else
				{
					mGrabbedItem->QuantizeLocation();
				}

				mCity.SortTiles();
				mGrabbedItem = nullptr;
			}
		}

	}
    // See if an item is currently being moved by the mouse
    

    // Force the screen to redraw
	Invalidate();

}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}



/**
* \brief Handler for the File/Save As menu option
*/
void CChildView::OnFileSaveas()
{
    CFileDialog dlg(false,  // false = Save dialog box
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        OFN_OVERWRITEPROMPT,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();

    mCity.Save(filename);
}


/** \brief This function is called when an File Open menu item is selected.
*
* It loads the city from a file.
*/
void CChildView::OnFileOpen()
{
    CFileDialog dlg(true,  // true = Open dialog box::addbuilding
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        0,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();
    mCity.Load(filename);
    Invalidate();
}



/**
 * \brief Add a CTileBuilding tile to the drawing.
 * \param file The file for the building image
 */
void CChildView::AddBuilding(const std::wstring &file)
{
    auto tile = make_shared<CTileBuilding>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
* \brief Add a Car tile to the drawing.
* \param file The file for the building image
*/
void CChildView::AddCar(const std::wstring &file)
{
	int carCount = mCity.GetCarCount();
	if (carCount == 0)
	{
		auto tile = make_shared<CTileCar>(&mCity);
		carCount++;
		tile->SetImage(file);
		tile->SetLocation(InitialX, InitialY);
		tile->SetZoning(CTile::CAR);
		mCity.Add(tile);
		mCity.MoveToFront(tile);
		mCity.SetCarCount(carCount);
		Invalidate();
	}
	else {
		wstringstream str;
		str << L"You can only have one car.";
		AfxMessageBox(str.str().c_str());
	}
}


/**
* \brief Add a CTileLandscaping tile to the drawing.
* \param file The file for the landscape image
*/
void CChildView::AddLandscape(const std::wstring &file)
{
    auto tile = make_shared<CTileLandscape>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/**
 * \cond
 *
 * I'm not going to document these menu handlers, since what they 
 * so is obvious. I'm using a Doxygen feature to ignore the functions
 */

void CChildView::OnLandscapingRoad()
{
	auto tile = make_shared<CTileRoad>(&mCity);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	Invalidate();
}








void CChildView::OnBuildingsFarmhouse()
{
    AddBuilding(L"farm0.png");
}


void CChildView::OnLandscapingGrass()
{
    AddLandscape(L"grass.png");
}


void CChildView::OnLandscapingSpartystatue()
{
    AddLandscape(L"sparty.png");
}


void CChildView::OnBuildingsBlacksmithshop()
{
    AddBuilding(L"blacksmith.png");
}


void CChildView::OnLandscapingTallgrass()
{
    AddLandscape(L"tallgrass.png");
}


void CChildView::OnBuildingsBrownhouse()
{
    AddBuilding(L"house.png");
}


void CChildView::OnBuildingsYellowhouse()
{
    AddBuilding(L"yellowhouse.png");
}


void CChildView::OnBuildingsF()
{
    AddBuilding(L"firestation.png");
}


void CChildView::OnBuildingsHospital()
{
    AddBuilding(L"hospital.png");
}


void CChildView::OnBuildingsMarket()
{
    AddBuilding(L"market.png");
}


void CChildView::OnBuildingsCondos()
{
    AddBuilding(L"condos.png");
}


void CChildView::OnLandscapingTree()
{
    AddLandscape(L"tree.png");
}


void CChildView::OnLandscapingTrees()
{
    AddLandscape(L"tree2.png");
}


void CChildView::OnLandscapingBigtrees()
{
    AddLandscape(L"tree3.png");
}



/** \endcond */



/** Menu handler that sets the border draw to none */
void CChildView::OnBorderNone()
{
	mZoning = CTile::NONE;
}

/** Menu handler that sets the border draw to residential*/
void CChildView::OnBorderResidential()
{
	mZoning = CTile::RESIDENTIAL;
}

/** Menu handler that sets the border draw to industrial */
void CChildView::OnBorderIndustrial()
{
	mZoning = CTile::INDUSTRIAL;
}

/** Menu handler that sets the border draw to agricultural */
void CChildView::OnBorderAgricultural()
{
	mZoning = CTile::AGRICULTURAL;
}

/** Menu handler that sets the border draw to construction */
void CChildView::OnBorderConstruction()
{
	mZoning = CTile::CONSTRUCTIONAL;
}

/** Menu handler that sets the border draw to transportation */
void CChildView::OnBorderTransportation()
{
	mZoning = CTile::TRANSPORTATION;
}

/** Menu handler that sets the border draw to power */
void CChildView::OnBorderPower()
{
	mZoning = CTile::POWER;
}

/** Menu handler that sets the border draw to car */
void CChildView::OnBorderCar()
{
	mZoning = CTile::CAR;
}

/** Menu handler that sets the border draw to business */
void CChildView::OnBorderBusiness()
{
	mZoning = CTile::BUSINESS;
}



/** Menu handler that sets the border draw to none 
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::NONE);
}


/** Menu handler that sets the border draw to residential
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderResidential(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::RESIDENTIAL);
}

/** Menu handler that sets the border draw to industrial
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderIndustrial(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::INDUSTRIAL);
}

/** Menu handler that sets the border draw to agricultural 
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderAgricultural(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::AGRICULTURAL);
}

/** Menu handler that sets the border draw to construction
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderConstruction(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::CONSTRUCTIONAL);
}

/**
* check mark on menu
* \param pCmdUI
*/
void CChildView::OnUpdateBorderTransportation(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::TRANSPORTATION);
}

/**
* check mark on menu
* \param pCmdUI
*/
void CChildView::OnUpdateBorderPower(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::POWER);
}

void CChildView::OnUpdateBorderCar(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::CAR);
}


void CChildView::OnUpdateBorderBusiness(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == CTile::BUSINESS);
}


/** Menu handler that counts the number of builds */
void CChildView::OnBuildingsCount()
{
	CBuildingCounter visitor;
	mCity.Accept(&visitor);
	int cnt = visitor.GetNumBuildings();

	wstringstream str;
	str << L"There are " << cnt << L" buildings.";
	AfxMessageBox(str.str().c_str());
}



/** Menu handler deals with building power tile */
void CChildView::OnPowerBuild()
{
	mPowerActivate = !mPowerActivate;
}

/** Menu handler deals with building power tile
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdatePowerBuild(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mPowerActivate);
}


/**
 * build curve road
 */
void CChildView::OnTransportationCurvedroad()
{
	AddTransportation(CTileTransportation::CURVED);

}


/**
 * build road
 */
void CChildView::OnTransportationRoad()
{
	AddTransportation(CTileTransportation::FLAT);

}

/**
 * build elevated road
 */
void CChildView::OnTransportationElevatedroad()
{
	AddTransportation(CTileTransportation::ELEVATED);

}

/**
 * build inclined road
 */
void CChildView::OnTransportationInclinedroad()
{

	AddTransportation(CTileTransportation::INCLINED);

}

/**
 * build plain road
 */
void CChildView::OnTransportationPlainroad()
{
	AddTransportation(CTileTransportation::PLAIN);
}


/**
 * When we at build mode of power, right click the picture will rotate picture
 * \param nFlags 
 * \param point 
 */
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mCity.HitTest(point.x, point.y, mOriginOffsetX, mOriginOffsetY);
	if (mGrabbedItem != nullptr)
	{
		if (mPowerActivate)
		{
			// Instantiate the visitor
			CPowerRotate visitor;

			// Send to JUST this one time
			mGrabbedItem->Accept(&visitor);

			// Clear this since we don't want to then drag
			mGrabbedItem = false;
		}
	}
}

/**
* \brief Add a CTilePower tile to the drawing.
* \param type type of power tile
*/
void CChildView::AddPower(CTilePower::PowerType type)
{
	auto tile = make_shared<CTilePower>(&mCity, type);
	tile->SetLocation(InitialX, InitialY);
	tile->SetZoning(CTile::POWER);
	mCity.Add(tile);
	Invalidate();
}

/**
* \brief Add a CTilePower tile to the drawing.
* \param type type of power tile
*/
void CChildView::AddTransportation(CTileTransportation::TransTileType type)
{
	auto tile = make_shared<CTileTransportation>(&mCity, type);
	tile->SetLocation(InitialX, InitialY);
	tile->SetZoning(CTile::TRANSPORTATION);
	mCity.Add(tile);
	Invalidate();
}


/**
 * build grass site
 */
void CChildView::OnConstructionGrasssite()
{
	// Take the floating point "mDuration" and move the decimal over
	// This will move the decimal over by 8 places
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	// Test if that number is even or odd. This is the randomness
	if (time.QuadPart % 2 == 0)
	{
		auto tile = make_shared<CTileStadium>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		tile->SetZoning(CTile::CONSTRUCTIONAL);
		mCity.Add(tile);
	}
	else
	{	
		auto tile = make_shared<CTileOremine>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		tile->SetZoning(CTile::CONSTRUCTIONAL);
		mCity.Add(tile);
	}
	
	//auto tile = make_shared<CTileConstruction>(&mCity);
	
	Invalidate();
}





/**
 * number of tiles in city
 */
void CChildView::OnTilesinfoTilesincity()
{	
	int cnt = mCity.CountTiles();

	wstringstream str;

	/// Displaying that information
	str << L"There are " << cnt << L" tiles.";
	AfxMessageBox(str.str().c_str());
}


/**
 * 	build a car
 */
void CChildView::OnTransportationCar()
{
	AddCar(L"car2.png");
}


/**
* number of partially overlapping tiles
*/
void CChildView::OnTilesinfoPartiallyoverlapping()
{
	int i;
	CRect rect;
	GetClientRect(&rect);
	i = mCity.CountPartialOverlapping();
	wstringstream str;

	/// Displaying that information
	str << L"There are " << i << L" partially overlapping tiles.";
	AfxMessageBox(str.str().c_str());
}


/**
 * number of fully overlapping tiles
 */
void CChildView::OnTilesinfoFullyoverlapping()
{
	int i;
	CRect rect;
	GetClientRect(&rect);
	i = mCity.CountFullyOverlapping();
	wstringstream str;

	/// Displaying that information
	str << L"There are " << i << L" fully overlapping tiles.";
	AfxMessageBox(str.str().c_str());
}


void CChildView::OnTransportationVehiclemode()
{
	mVehicleMode = !mVehicleMode;
}


void CChildView::OnUpdateTransportationVehiclemode(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mVehicleMode);
}




/** Menu handler deals with trumping feature */
void CChildView::OnCoalmineTrump()
{
	mTrumpCheck = !mTrumpCheck;
}

/** Menu handler deals with trumping feature
* \param pCmdUI This is pass to be able to change the checkmark on the screen
*/
void CChildView::OnUpdateCoalmineTrump(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mTrumpCheck);
}

/** Menu handler that counts the tons of coal hauled */
void CChildView::OnCoalmineHaulcole()
{
	CCoalCounter visitor;
	mCity.Accept(&visitor);
	double totalProduction = visitor.GetTotalProduction();

	wstringstream str;
	str << L"The total production is " << totalProduction << L" tons.\n You just earned $"<<
		totalProduction*mCoalPrice << " because the price of 1 ton of coal is worth $" << mCoalPrice;
	AfxMessageBox(str.str().c_str());

	mTotalMoney = mTotalMoney + totalProduction*mCoalPrice;

	CResetCoal visitor2;
	mCity.Accept(&visitor2);
}


void CChildView::OnBankCreatebank()
{
	auto tile = make_shared<CTileBank>(&mCity);
	tile->SetLocation(InitialX, InitialY);
	tile->SetZoning(CTile::BUSINESS);
	mCity.Add(tile);
	Invalidate();
}


void CChildView::OnOremineBuyoremine()
{
	if (mTotalMoney < mOreminePrice)
	{
		wstringstream str;
		str << L"You do not have enough money to buy an Oremine.\n\n" <<
			"Your current total money is: $" << mTotalMoney <<
			"\nThe cost of an Oremine is: $" << mOreminePrice;
		AfxMessageBox(str.str().c_str());
	}
	else
	{
		mTotalMoney = mTotalMoney - mOreminePrice;

		auto tile = make_shared<CTileOremine>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		tile->SetZoning(CTile::BUSINESS);
		mCity.Add(tile);
		Invalidate();
	}

	
}

void CChildView::OnCoalmineCreatecoalmine()
{
	if (mTotalMoney < mCoalminePrice)
	{
		wstringstream str;
		str << L"You do not have enough money to buy a Coalmine.\n\n" <<
			"Your current total money is: $" << mTotalMoney <<
			"\nThe cost of an Coalmine is: $" << mCoalminePrice;
		AfxMessageBox(str.str().c_str());
	}
	else
	{
		mTotalMoney = mTotalMoney - mCoalminePrice;

		auto tile = make_shared<CTileCoalmine>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		tile->SetZoning(CTile::BUSINESS);
		mCity.Add(tile);

		Invalidate();
	}
	
	
}


void CChildView::OnOremineHaulore()
{
	COreCounter visitor;
	mCity.Accept(&visitor);
	double totalProduction = visitor.GetTotalProduction();

	wstringstream str;
	str << L"The total production is " << totalProduction << L" tons.\n You just earned $" <<
		totalProduction*mOrePrice << " because the price of 1 ton of coal is worth $" << mOrePrice;
	AfxMessageBox(str.str().c_str());

	mTotalMoney = mTotalMoney + totalProduction*mOrePrice;

	CResetOre visitor2;
	mCity.Accept(&visitor2);
}


/*
CCoalCounter visitor;
mCity.Accept(&visitor);
double totalProduction = visitor.GetTotalProduction();

wstringstream str;
str << L"The total production is " << totalProduction << L" tons.\n You just earned $"<<
totalProduction*mCoalPrice << " because the price of 1 ton of coal is worth $" << mCoalPrice;
AfxMessageBox(str.str().c_str());

mTotalMoney = mTotalMoney + totalProduction*mCoalPrice;

CResetCoal visitor2;
mCity.Accept(&visitor2);
*/

/*

CCoalCounter visitor;
mCity.Accept(&visitor);
double totalProduction = visitor.GetTotalProduction();

wstringstream str;
str << L"The total production is " << totalProduction << L" tons.\n You just earned $"<<
totalProduction*mCoalPrice << " because the price of 1 ton of coal is worth $" << mCoalPrice;
AfxMessageBox(str.str().c_str());

mTotalMoney = mTotalMoney + totalProduction*mCoalPrice;

CResetCoal visitor2;
mCity.Accept(&visitor2);*/
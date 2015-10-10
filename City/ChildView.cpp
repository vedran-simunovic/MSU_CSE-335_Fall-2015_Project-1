/**
 * \file ChildView.cpp
 *
 * \author Charles B. Owen
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
#include "BuildingCounter.h"
#include "CoalCounter.h"
#include "ResetCoal.h"
#include "Trump.h"
#include "TransRotate.h"
#include "TileTransportation.h"
#include "PowerRotate.h"

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
    ON_COMMAND(ID_BUSINESSES_COALMINE, &CChildView::OnBusinessesCoalmine)
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
	ON_COMMAND(ID_BUSINESSES_HAULCOLE, &CChildView::OnBusinessesHaulcole)
	ON_COMMAND(ID_BUSINESSES_TRUMP, &CChildView::OnBusinessesTrump)
	ON_UPDATE_COMMAND_UI(ID_BUSINESSES_TRUMP, &CChildView::OnUpdateBusinessesTrump)
	ON_COMMAND(ID_POWER_BUILD, &CChildView::OnPowerBuild)
	ON_UPDATE_COMMAND_UI(ID_POWER_BUILD, &CChildView::OnUpdatePowerBuild)
	ON_COMMAND(ID_TRANSPORTATION_CURVEDROAD, &CChildView::OnTransportationCurvedroad)
	ON_COMMAND(ID_TRANSPORTATION_ROAD, &CChildView::OnTransportationRoad)
	ON_COMMAND(ID_TRANSPORTATION_ELEVATEDROAD, &CChildView::OnTransportationElevatedroad)
	ON_COMMAND(ID_TRANSPORTATION_INCLINEDROAD, &CChildView::OnTransportationInclinedroad)
	ON_COMMAND(ID_TRANSPORTATION_PLAINROAD, &CChildView::OnTransportationPlainroad)
	ON_WM_RBUTTONDOWN()
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

	if (mPowerActivate){
		// Bottom minus image size minus margin is top of the image
		mPowerToolbarTop = rect.Height() - mPowerToolbar->GetHeight();
		mPowerToolbarLeft = rect.Width() - mPowerToolbar->GetWidth();

		graphics.DrawImage(mPowerToolbar.get(), mPowerToolbarLeft, mPowerToolbarTop,
			mPowerToolbar->GetWidth(), mPowerToolbar->GetHeight());
	}


    /*
     * Actually Draw the city
     */
    mCity.OnDraw(&graphics);


	Pen pen(Color::Green, 2);

	// draw box over all of the tiles
	
	//if (!mNoneCheck && !mAgriculturalCheck && !mIndustrialCheck && !mResidentialCheck)
	/*
	for (auto tile : mCity)
	{
		tile->DrawBorder(&graphics, &pen);
	}*/

	

	// draw box only over the tile elements selected.

	if (mNoneCheck || mAgriculturalCheck || mIndustrialCheck || mResidentialCheck)
	{
		for (auto tile : mCity.GetZoning(mZoning))		
		{
			tile->DrawBorder(&graphics, &pen);
		}
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

    auto tile = mCity.HitTest(point.x, point.y);
    if (tile != nullptr) 
    {
		/// If the double clicked tile is a transportation tile, we need to rotate it.
		if (tile->GetZoning() == CTile::TRANSPORTATION)
		{
			CTransRotate visitor;

			tile->Accept(&visitor);
			// We double-clicked on a tile
			// Bring up the tile editing dialog box
			//tile->PropertiesDlg();
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
	if (mPowerActivate == true && (point.x>mPowerToolbarLeft && point.y > mPowerToolbarTop)){
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


	mGrabbedItem = mCity.HitTest(point.x, point.y);
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

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    OnMouseMove(nFlags, point);
}



/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if (nFlags & MK_LBUTTON)
        {
            mGrabbedItem->SetLocation(point.x, point.y);
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

        // Force the screen to redraw
        Invalidate();
    }
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
    CFileDialog dlg(true,  // true = Open dialog box
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


void CChildView::OnLandscapingRoad()
{
    auto tile = make_shared<CTileRoad>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}


void CChildView::OnBusinessesCoalmine()
{
    auto tile = make_shared<CTileCoalmine>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/** \endcond */

/** Menu handler that sets the border draw to none */
void CChildView::OnBorderNone()
{
	mZoning = CTile::NONE;
	mNoneCheck = !mNoneCheck;
	//mNoneCheck = true;
	mResidentialCheck = false;
	mIndustrialCheck = false;
	mAgriculturalCheck = false;
}

/** Menu handler that sets the border draw to residential*/
void CChildView::OnBorderResidential()
{
	mZoning = CTile::RESIDENTIAL;
	mNoneCheck = false;
	mResidentialCheck = !mResidentialCheck;
	//mResidentialCheck = true;
	mIndustrialCheck = false;
	mAgriculturalCheck = false;
}

/** Menu handler that sets the border draw to industrial */
void CChildView::OnBorderIndustrial()
{
	mZoning = CTile::INDUSTRIAL;
	mNoneCheck = false;
	mResidentialCheck = false;
	mIndustrialCheck = !mIndustrialCheck;
	//mIndustrialCheck = true;
	mAgriculturalCheck = false;
}

/** Menu handler that sets the border draw to agricultural */
void CChildView::OnBorderAgricultural()
{
	mZoning = CTile::AGRICULTURAL;
	mNoneCheck = false;
	mResidentialCheck = false;
	mIndustrialCheck = false;
	mAgriculturalCheck = !mAgriculturalCheck;
	//mAgriculturalCheck = true;
}

/** Menu handler that sets the border draw to none 
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mNoneCheck);
}


/** Menu handler that sets the border draw to residential
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderResidential(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mResidentialCheck);
}

/** Menu handler that sets the border draw to industrial
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderIndustrial(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mIndustrialCheck);
}

/** Menu handler that sets the border draw to agricultural 
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBorderAgricultural(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mAgriculturalCheck);
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

/** Menu handler that counts the tons of coal hauled */
void CChildView::OnBusinessesHaulcole()
{
	CCoalCounter visitor;
	mCity.Accept(&visitor);
	double totalProduction = visitor.GetTotalProduction();

	wstringstream str;
	str << L"The total production is " << totalProduction << L" tons";
	AfxMessageBox(str.str().c_str());

	CResetCoal visitor2;
	mCity.Accept(&visitor2);
}

/** Menu handler deals with trumping feature */
void CChildView::OnBusinessesTrump()
{
	mTrumpCheck = !mTrumpCheck;
}

/** Menu handler deals with trumping feature 
* \param pCmdUI This is pass to be able to change the checkmard on the screen
*/
void CChildView::OnUpdateBusinessesTrump(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mTrumpCheck);
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
 * 
 */
void CChildView::OnTransportationCurvedroad()
{
	auto tile = make_shared<CTileTransportation>(&mCity);
	tile->SetTransType(CTileTransportation::CURVED);
	tile->SetZoning(CTile::TRANSPORTATION);
	tile->SetLocation(InitialX, InitialY);
	tile->SetImage(L"road_ab.png");
	mCity.Add(tile);
	Invalidate();
}


/**
 * 
 */
void CChildView::OnTransportationRoad()
{
	auto tile = make_shared<CTileTransportation>(&mCity);
	tile->SetTransType(CTileTransportation::FLAT);
	tile->SetZoning(CTile::TRANSPORTATION);
	tile->SetLocation(InitialX, InitialY);
	tile->SetImage(L"road_ac.png");
	mCity.Add(tile);
	Invalidate();
}


/**
 * 
 */
void CChildView::OnTransportationElevatedroad()
{
	auto tile = make_shared<CTileTransportation>(&mCity);
	tile->SetTransType(CTileTransportation::ELEVATED);
	tile->SetZoning(CTile::TRANSPORTATION);
	tile->SetLocation(InitialX, InitialY);
	tile->SetImage(L"roadbridge_ac.png");
	mCity.Add(tile);
	Invalidate();
}


/**
 * 
 */
void CChildView::OnTransportationInclinedroad()
{
	auto tile = make_shared<CTileTransportation>(&mCity);
	tile->SetZoning(CTile::TRANSPORTATION);
	tile->SetTransType(CTileTransportation::INCLINED);
	tile->SetLocation(InitialX, InitialY);
	tile->SetImage(L"roadrampa_ac.png");
	mCity.Add(tile);
	Invalidate();
}




/**
 * 
 */
void CChildView::OnTransportationPlainroad()
{
	auto tile = make_shared<CTileTransportation>(&mCity);
	tile->SetZoning(CTile::TRANSPORTATION);
	tile->SetTransType(CTileTransportation::PLAIN);
	tile->SetLocation(InitialX, InitialY);
	tile->SetImage(L"roadint_abc.png");
	mCity.Add(tile);
	Invalidate();
}


/**
 * When we at build mode of power, right click the picture will rotate picture
 * \param nFlags 
 * \param point 
 */
void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	mGrabbedItem = mCity.HitTest(point.x, point.y);
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
	mCity.Add(tile);
	Invalidate();
}
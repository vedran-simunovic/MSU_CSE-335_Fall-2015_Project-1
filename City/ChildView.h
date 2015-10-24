/**
* \file ChildView.h
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*
* \brief Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/

#pragma once

#include "City.h"
#include "Tile.h"
#include "TilePower.h"
#include "TileTransportation.h"

class CTile;

/** \brief The child window our program draws in. */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
    void AddBuilding(const std::wstring &file);
    void AddLandscape(const std::wstring &file);
	void AddPower(CTilePower::PowerType);
	void AddTransportation(CTileTransportation::TransTileType type);
	void AddCar(const std::wstring &file);

    /// The city
    CCity mCity;

	/// The zoning
	CTile::Zonings mZoning = CTile::NONE;

	/// Check for vehicle mode ( can move the car with arroe keys )
	bool mVehicleMode = false;

	/// Checkmark for the trump option
	bool mTrumpCheck = false;

    /// True until the first time we draw
    bool mFirstDraw = true;

    long long mLastTime;    ///< Last time we read the timer
    double mTimeFreq;       ///< Rate the timer updates

    /// Any item we are currently dragging
    std::shared_ptr<CTile> mGrabbedItem;

	/// Total wallet money in US dollars $
	double mTotalMoney = 1000000;

	/// Price of building of all other tiles
	double mOtherTilesPrice = 0;

	/// Price of building a coalmine
	double mCoalminePrice = 5000;

	/// Price of building a oremine
	double mOreminePrice = 50000;

	/// Price of promotion of business tile
	double mPromotionPrice = 1000;

	/// Money that 1 ton of coal provides in US dollars $
	double mCoalPrice = 1000;

	/// Money that 1 ton of coal provides in US dollars $
	double mOrePrice = 500;

    std::unique_ptr<Gdiplus::Bitmap> mTrashcan; ///< Trashcan image to use
    int mTrashcanTop = 0;           ///< Top line of the trashcan in pixels
    int mTrashcanRight = 0;         ///< Right side of the trashcan in pixels

	std::unique_ptr<Gdiplus::Bitmap> mWallet; ///< Wallet image to use
	int mWalletTop = 0;           ///< Top line of the wallet in pixels
	int mWalletRight = 0;         ///< Right side of the wallet in pixels

	std::unique_ptr<Gdiplus::Bitmap> mInventory; ///< Wallet image to use
	int mInventoryTop = 0;           ///< Top line of the wallet in pixels
	int mInventoryRight = 0;         ///< Right side of the wallet in pixels

	std::unique_ptr<Gdiplus::Bitmap> mPowerToolbar;	///< toolbar image for power
	bool mPowerActivate = false;			///< if power toolbar checked
	int mPowerToolbarTop = 0;           ///< Top line of the power toolbar in pixels
	int mPowerToolbarLeft = 0;         ///< Leftside of the power toolbar in pixels

	std::unique_ptr<Gdiplus::Bitmap> mScroll;	///< toolbar image for scrolling
	bool mScrollActivate = false;			///< if scrolling toolbar checked
	int mScrollTop = 0;				///< Top line of the scrolling toolbar in pixels
	int mScrollLeft= 0;			///< Leftside of the scrolling toolbar in pixels

	double mOriginOffsetX = 0;	///< offset for origin point in x
	double mOriginOffsetY = 0;	///< offset for origin point in y

	double mScrollOffsetX = 0;	///< offset for origin point in x, when scrolling.
	double mScrollOffsetY = 0;	///< offset for origin point in y, when scrolling.

	double mStartX = 0;		///< start point for scrolling in x
	double mStartY = 0;		///< start point for scrolling in y

	double mScale = 1;		///< scale


public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnFileOpen();
    afx_msg void OnFileSaveas();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

    /** \cond */
    afx_msg void OnBuildingsFarmhouse();
    afx_msg void OnLandscapingGrass();
    afx_msg void OnLandscapingSpartystatue();
    afx_msg void OnBuildingsBlacksmithshop();
    afx_msg void OnLandscapingTallgrass();
    afx_msg void OnBuildingsBrownhouse();
    afx_msg void OnBuildingsYellowhouse();
    afx_msg void OnBuildingsF();
    afx_msg void OnBuildingsHospital();
    afx_msg void OnBuildingsMarket();
    afx_msg void OnBuildingsCondos();
    afx_msg void OnLandscapingTree();
    afx_msg void OnLandscapingTrees();
    afx_msg void OnLandscapingBigtrees();
	afx_msg void OnLandscapingRoad();
	
	
	afx_msg void OnTransportationDeclinedroad();
	/** \endcond */
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBorderNone();
	afx_msg void OnBorderResidential();
	afx_msg void OnBorderIndustrial();
	afx_msg void OnBorderAgricultural();
	afx_msg void OnUpdateBorderNone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderResidential(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderIndustrial(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderAgricultural(CCmdUI *pCmdUI);
	afx_msg void OnBuildingsCount();
	
	
	afx_msg void OnPowerBuild();
	afx_msg void OnUpdatePowerBuild(CCmdUI *pCmdUI);
	afx_msg void OnTransportationCurvedroad();
	afx_msg void OnTransportationRoad();
	afx_msg void OnTransportationElevatedroad();
	afx_msg void OnTransportationInclinedroad();
	
	afx_msg void OnTransportationPlainroad();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnConstructionGrasssite();
	afx_msg void OnBorderConstruction();
	afx_msg void OnUpdateBorderConstruction(CCmdUI *pCmdUI);
	afx_msg void OnBorderTransportation();
	afx_msg void OnBorderPower();
	afx_msg void OnUpdateBorderTransportation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderPower(CCmdUI *pCmdUI);
	afx_msg void OnTilesinfoTilesincity();
	afx_msg void OnTransportationCar();
	afx_msg void OnTilesinfoPartiallyoverlapping();
	afx_msg void OnTilesinfoFullyoverlapping();
	
	afx_msg void OnTransportationVehiclemode();
	afx_msg void OnUpdateTransportationVehiclemode(CCmdUI *pCmdUI);
	afx_msg void OnCoalmineCreatecoalmine();
	afx_msg void OnCoalmineTrump();
	afx_msg void OnUpdateCoalmineTrump(CCmdUI *pCmdUI);
	afx_msg void OnCoalmineHaulcole();
	afx_msg void OnBankCreatebank();
	afx_msg void OnOremineBuyoremine();
	afx_msg void OnBorderCar();
	afx_msg void OnBorderBusiness();
	afx_msg void OnUpdateBorderCar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderBusiness(CCmdUI *pCmdUI);
	afx_msg void OnOremineHaulore();
};


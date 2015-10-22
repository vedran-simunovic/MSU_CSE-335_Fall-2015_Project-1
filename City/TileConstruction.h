/**
* \file TileConstruction.h
*
* \author Vedran Simunovic
*
* \brief Base Class that implements a Construction tile
*/

#pragma once
#include "Tile.h"

/**
* \brief Base class for construction tiles
*/
class CTileConstruction :
	public CTile
{
public:
	CTileConstruction(CCity *city);

	/// \brief Default constructor (disabled)
	CTileConstruction() = delete;

	/// \brief Copy constructor (disabled)
	CTileConstruction(const CTileConstruction &) = delete;

	~CTileConstruction();

	/// The possible clearing levels
	enum Clearing {
		CLEARING_0 = 0,	  ///< Clearing step 0
		CLEARING_1 = 1,   ///< Clearing step 1
		CLEARING_2 = 2,   ///< Clearing step 2
		CLEARING_3 = 3,   ///< Clearing step 3
		CLEARING_4 = 4,   ///< Clearing step 4
		CLEARING_5 = 5,   ///< Clearing step 5
		CLEARING_6 = 6,   ///< Clearing step 6
		CLEARING_7 = 7,   ///< Clearing step 7
		CLEARING_8 = 8,   ///< Clearing step 8
	};    ///< Clearing level tracker

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitConstruction(this); }

	void Update(double elapsed);
	
	/** Sets the clearing level
	* \param clearingLevel The clearing level to be newly set */
	void SetClearingLevel(Clearing clearingLevel) { mClearingLevel = clearingLevel; }

	/** Gets the clearing level
	* \return mClearingLevel The clearing level of the construction */
	Clearing GetClearingLevel() { return mClearingLevel; }

	/** Sets the construction flag to 
	* signify the start of construction 
	* \param start The start of construction flag*/
	virtual void SetStartFlag(bool start) { mStartConstruction = start; }

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	// This is for drawing the border around the big spartan stadium icon
	/** \brief Draw this item
	* \param scrollOffsetX offset for x location
	* \param scrollOffsetY offset for y location
	* \param scale scale of draw
	* \param graphics The graphics context to draw on 
	* \param pen pen object
	*/
	virtual void DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen, int scrollOffsetX, int scrollOffsetY, double scale) { CTile::DrawBorder(graphics, pen, scrollOffsetX, scrollOffsetY, scale); }

	/** \brief Set the item location
	* \param x X location
	* \param y Y location */
	virtual void SetLocation(int x, int y) { CTile::SetLocation(x, y); }

private:
	double mDuration = 0;///< Duration of time the animations have been changing.

	Clearing mClearingLevel = CLEARING_0;///< The current clearing level

	bool mStartConstruction = false; ///< This is a flag for the tile so that it knows to start clearing
	
	std::wstring mFile;///< File that the image will be saved from
};
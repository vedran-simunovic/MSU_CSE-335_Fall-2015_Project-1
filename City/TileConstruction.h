/**
* \file TileConstruction.h
*
* \author Vedran Simunovic
*
* \brief Class that implements a Landscape tile
*/

#pragma once
#include "Tile.h"

/**
* \brief A Construction tile
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

	/// The possible construction statuses
	enum ConstructionStatus {
		NOT_COMPLETE = 0,	///< Construction has not been completed
		STADIUM = 1,		///< Construction is completed into a stadium
		OREMINE = 2,		///< Construction is completed into an oremine
	};    ///< Construction Status Tracker

	/// The possible oremine levels
	enum OremineLevel {
		OREMINE_1 = 1,   ///< Oremine step 1
		OREMINE_2 = 2,   ///< Oremine step 2
		OREMINE_3 = 3,   ///< Oremine step 3
		OREMINE_4 = 4,   ///< Oremine step 4
		OREMINE_5 = 5,   ///< Oremine step 5
		OREMINE_6 = 6,   ///< Oremine step 6
		OREMINE_7 = 7,   ///< Oremine step 7
		OREMINE_8 = 8,   ///< Oremine step 8
	};    ///< Oremine level tracker

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitConstruction(this); }

	void CTileConstruction::Update(double elapsed);
	
	/** Sets the duration
	* \param duration The duration to be newly set */
	void SetDuration(double duration) { mDuration = duration; }

	/** Gets the duration
	* \return mDuration The duration*/
	double GetDuration() { return mDuration; }

	/** Sets the clearing level
	* \param clearingLevel The clearing level to be newly set */
	void SetClearingLevel(Clearing clearingLevel) { mClearingLevel = clearingLevel; }

	/** Gets the clearing level
	* \return mClearingLevel The clearing level of the construction */
	Clearing GetClearingLevel() { return mClearingLevel; }

	/** Sets the oremine level
	* \param oremineLevel The ormine level to be newly set */
	void SetOremineLevel(OremineLevel oremineLevel) { mOremineLevel = oremineLevel; }

	/** Gets the oremine level
	* \return mOremineLevel The oremine level of the oremine */
	OremineLevel GetOremineLevel() { return mOremineLevel; }

	/** Sets the clearing flag to signify the start of construction */
	virtual void SetClearFlag() override { mStartClearing = true; }

	/** Gets the clearing flag to signify the start of construction
	* \return mStartClearing The clearing flag of the construction */
	bool GetClearFlag() { return mStartClearing; }

	/** Sets the rising flag to signify if sequence of oremine states is increasing or decreasing */
	void SetRisingFlag(bool rising) { mRising = rising; }

	/** Gets the rising flag
	* \return mRising The clearing flag of the construction */
	bool GetRisingFlag() { return mRising; }

	/** Sets the status
	* \param status The status of the construction build */
	void SetStatus(ConstructionStatus status) { mStatus = status; }

	/** Gets the status
	* \return mStatus The duration*/
	ConstructionStatus GetStatus() { return mStatus; }

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	// This is for drawing the border around the big spartan stadium icon
	/** \brief Draw this item
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics *graphics, double offsetX, double offsetY) override;

	virtual void DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen) override;

	virtual void SetLocation(int x, int y);

	

	

private:
	/// Duration of time the animations have been changing.
	double mDuration = 0;

	/// The current clearing level
	Clearing mClearingLevel = CLEARING_0;

	/// The current clearing level
	OremineLevel mOremineLevel = OREMINE_1;

	/// The current construction status
	ConstructionStatus mStatus = NOT_COMPLETE;

	/// This is a flag for the tile so that it knows to start clearing
	bool mStartClearing = false;

	/// This is a flag that helps the program know if it is supposed
	/// to transition from 1 to 2, 2 -> 3 etc......or 3->2 , 2->1 etc.
	bool mRising = true;

	std::wstring mFile;

	int mX = 0;

	int mY = 0;


};
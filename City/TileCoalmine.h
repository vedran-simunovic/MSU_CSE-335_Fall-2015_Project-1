/**
* \file TileCoalmine.h
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"

/// The production scale factor for normal production
const int NormalProduction = 1;

/// The production scale factor for trumped production
const int TrumpProduction = 2;

/**
* \brief A Landscape tile
*/
class CTileCoalmine : public CTile
{
public:
    CTileCoalmine(CCity *city);

    /// \brief Default constructor (disabled)
    CTileCoalmine() = delete;

    /// \brief Copy constructor (disabled)
    CTileCoalmine(const CTileCoalmine &) = delete;

    ~CTileCoalmine();

	/// The possible trumping levels
	enum Trumping {
		NO_TRUMP = 0,   ///< No trump activated
		FIRST_TRUMP = 1,      ///< First trump activated
		SECOND_TRUMP = 2,       ///< Second trump activate: meltdown

	};    ///< Trumping tracker

	/// The possible level ups for the oremine
	enum CoalmineLevelUp {
		LEVEL_1 = 1,   ///< Level 1, normal
		LEVEL_2 = 2,   ///< Level 2, promoted level	
	};    ///< Oremine level up

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCoalmine(this); }

	void CTileCoalmine::Update(double elapsed);

	/** Sets the duration
	* \param duration The duration to be newly set */
	void SetDuration(double duration) { mDuration = duration; }

	/** Gets the duration
	* \return mDuration The duration*/
	double GetDuration() { return mDuration; }

	/** Sets the production
	* \param production The production to be newly set */
	void SetProduction(double production) { mProduction = production; }

	/** Gets the production
	* \return mProduction The amount of the coal */
	double GetProduction() { return mProduction*mCoalminePromotionLevel; }

	/** Sets the trump level
	* \param trumpLevel The trump level to be newly set */
	void SetTrump(Trumping trumpLevel) { mTrumpLevel = trumpLevel; }

	/** Gets the trump level
	* \return mTrumpLevel The trump level of the coal mine */
	Trumping GetTrump() { return mTrumpLevel; }

	/** Sets the trump scale
	* Since it can only be set to the trump level, this is what it gets set to */
	void SetTrumpScale() { mTrumpScale = TrumpProduction; }

	/** Gets the trump level
	* \return mTrumpScale The current trump scale of the coal mine*/
	int GetTrumpScale() { return mTrumpScale; }

	/** Gets the level up
	* \return mCoalminePromotionLevel The promotion level of the coal mine */
	CoalmineLevelUp GetPromotionLevel() { return  mCoalminePromotionLevel; }

	void virtual Promote();

	

private:
	/// Duration that the coal has been in its current production mode
	double mDuration = 0;

	/// The amount of coal produced by the coal mine
	double mProduction = 0;

	/// The current trump level. Signifies how many times trump has been clicked on for the coalmine
	Trumping mTrumpLevel = NO_TRUMP;

	/// The scale factor that changes after trump is clicked. When trump is clicked,
	/// necessary production time is decreased.
	int mTrumpScale = NormalProduction;

	CoalmineLevelUp mCoalminePromotionLevel = LEVEL_1; ///< The current prmotion level

	/// This is a flag that makes it so that the construction of 
	/// an oremine can start only if the plain construction tile
	/// is overlapping with a power tile.
	bool mPowerOverlap = true;
};


/**
 * \file TileOremine.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * Oremine class to draw oremine
 */

#pragma once
#include "TileConstruction.h"
/**
 * This class draws the stadium
 */
class CTileOremine :
	public CTileConstruction
{
public:
	CTileOremine(CCity *city);

	/// \brief Default constructor (disabled)
	CTileOremine() = delete;

	/// \brief Copy constructor (disabled)
	CTileOremine(const CTileOremine &) = delete;

	~CTileOremine();

	/// The possible oremine animations
	enum OremineAnimation {
		OREMINE_1 = 1,   ///< Oremine step 1
		OREMINE_2 = 2,   ///< Oremine step 2
		OREMINE_3 = 3,   ///< Oremine step 3
		OREMINE_4 = 4,   ///< Oremine step 4
		OREMINE_5 = 5,   ///< Oremine step 5
		OREMINE_6 = 6,   ///< Oremine step 6
		OREMINE_7 = 7,   ///< Oremine step 7
		OREMINE_8 = 8,   ///< Oremine step 8
	};    ///< Oremine animation tracker

	/// The possible level ups for the oremine
	enum OremineLevelUp {
		LEVEL_1 = 1,   ///< Level 1, normal
		LEVEL_2 = 2,   ///< Level 2, promoted level	
	};    ///< Oremine level up


	void Update(double elapsed);

	/** Sets the clearing flag to signify the start of construction */
	virtual void SetClearFlag() override { mStartClearing = true; }

	/** Gets the clearing flag to signify the start of construction
	* \return mStartClearing The clearing flag of the construction */
	bool GetClearFlag() { return mStartClearing; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitOremine(this); }

	/** Sets the oremine level
	* \param oremineLevel The ormine level to be newly set */
	void SetOremineAnimationLevel(OremineAnimation oremineLevel) { mOremineAnimationLevel = oremineLevel; }

	/** Gets the oremine level
	* \return mOremineLevel The oremine level of the oremine */
	OremineAnimation GetOremineAnimationLevel() { return mOremineAnimationLevel; }

	/** Sets the construction flag to
	* signify the start of construction
	* \param start The start of construction flag*/
	virtual void SetStartFlag(bool start) { mStartConstruction = start; }


	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void virtual Promote();

	/** Gets the production
	* \return mProduction*mOreminePromotionLevel The amount of the ore */
	int GetProduction() { return mProduction*mOreminePromotionLevel; }

	/** Sets the production
	* \param production The production to be newly set */
	void SetProduction(double production) { mProduction = production; }

	/** Gets the level up
	* \return mCoalminePromotionLevel The promotion level of the coal mine */
	OremineLevelUp GetPromotionLevel() { return  mOreminePromotionLevel; }

private:
	OremineAnimation mOremineAnimationLevel = OREMINE_1; ///< The current animation level

	OremineLevelUp mOreminePromotionLevel = LEVEL_1; ///< The current prmotion level

	bool mStartClearing = false; ///< This is a flag for the tile so that it knows to start clearing

	bool mStartConstruction = false; ///< This is a flag for the tile so that it knows to start clearing

	double mDuration = 0; ///< Duration of time the animations have been changing.

	std::wstring mFile; ///< File that the image will be saved from

	/// This is a flag that helps the program know if it is supposed
	/// to transition from 1 to 2, 2 -> 3 etc......or 3->2 , 2->1 etc.
	bool mRising = true;

	/// The amount of ore produced by the ore mine
	double mProduction = 0;
	
	/// This is to do an action only one single time
	bool mDoOnceFlag = true;
};


/**
 * \file TileStadium.h
 *
 * \author Vedran Simunovic
 *
 * Stadium class that implements stadium
 */

#pragma once
#include "TileConstruction.h"
/**
 * This class draws the stadium
 */
class CTileStadium :
	public CTileConstruction
{
public:
	CTileStadium(CCity *city);

	/// \brief Default constructor (disabled)
	CTileStadium() = delete;

	/// \brief Copy constructor (disabled)
	CTileStadium(const CTileStadium &) = delete;

	~CTileStadium();

	void Update(double elapsed);

	/** Sets the clearing flag to signify the start of construction */
	virtual void SetClearFlag() override { mStartClearing = true; }

	/** Sets the construction flag to signify the start of construction */
	virtual void SetStartFlag(bool start) { mStartConstruction = start; }


private:	
	double mDuration = 0;		///< Duration of time the animations have been changing.
	
	bool mStartClearing = false;///< This is a flag for the tile so that it knows to start clearing
	
	bool mStartConstruction = false;///< This is a flag for the tile so that it knows to start clearing
	
	std::wstring mFile;			///< File that the image will be saved from

	int mX = 0;

	int mY = 0;
};


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

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	// This is for drawing the border around the big spartan stadium icon

	virtual void DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen, int scrollOffsetX, int scrollOffsetY, double scale) override;

	virtual void SetLocation(int x, int y);
	
private:	
	double mDuration = 0;			///< Duration of time the animations have been changing.
	
	bool mStartClearing = false;	///< This is a flag for the tile so that it knows to start clearing
	
	bool mStartConstruction = false;///< This is a flag for the tile so that it knows to start clearing
	
	std::wstring mFile;				///< File that the image will be saved from

	int mX = 0;						///< X coordinate for drawing border for the stadium

	int mY = 0;						///< Y coordinate for drawing border for the stadium
};


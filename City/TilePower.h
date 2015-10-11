/**
 * \file TilePower.h
 *
 * \author Nan Du
 *
 * class for power tile
 */

#pragma once
#include "Tile.h"
#include "City.h"


/** A power tile
 *  power tile
 */
class CTilePower :
	public CTile
{
public:

	/// Type for diffrent power tile
	enum PowerType
	{
		NONE = 0,
		GRID = 1,
		LGRID = 2,
		TGRID = 3,
		XGRID = 4,
		SUBSTATION = 5,
		POWERPLANT = 6,
		SOLARSTATION = 7
	};

	/// Type for diection of tile
	enum PowerDirection
	{
		EAST = 0,
		SOUTH = 1,
		WEST = 2,
		NORTH = 3,
	};

	CTilePower(CCity *city, PowerType type);

	/// \brief Default constructor (disabled)
	CTilePower() = delete;

	/// \brief Copy constructor (disabled)
	CTilePower(const CTilePower &) = delete;

	virtual ~CTilePower();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitPower(this); }

	/** return power type*/
	PowerType GetPowerType() { return mPowerType; }

	void SetPowerType(CTilePower::PowerType type) { mPowerType = type; }

	bool GetConnected() { return mConnected; }

	PowerDirection GetPowerDirection() { return mPowerDirection; }

	void SetConnection(bool connect) { mConnected = connect; }

	void SetPowerDirection(CTilePower::PowerDirection direction) { mPowerDirection = direction; }

	void RotateImage();

private:

	PowerType mPowerType = NONE;	///< type of tile
	std::wstring mFile;
	bool mConnected = false;			///< whethe this tile connect to the power plant

	PowerDirection mPowerDirection = EAST;	///< dirction of tile
};


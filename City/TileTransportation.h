/**
 * \file TileTransportation.h
 *
 * \author Helena Narowski
 *
 * 
 */

#pragma once

#include "Tile.h"
/**
 * 
 */
class CTileTransportation : public CTile
{
public:

	enum TransTileType
	{
		NONE = 0,
		PLAIN = 1,
		FLAT = 2,
		CURVED = 3,
		INCLINED = 4,
		ELEVATED = 5
	};

	/** \brief The tile zoning
	* \returns Zoning value */
	CTileTransportation::TransTileType GetTransType() { return mTransType; }

	/** \brief Set the tile zoningsss
	* \param zoning Zoning value */
	void SetTransType(CTileTransportation::TransTileType transTile) { mTransType = transTile; }

	CTileTransportation(CCity *city);
	//virtual ~CTileTransportation();

	/// \brief Copy constructor (disabled)
	CTileTransportation(const CTileTransportation &) = delete;

	~CTileTransportation();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void SetAdjacencies(bool ul, bool ur, bool ll, bool lr);
	//void SetTransTileType();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitTrans(this); }

	int GetRotationPos() { return mRotationPos; }
	void SetRotationPos(int pos) { mRotationPos = pos; }
	void IncrementRotationPos();

private:
	/// The current adjacency integer or -1 if none
	int mCurrentAdj = -1;
	int mRotationPos = 0;

	/// Any zoning for this property
	TransTileType mTransType = NONE;

};


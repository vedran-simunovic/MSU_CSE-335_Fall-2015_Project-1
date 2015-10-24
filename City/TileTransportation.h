/**
 * \file TileTransportation.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * \brief Class that implements a Transportation tile
 */

#pragma once

#include "Tile.h"

/** A transportation tile
 *  trans tiles
 */
class CTileTransportation : public CTile
{
public:

	/// The possible transportation tile types
	enum TransTileType
	{
		NONE = 0,///< No current zoning
		PLAIN = 1, /// Plain tile
		FLAT = 2, /// Flat tile
		CURVED = 3, /// Curved tile
		INCLINED = 4, /// Inclined tile
		ELEVATED = 5, /// Elevated tile
	};	 ///< Transportation levels

	/** \brief The tile zoning
	* \returns Zoning value */
	CTileTransportation::TransTileType GetTransType() { return mTransType; }

	/** \brief Set the tile zoningsss
	* \param transTile Zoning value */
	void SetTransType(CTileTransportation::TransTileType transTile) { mTransType = transTile; }

///	CTileTransportation(CCity *city);
	CTileTransportation(CCity *city, TransTileType type);

	//virtual ~CTileTransportation();

	/// \brief Copy constructor (disabled)
	CTileTransportation(const CTileTransportation &) = delete;

	~CTileTransportation();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	void SetAdjacencies(bool ul, bool ur, bool ll, bool lr);

	/** \brief Set the trans tile type
	* \param type Trans type */
	void SetTransTileType(TransTileType type) { mTransType = type; }

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitTrans(this); }

	/** \brief Gets the rotation position 
	* \returns rotation value */
	int GetRotationPos() { return mRotationPos; }

	/** \brief Set the tile rotation value
	* \param pos position value */
	void SetRotationPos(int pos) { mRotationPos = pos; }

	/** \brief Rotation position */
	void IncrementRotationPos();

private:
	/// The current adjacency integer or -1 if none
	int mCurrentAdj = -1;

	/// The current rotation position integer or 0 if none
	int mRotationPos = 0;

	std::wstring mFile;	///< File that the image will be saved from

	/// Any zoning for this property
	TransTileType mTransType = NONE;

};


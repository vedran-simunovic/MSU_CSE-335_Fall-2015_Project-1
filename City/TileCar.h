/**
 * \file TileCar.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * 
 */

#pragma once
#include "Tile.h"

/** Car object class
 * 
 */
class CTileCar :
	public CTile
{
public:
	CTileCar(CCity *city);
	//virtual ~CTileCar();

	/// \brief Default constructor (disabled)
	CTileCar() = delete;

	/// \brief Copy constructor (disabled)
	CTileCar(const CTileCar &) = delete;

	~CTileCar();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCar(this); }

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	//void SetTileUnderRotation(int rot) { mTransTileUnderRotation = rot; }
	//int GetTileUnderRotation() { return mTransTileUnderRotation; }

//	void SetTransTileUnder(string tile) { mTransTileUnder = tile; }
//	string GetTransTileUnder(){ return mTransTileUnder; }
//
//private:
//	string mTransTileUnder = "flat"; // Initialized to flat
//	int mTransTileUnderRotation = 0; // Initialized to zero.

};


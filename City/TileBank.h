/**
 * \file TileBank.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * 
 */

#pragma once
#include "Tile.h"
class CTileBank :
	public CTile
{
public:
	CTileBank(CCity *city);

	/// \brief Default constructor (disabled)
	CTileBank() = delete;

	/// \brief Copy constructor (disabled)
	CTileBank(const CTileBank &) = delete;

	~CTileBank();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitBank(this); }
};


/**
* \file TileLandscape.h
*
* \author Helena Narowski
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Landscape tile
*/
class CTileLandscape : public CTile
{
public:
	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitLandscape(this); }

    CTileLandscape(CCity *city);

    /// \brief Default constructor (disabled)
    CTileLandscape() = delete;

    /// \brief Copy constructor (disabled)
    CTileLandscape(const CTileLandscape &) = delete;

    ~CTileLandscape();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

};


/**
 * \file Tile.h
 *
 * \author Vedran Simunovic, Nan Du, Helena Narowski
 *
 * \brief Base class for any tile in our city
 */

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "TileVisitor.h"

class CCity;

/**
 * \brief Base class for any tile in our city
 */
class CTile
{
public:
    /// The possible tile zonings
    enum Zonings {NONE=0,   ///< No current zoning
        RESIDENTIAL=1,      ///< Residential zoning
        INDUSTRIAL=2,       ///< Industrial zoning
        AGRICULTURAL=3,		///< Agricultural zoning
		TRANSPORTATION=4,	///< Transportational zoning
		POWER=5,			///< Power zoning
		CONSTRUCTIONAL=6,	///< Constructional zoning
		CAR=7,				///< Car zoning
		BUSINESS_OREMINE=8,	///< Business zoning, make money & buy only with these tiles
		BUSINESS_COALMINE = 9, ///< Business zoning coalmine, make money & buy only with these tiles
		BANK=10,			///< Bank zoning, used to know when to deposit money into the wallet
	};   /// The possible tile zonings in the program
	

    /** The directory were the images are stored */
    static const std::wstring ImagesDirectory;

    /** The grid spacing in the city */
    static const int GridSpacing = 64;

    /// \brief Default constructor (disabled)
    CTile() = delete;

    /// \brief Copy constructor (disabled)
    CTile(const CTile &) = delete;

    virtual ~CTile();

    void SetImage(const std::wstring &file);

    /** \brief Get the file name for this tile image
     * \returns Filename or blank if none */
    std::wstring GetFile() { return mFile; }

    /** \brief The X location of the center of the tile
    * \returns X location in pixels */
    int GetX() const { return mX; }

    /** \brief The Y location of the center of the tile
    * \returns Y location in pixels */
    int GetY() const { return mY; }

    /** \brief Set the item location
    * \param x X location
    * \param y Y location */
    virtual void SetLocation(int x, int y) { mX = x; mY = y; }

    /** \brief Draw this item
    * \param graphics The graphics context to draw on */
    virtual void Draw(Gdiplus::Graphics *graphics, double offsetX, double offsetY);

	void CTile::DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen, int scrollOffsetX, int scrollOffsetY, double scale);

    /** \brief Test this item to see if it has been clicked on
    * \param x X location on the aquarium to test
    * \param y Y location on the aquarium to test
    * \return true if clicked on */
	bool HitTest(int x, int y, double offsetX, double offsetY);

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node);
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

    /// \brief Handle updates for animation
    /// \param elapsed The time since the last update
    virtual void Update(double elapsed) {}

    /// \brief Get the city this item is in
    /// \returns City pointer
    CCity *GetCity() { return mCity; }

    void QuantizeLocation();

    /**
    * \brief Get any adjacent tile.
    *
    * Given a tile in the city, this determines if there is another
    * tile adjacent to it. The parameters dx, dy determine which direction
    * to look.
    *
    * The values for specific adjacencies (dx, dy, and direction):
    *    - -1 -1 Upper left
    *    - 1 -1 Upper right
    *    - -1 1 Lower left
    *    - 1 1 Lower right
    *
    * \param dx Left/right determination, -1=left, 1=right
    * \param dy Up/Down determination, -1=up, 1=down
    * \returns Adjacent tile or nullptr if none.
    */
    virtual std::shared_ptr<CTile> GetAdjacent(int dx, int dy);


    /** \brief The tile zoning
    * \returns Zoning value */
    CTile::Zonings GetZoning() { return mZoning; }

    /** \brief Set the tile zoning
    * \param zoning Zoning value */
    void SetZoning(CTile::Zonings zoning) { mZoning = zoning; }

    void PropertiesDlg();

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) = 0;

	virtual void SetClearFlag();

	virtual void Promote();

	/**
	* set connection
	* \param connect whether connect or not
	*/
	virtual void SetConnection(bool connect) { mConnected = connect; };

	/**
	* get flag for DFS
	* \returns if the tile already been visited in DFS
	*/
	virtual bool IsVisited() { return DFSvisited; }

	bool CheckAdjacentConnection();

protected:
    CTile(CCity *city);

	bool mConnected = false;		///< flag for connect to plant

	bool DFSvisited = false;		///< flag for DFS visit

private:
    /// The city this item is contained in
    CCity   *mCity;

    // Item location in the aquarium
    int   mX = 0;     ///< X location for the center of the item
    int   mY = 0;     ///< Y location for the center of the item

    /// The image of this tile
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

    /// The file for this item
    std::wstring mFile;

    /// Any zoning for this property
    Zonings mZoning = NONE;

	/// need for this tile
	int mPowerNeed = 0;
};


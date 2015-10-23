/**
 * \file City.h
 *
 * \author Helena Narowski
 *
 * \brief Class that implements a simple city with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>

#include "XmlNode.h"
#include "Tile.h"

/**
 * \brief Implements a simple city with tiles we can manipulate
 */
class CCity
{
public:
    CCity();
    virtual ~CCity();

    /// The spacing between grid locations
    static const int GridSpacing = 32;

    void Add(std::shared_ptr<CTile> item);
	std::shared_ptr<CTile> CCity::HitTest(int x, int y, double offsetX, double offsetY);
    void MoveToFront(std::shared_ptr<CTile> item);
    void DeleteItem(std::shared_ptr<CTile> item);

	std::shared_ptr<CTile> FindCar();

    void OnDraw(Gdiplus::Graphics *graphics, double offsetX, double offsetY);

    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();

    void Update(double elapsed);
    void SortTiles();

    std::shared_ptr<CTile> GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy);
    std::shared_ptr<CTile> GetAdjacent(CTile *tile, int dx, int dy);

	void Accept(CTileVisitor *visitor);

	int CountTiles();

	int CountPartialOverlapping();
	int CountFullyOverlapping();


	/** Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** Constructor
		* \param city The city we are iterating over 
		\param pos The current position we are at in the iteration */
		Iter(CCity *city, int pos) : mCity(city), mPos(pos) {}

		/** Test for end of the iterator
		* \param other This just passed in the other iterator object that is being compared against
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}
		
		

	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
	};// End of Iter Class

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mTiles.size()); }


	/** Iterator that iterates over the zoning city tiles */
	class ZoningIter
	{
	public:
		/** Constructor
		* \param city The city we are zoning iterating over 
		\param pos The current position we are at in the iteration 
		\param zoning The zoning type that we are interested in */
		ZoningIter(CCity *city, int pos, CTile::Zonings zoning) : mCity(city), mPos(pos), mZoning(zoning) {}

		/** Test for end of the zoning iterator
		* \param other This just passed in the other iterator object that is being compared against
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const ZoningIter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		
		const ZoningIter &operator++();
		/*{
			mPos++;
			return *this;
		}*/

	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
		CTile::Zonings mZoning; ///< This is the zoning type for the iterator
	};// End of ZoningIter Class

	//
	//
	//	Supporting Class for ZonigIter
	//
	//
	/** A class we return to support iterating over
	* only specific zonings in the collection */
	class ZoningIterSupport 
	{
	public:
		/** Constructor
		* \param city The city we are iteratoring over
		* \param zoning The zoning we are interested in */
		ZoningIterSupport(CCity *city, CTile::Zonings zoning) : mCity(city), mZoning(zoning) {}

		
		ZoningIter begin(); 

		/** Get an iterator for the end of the collection
		* \returns ZoningIter object at position past the end */
		ZoningIter end() { return ZoningIter(mCity, mCity->mTiles.size(),mZoning); }

	private:
		CCity *mCity;			///< City we are iterating over
		CTile::Zonings mZoning;	///< This is the zoning type for the iterator

	};

	
	/** Get a zoning iterator support object
	* \param zoning The zoning we are interested in
	* \returns ZoningIterSupport object
	*/
	ZoningIterSupport GetZoning(CTile::Zonings zoning) { return ZoningIterSupport(this, zoning); }

	/// Get the number of cars in the city
	int GetCarCount() { return mCarCount; }

	/// Set the number of cars in the city
	void SetCarCount(int count){ mCarCount = count; }

private:
    void XmlTile(const std::shared_ptr<xmlnode::CXmlNode> &node);
    void BuildAdjacencies();

    /// All of the tiles that make up our city
    std::vector<std::shared_ptr<CTile> > mTiles;

    /// Adjacency lookup support
    std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;

	/// the power product of all city
	int mTotalPowerProduct = 0;

	/// the power need of all city
	int mTotalPowerNeed = 0;

	/// number of cars in city
	int mCarCount = 0;
};


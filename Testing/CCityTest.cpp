#include "stdafx.h"
#include "CppUnitTest.h"

#include "City.h"
#include "TileRoad.h"

#include "TileRoad.h"
#include "TileLandscape.h"
#include "TileCoalmine.h"
#include "TileBuilding.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/**
	* \brief This is an implementation of a test visitor
	*/
	class CTestVisitor : public CTileVisitor
	{
	public:

		/** Road visitor function
		* \param road The pointer to the road object being visited */
		virtual void VisitRoad(CTileRoad *road) { mNumRoads++; }
		int mNumRoads = 0;	///< Total roads visited

		/** Building visitor function
		* \param building The pointer to the building object being visited */
		virtual void VisitBuilding(CTileBuilding *building) { mNumBuildings++; }
		int mNumBuildings = 0;	///< Total buildings visited

		/** Coal mine visitor function
		* \param coalmine The pointer to the coalmine object being visited */
		virtual void VisitCoalmine(CTileCoalmine *coalmine) { mNumCoalmines++; }
		int mNumCoalmines = 0;	///< Total coalmines visited

		/** Landscape visitor function
		* \param landscape The pointer to the road object being visited */
		virtual void VisitLandscape(CTileLandscape *landscape) { mNumLandscapes++; }
		int mNumLandscapes = 0;	///< Total landscapes visited
	};

	TEST_CLASS(CCityTest)
	{
	public:
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

		TEST_METHOD(TestCCityConstructor)
		{
            CCity city;
		}

        /** \brief Tests for the GetAdjacent function
         */
        TEST_METHOD(TestCCityAdjacent)
        {
            CCity city;
            int grid = CCity::GridSpacing;

            // Add a center tile to test
            auto center = make_shared<CTileRoad>(&city);
            center->SetLocation(grid * 10, grid * 17);
            city.Add(center);

            // Upper left
            auto ul = make_shared<CTileRoad>(&city);
            ul->SetLocation(grid * 8, grid * 16);
            city.Add(ul);
            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, -1, -1) == ul, L"Upper left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == nullptr, L"Upper right null test");

            // Upper right
            auto ur = make_shared<CTileRoad>(&city);
            ur->SetLocation(grid * 12, grid * 16);
            city.Add(ur);

            // Lower left
            auto ll = make_shared<CTileRoad>(&city);
            ll->SetLocation(grid * 8, grid * 18);
            city.Add(ll);

            // Lower right
            auto lr = make_shared<CTileRoad>(&city);
            lr->SetLocation(grid * 12, grid * 18);
            city.Add(lr);

            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == ur, L"Upper right test");
            Assert::IsTrue(city.GetAdjacent(center, -1, 1) == ll, L"Lower left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, 1) == lr, L"Lower right test");
        }

		/** \brief Tests for the city iterator function
		*/
		TEST_METHOD(TestCCityIterator)
		{
			// Construct a city object
			CCity city;

			// Add some tiles
			auto tile1 = make_shared<CTileRoad>(&city);
			auto tile2 = make_shared<CTileRoad>(&city);
			auto tile3 = make_shared<CTileRoad>(&city);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);

			// Does begin point to the first tile?
			auto iter1 = city.begin();
			auto iter2 = city.end();

			
			Assert::IsTrue(tile1 == *iter1, L"First item correct");
			++iter1;
			Assert::IsTrue(tile2 == *iter1, L"Second item correct");
			++iter1;
			Assert::IsTrue(tile3 == *iter1, L"Third item correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);
		}

		/** \brief Tests for the city zoning iterator function
		*/
		TEST_METHOD(TestCCityZoningIterator)
		{
			// Construct a city object
			CCity city;

			/*
			* Test on an empty city
			*/
			// Get the iterator support object
			auto itersupport = city.GetZoning(CTile::AGRICULTURAL);

			// Begin points to the first item
			auto iter1 = itersupport.begin();

			// End points after the last item
			auto iter2 = itersupport.end();

			Assert::IsFalse(iter1 != iter2);

			/*
			* Add some tiles and test
			*/
			auto tile1 = make_shared<CTileRoad>(&city);
			tile1->SetZoning(CTile::AGRICULTURAL);
			auto tile2 = make_shared<CTileRoad>(&city);
			tile2->SetZoning(CTile::INDUSTRIAL);
			auto tile3 = make_shared<CTileRoad>(&city);
			tile3->SetZoning(CTile::AGRICULTURAL);
			auto tile4 = make_shared<CTileRoad>(&city);
			tile4->SetZoning(CTile::NONE);
			auto tile5 = make_shared<CTileRoad>(&city);
			tile5->SetZoning(CTile::INDUSTRIAL);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);
			city.Add(tile4);
			city.Add(tile5);

			//
			// First test: AGRICULTURAL tiles
			//

			// Get the iterator support object
			itersupport = city.GetZoning(CTile::AGRICULTURAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsTrue(tile1 == *iter1, L"First agricultural correct");
			Assert::IsTrue(tile1 == *iter1, L"First agricultural still correct");
			++iter1;
			Assert::IsTrue(tile3 == *iter1, L"Second agricultural correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);

			//
			// Second test: INDUSTRIAL tiles
			//

			// Get the iterator support object
			itersupport = city.GetZoning(CTile::INDUSTRIAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsTrue(tile2 == *iter1, L"First industrial correct");
			++iter1;
			Assert::IsTrue(tile5 == *iter1, L"Second industrial correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);

			//
			// Third test: zoning with no results
			//
			// Get the iterator support object
			itersupport = city.GetZoning(CTile::RESIDENTIAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsFalse(iter1 != iter2);
		}

		/** \brief Tests for the city visitor function
		*/
		TEST_METHOD(TestCCityVisitor)
		{
			
			// Construct a city object
			CCity city;

			// Add some tiles of each time
			auto tile1 = make_shared<CTileRoad>(&city);
			auto tile2 = make_shared<CTileBuilding>(&city);
			auto tile3 = make_shared<CTileLandscape>(&city);
			auto tile4 = make_shared<CTileCoalmine>(&city);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);
			city.Add(tile4);

			//
			// All visit functions working
			//

			CTestVisitor visitor;
			city.Accept(&visitor);
			Assert::AreEqual(1, visitor.mNumRoads,
				L"Visitor number of roads");
			Assert::AreEqual(1, visitor.mNumBuildings,
				L"Visitor number of buildings");
			Assert::AreEqual(1, visitor.mNumCoalmines,
				L"Visitor number of coalmines");
			Assert::AreEqual(1, visitor.mNumLandscapes,
				L"Visitor number of landscapes");

			//
			// No visit functions being called on
			// an empty city
			//

			// If no visit function is called, then no increment
			// on any of the things in the class.

			CCity city2;

			CTestVisitor visitor2;
			city2.Accept(&visitor2);
			Assert::AreEqual(0, visitor2.mNumRoads,
				L"Visitor number of roads");
			Assert::AreEqual(0, visitor2.mNumBuildings,
				L"Visitor number of buildings");
			Assert::AreEqual(0, visitor2.mNumCoalmines,
				L"Visitor number of coalmines");
			Assert::AreEqual(0, visitor2.mNumLandscapes,
				L"Visitor number of landscapes");



		}
        
	};
}
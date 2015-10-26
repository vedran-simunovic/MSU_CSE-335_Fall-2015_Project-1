/**
* \file TileVisitor.h
*
* \author Vedran Simunovic, Nan Du, Helena Narowski
*
* Tile visitor base class.
*/


#pragma once
#include <memory>

// Forward references to all tile types
class CTileBuilding;
class CTileCoalmine;
class CTileLandscape;
class CTileRoad;
class CTileConstruction;
class CTileTransportation;
class CTilePower;
class CTileCar;
class CTileBank;
class CTileOremine;

/** Tile visitor base class */
class CTileVisitor
{
public:
	CTileVisitor();
	virtual ~CTileVisitor();

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building) {}

	/** Visit a CTileCoalmine object
	* \param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine) {}

	/** Visit a CTileOremine object
	* \param oremine Ore mine we are visiting */
	virtual void VisitOremine(CTileOremine *oremine) {}

	/** Visit a CTileLandscape object
	* \param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape) {}

	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitRoad(CTileRoad *road) {}

	/** Visit a CTileConstruction object
	* \param construction Construction we are visiting */
	virtual void VisitConstruction(CTileConstruction *construction) {}

	/** Visit a CTileTransportation object
	* \param trans we are visiting */
	virtual void VisitTrans(CTileTransportation *trans) {}

	/** Visit a CTileTransportation object
	* \param car we are visiting */
	virtual void VisitCar(CTileCar *car) {}

	/** Visit a CTilePower object
	* \param power we are visiting */
	virtual void VisitPower(CTilePower* power) {}

	/** Visit a CTileBank object
	* \param bank we are visiting */
	virtual void VisitBank(CTileBank *bank) {}



};
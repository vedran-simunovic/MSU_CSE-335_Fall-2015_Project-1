/**
 * \file MoveCar.h
 *
 * \author Helena Narowski
 *
 * 
 */

#pragma once

#include <utility>

#include "TileVisitor.h"
/**
 * 
 */
class CMoveCar :
	public CTileVisitor
{
public:
	CMoveCar();
	virtual ~CMoveCar();

	void VisitCar(CTileCar *car);
	void MoveVehicle();

	int GetKey() { return mKey; }
	void SetKey(int key) { mKey = key; }

	std::pair<int,int> GetCoordinates() { return mCoordinates; }

	void SetCoordinates(int x, int y) { mCoordinates = std::make_pair(x, y); }

private:
	int mKey = 0;
	std::pair<int, int> mCoordinates;

};


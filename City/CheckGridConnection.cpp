/**
 * \file CheckGridConnection.cpp
 *
 * \author Nan Du
 */

#include "stdafx.h"
#include "CheckGridConnection.h"
#include "TilePower.h"


CCheckGridConnection::CCheckGridConnection()
{
}


CCheckGridConnection::~CCheckGridConnection()
{
}


/**
 * visitor for set connection of power tile
 * \param power power tile we visited
 */
void CCheckGridConnection::VisitPower(CTilePower* power) 
{
	power->SetVisited(true);
	power->SetConnection(true);

}
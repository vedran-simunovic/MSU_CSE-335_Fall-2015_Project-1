/**
 * \file CheckGridConnection.cpp
 *
 * \author Helena Narowski
 */

#include "stdafx.h"
#include "CheckGridConnection.h"
#include "TilePower.h"


/**
 * 		  Constructor
 */
CCheckGridConnection::CCheckGridConnection()
{
}


/**
 * 		  Destructor
 */
CCheckGridConnection::~CCheckGridConnection()
{
}


/** Visits a power tile, sets its visited boolean and connection boolean
 * 
 * \param power 
 */
void CCheckGridConnection::VisitPower(CTilePower* power) 
{
	power->SetVisited(true);
	power->SetConnection(true);

}
#include "stdafx.h"
#include "CheckGridConnection.h"
#include "TilePower.h"


CCheckGridConnection::CCheckGridConnection()
{
}


CCheckGridConnection::~CCheckGridConnection()
{
}

void CCheckGridConnection::VisitPower(CTilePower* power) 
{
	power->SetVisited(true);
	power->SetConnection(true);

}
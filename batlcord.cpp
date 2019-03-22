// CBattleShipCoordinate - abstract game board class
//

#include "BatlCord.hpp"
#include "Battle.h"

/////////////////////////////////////////////////////////////////////////////
// CBattleShipCoordinate

CBattleShipCoordinate::CBattleShipCoordinate()
{
   // start out with nothing on them
   m_bIsOccupied = false;
   m_CoordWidth  = COORDWIDTH;
   m_CoordHeight = COORDHEIGHT;

}

CBattleShipCoordinate::~CBattleShipCoordinate()
{
}

void CBattleShipCoordinate::Initialize()
{
}

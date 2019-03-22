// CBattleShipGamePiece - Battle Ship Game Piece
//

#include "Battlegp.hpp"
#include "Battle.h"

/////////////////////////////////////////////////////////////////////////////
// CBattleShipGamePiece

CBattleShipGamePiece::CBattleShipGamePiece()
{
   m_bSunk = false;
}

CBattleShipGamePiece::~CBattleShipGamePiece()
{
}

CBattleShipGamePiece* CBattleShipGamePiece::Hit(IPoint point)
{
   return NULL;
}

void CBattleShipGamePiece::Initialize()
{
}

Boolean CBattleShipGamePiece::IsShipSunk()
{
   // should not call this function for anything other
   // than a ship!
   if (m_nShipType > ePTBOAT)
      return (false);
      
   return (m_bSunk);
}
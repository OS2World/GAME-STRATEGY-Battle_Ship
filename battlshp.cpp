// CBattleShipGamePiece - Battle Ship Game Piece
//

#include "Battlshp.hpp"

/////////////////////////////////////////////////////////////////////////////
// CBattleShipGamePiece

CBattleShip::CBattleShip( CBattleShipGame* pGame,
                          Sound* pSound,
                          unsigned long id,
                          IWindow* parent,
                          unsigned long bitmapId,
                          const IRectangle& initial)
         : CWndBattleShipGamePiece(pGame,
                                   pSound,
                                   id, 
                                   parent, 
                                   bitmapId, 
                                   initial)
{
   m_nLength = 5;
   m_nShipType = eBATTLESHIP;    
   m_csShipName = "BATTLE";
   
   m_nHorizontalShipNumber = HBATTLE;
}

CBattleShip::~CBattleShip()
{
}

void CBattleShip::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}


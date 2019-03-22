// CSubmarine - Submarine Game Piece
//

#include "Sub.hpp"

/////////////////////////////////////////////////////////////////////////////
// CSubmarine constructor

CSubmarine::CSubmarine( CBattleShipGame* pGame,
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
   //Save some info particular to this ship
   m_nLength = 4;
   m_nShipType = eSUBMARINE;
   m_csShipName = "SUB";

   m_nHorizontalShipNumber = HSUB;
}


// CSubmarine destructor
CSubmarine::~CSubmarine()
{
}

void CSubmarine::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}


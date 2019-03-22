// CDestroyer - Destroyer Game Piece
//

#include "Destroy.hpp"

/////////////////////////////////////////////////////////////////////////////
// CDestroyer

CDestroyer::CDestroyer( CBattleShipGame* pGame,
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
   m_nLength = 3;
   m_nShipType = eDESTROYER;
   m_csShipName = "DESTROY";

   m_nHorizontalShipNumber = HDESTROY;
}

CDestroyer::~CDestroyer()
{
}

void CDestroyer::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}


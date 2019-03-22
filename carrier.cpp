// CCarrier - Carrier Game Piece
//

#include "carrier.hpp"

/////////////////////////////////////////////////////////////////////////////
// CCarrier

CCarrier::CCarrier( CBattleShipGame* pGame,
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
   m_nLength = 4;
   m_nShipType = eCARRIER;
   m_csShipName = "CARRIER";

   m_nHorizontalShipNumber = HCARRIER;
}

CCarrier::~CCarrier()
{
}

void CCarrier::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}


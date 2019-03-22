// CPTBoat - PTBoat Game Piece
//

#include "PTBoat.hpp"

/////////////////////////////////////////////////////////////////////////////
// CPTBoat

CPTBoat::CPTBoat( CBattleShipGame* pGame,
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
   m_nLength = 2;
   m_nShipType = ePTBOAT;
   m_csShipName = "PTBOAT";

   m_nHorizontalShipNumber = HPTBOAT;
}

CPTBoat::~CPTBoat()
{
}

void CPTBoat::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}


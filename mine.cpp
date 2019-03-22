// CMine - Mine Game Piece
//

#include "mine.hpp"

/////////////////////////////////////////////////////////////////////////////
// CMine

CMine::CMine(CBattleShipGame* pGame,
             Sound* pSound,
             unsigned long id,
             IWindow* parent,
             unsigned long bitmapId,
             const IRectangle& initial,
             const Boolean& bVisible)
         : CWndBattleShipGamePiece(pGame,
                                   pSound,
                                   id, 
                                   parent, 
                                   bitmapId, 
                                   initial)
{
   m_nLength = 1;
   m_nShipType = MINE;
   m_csShipName = "MINE";
   m_bWasDetonated = false;

   setBitmap(MINE);
   moveSizeTo(initial);

   if ( bVisible ) 
   {
      show(true);
      refresh();
   }
}

CMine::~CMine()
{
}
                                                       
void CMine::Initialize()
{
   m_nOpenTargets = m_nLength;

   CWndBattleShipGamePiece::Initialize();
}

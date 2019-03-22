// CMine - The actual Mine game piece
//
#ifndef __MINE_H__
#define __MINE_H__

#include "w_batgp.hpp"
#include "battle.h"

//class CWndBattleShipBoard;

class CMine : public CWndBattleShipGamePiece
{
// Implementation
public:
   CMine(CBattleShipGame* pGame,
         Sound* pSound,
         unsigned long id,
         IWindow* parent,
         unsigned long bitmapId,
         const IRectangle& initial = IRectangle(IPoint(0,0),ISize(COORDWIDTH,COORDHEIGHT)),
         const Boolean& bVisible = true);
   ~CMine();

// Attributes
private:
   Boolean  m_bWasDetonated;

// Operations
public:
   void     Initialize();
   void     SetDetonated() { m_bWasDetonated = true; }
   Boolean  WasDetonated() { return m_bWasDetonated; }

};
#endif


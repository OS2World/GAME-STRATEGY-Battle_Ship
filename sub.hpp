// CSubmarine - The actual Submarine game piece
//
#ifndef __SUBMARINE_H__
#define __SUBMARINE_H__

#include "battle.h"
#include "w_batgp.hpp"

//class CWndBattleShipBoard;

class CSubmarine : public CWndBattleShipGamePiece
{
// Implementation
public:
   CSubmarine(CBattleShipGame* pGame,
              Sound* pSound,
              unsigned long id,
              IWindow* parent,
              unsigned long bitmapId,
              const IRectangle& initial = IRectangle(IPoint(0,0),ISize(80, 20)));
   ~CSubmarine();

// Attributes
private:

// Operations
public:
   void Initialize();
//   int GetShipType() { return m_nShipType; }
};
#endif

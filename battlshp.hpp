// CBattleShip - The actual BattleShip Ship game piece
//
#ifndef __BATTLESHIP_H__
#define __BATTLESHIP_H__

#include "battle.h"
#include "w_batgp.hpp"

class CWndBattleShipGamePiece;

class CBattleShip : public CWndBattleShipGamePiece
{
// Implementation
public:
   CBattleShip(CBattleShipGame* pGame,
               Sound* pSound,
               unsigned long id,
               IWindow* parent,
               unsigned long bitmapId,
               const IRectangle& initial = IRectangle(IPoint(0,0),ISize(100, 20)));
   ~CBattleShip();

// Attributes
private:

// Operations
public:
//   int GetShipType() { return m_nShipType; }
   void Initialize();
};
#endif

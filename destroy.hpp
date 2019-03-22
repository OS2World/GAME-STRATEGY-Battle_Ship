// CDestroyer - The actual Destroyer game piece
//
#ifndef __DESTROYER_H__
#define __DESTROYER_H__

#include "battle.h"
#include "w_batgp.hpp"

//class CWndBattleShipBoard; //forward declaration so the constructor compiles

class CDestroyer : public CWndBattleShipGamePiece
{
// Implementation
public:

   CDestroyer(CBattleShipGame* pGame,
              Sound* pSound,
              unsigned long id,
              IWindow* parent,
              unsigned long bitmapId,
              const IRectangle& initial = IRectangle(IPoint(0,0),ISize(60, 20)));
   ~CDestroyer();

// Attributes
private:
   
// Operations
public:
   void Initialize();
//   int GetShipType() { return m_nShipType; }
};
#endif

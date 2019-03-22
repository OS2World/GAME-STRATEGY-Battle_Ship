// CPTBoat - The actual PTBoat game piece
//
#ifndef __PTBoat_H__
#define __PTBoat_H__

#include "battle.h"
#include "w_batgp.hpp"

//class CWndBattleShipBoard; //forward declaration so the constructor compiles

class CPTBoat : public CWndBattleShipGamePiece
{
// Implementation
public:
   CPTBoat(CBattleShipGame* pGame,
           Sound* pSound,
           unsigned long id,
           IWindow* parent,
           unsigned long bitmapId,
           const IRectangle& initial = IRectangle(IPoint(0,0),ISize(40, 20)));
   ~CPTBoat();

// Attributes
private:

// Operations
public:
   void Initialize();
//   int GetShipType() { return m_nShipType; }
};
#endif

// CCarrier - The actual Carrier game piece
//
#ifndef __CARRIER_H__
#define __CARRIER_H__

#include "w_batgp.hpp"
#include "battle.h"

//class CWndBattleShipBoard;

class CCarrier : public CWndBattleShipGamePiece
{
// Implementation
public:
   CCarrier(CBattleShipGame* pGame,
            Sound* pSound,
            unsigned long id,
            IWindow* parent,
            unsigned long bitmapId,
            const IRectangle& initial = IRectangle(IPoint(0,0),ISize(80, 20)));
   ~CCarrier();

// Attributes
private:

// Operations
public:
   void Initialize();
//   int GetShipType() { return m_nShipType; }
};
#endif

// CWndBattleShipGamePiece - windows abstraction of BattleShip Game Piece.
//

#ifndef __WNDBATTLEGAMEPIECE_H__
#define __WNDBATTLEGAMEPIECE_H__

class    CBattleShipGame;

#include "battlegp.hpp"
#include "sound.hpp"   

#include <assert.h>
#include <ibmpctl.hpp>

class CWndBattleShipGamePiece : public CBattleShipGamePiece, 
                                public IBitmapControl
{
// Implementation
public:
   CWndBattleShipGamePiece(CBattleShipGame* pGame,
                           Sound* pSound,
                           unsigned long id,
                           IWindow* parent,
                           unsigned long bitmapId,
                           const IRectangle& initial);
   ~CWndBattleShipGamePiece();
   
// Attributes
protected:
   CBattleShipGame*  m_pGame;
   Sound*            m_pSound;


// Operations
public:
   void Initialize();
   CWndBattleShipGamePiece* Hit(IPoint point, int);
};
#endif 

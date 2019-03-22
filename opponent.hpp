// COpponent - abstract board game class
//
#ifndef __OPPONENT_H__
#define __OPPONENT_H__

#include "stack.hpp"
#include "batshpgm.hpp"

class CBattleShipGame;        //Forward declarations

class COpponent
{
// Implementation
public:
   COpponent(CBattleShipGame* pGame=NULL);
   ~COpponent();

// Attributes
private:
   CBattleShipGame*  m_pGame;
   Boolean           m_vertical;
   Boolean           m_horizontal;   

   stack             *m_GuessStack;
   stack             *m_HitStack;
 
// Operations
protected:
   Boolean  SmartShot(); 
   Boolean  isCoordAvailable(int nWhere, IPoint* cPt);
   void     VerticalSmartShot(IPoint cpoint);
   void     HorizontalSmartShot(IPoint cpoint);
   
public:
   IPoint      TakeShot();
   IPoint      ChooseRandomCoord();
   UCHAR       ChooseRandomCoord(UCHAR ucValid);
   void        PlaceShips();
   void        PlaceMines();
   void        Initialize(); 
   void        PushHit(IPoint cpoint) { m_HitStack->push(cpoint); }
   void        ClearHitStack();
};
#endif



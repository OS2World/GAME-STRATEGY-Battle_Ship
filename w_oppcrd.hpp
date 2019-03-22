// CWndBattleShipOpponentCoordinate - Graphical BattleShip coordinate
//
#ifndef __WOPPONENTCOORD_H__
#define __WOPPONENTCOORD_H__

#include "sound.hpp"   

class CWndOpponentBoard;

class CWndOpponentCoordinate :  public IMouseHandler,
                                public IBitmapControl,
                                public IPaintHandler,
                                public CBattleShipCoordinate 
{
public:
// Implementation
   CWndOpponentCoordinate(CWndOpponentBoard* pParent, 
                          IPoint& cPnt, 
                          CBattleShipGame* cGame,
                          Sound* pSound,
                          unsigned long id,
                          unsigned long bitmapId,
                          const IRectangle& initial);
   ~CWndOpponentCoordinate();

protected:
   virtual Boolean 
      paintWindow(IPaintEvent &event),
      mouseClicked(IMouseClickEvent &event);

   Boolean  Mine();
   void     Hit();   //dsb
   void     Miss();  //dsb
   void     button1Down();

private:
   CWndOpponentBoard* m_pParent;

      
// Operations
public:
   void     Initialize();
   CWndOpponentBoard* GetParentWindow() { return m_pParent; }
   void SetShipOnCoordinate(CWndBattleShipGamePiece* pShip)
                   { m_pBattleShipGamePiece = pShip;
                     if (pShip) SetOccupied(TRUE);
                     else SetOccupied(FALSE); }       
};
#endif


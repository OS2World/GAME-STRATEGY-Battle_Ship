// CWndPlayerCoordinate - Graphical BattleShip coordinate
//
#ifndef __WBATTLECOORD_H__
#define __WBATTLECOORD_H__

#include "batlcord.hpp"
#include "sound.hpp"   

#include  <ipainhdr.hpp>         /* IPaintHandler               */
#include  <ipainevt.hpp>         /* IPaintEvent                 */
#include  <imchdr.hpp>           /* Mouse commands              */
#include  <imoushdr.hpp>
#include  <imousevt.hpp>
#include  "ammvehdr.hpp"

class CWndPlayerBoard;
                     
class CWndPlayerCoordinate :  public IMouseHandler,
                              public IBitmapControl,
                              public IPaintHandler,
                              public CBattleShipCoordinate 
{                             
public:
// Implementation
   CWndPlayerCoordinate(CWndPlayerBoard* pParent, 
                        IPoint& cPnt, 
                        CBattleShipGame* cGame,
                        Sound* pSound,
                        unsigned long id,
                        unsigned long bitmapId,
                        const IRectangle& initial);
   ~CWndPlayerCoordinate();

protected:
   virtual Boolean 
      paintWindow(IPaintEvent &event),
      mouseClicked(IMouseClickEvent &event);

   Boolean  Hit(); 
   void     Miss();
   void     button1Down();

   Boolean  Mine();
   void     DisplayDirectionals();

private:
   CWndPlayerBoard*           m_pParent;
   static Boolean             m_bDirSelect;     // utility flag for selecting direction

// Operations
public:
   void             Initialize();
   CWndPlayerBoard* GetParentWindow() { return m_pParent; }
   Boolean          FireOn();
   void             SetShipOnCoordinate(CWndBattleShipGamePiece* pShip);
};
#endif


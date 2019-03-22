// CBattleShipBoard - abstract game board class
//

#ifndef __WNDBATTLEBOARD_H__
#define __WNDBATTLEBOARD_H__

class CWndBattleShipBoard;

#include <icanvas.hpp>
#include <ibag.h>

#include "battlbrd.hpp"
#include "w_placrd.hpp"
//#include "mine.hpp"   

typedef CMine* MineObject;
typedef IBag <MineObject> MineCollectionType;


class CWndBattleShipBoard :   public CBattleShipBoard, 
                              public ICanvas
{
// Implementation
public:
   CWndBattleShipBoard(CBattleShipGame* pGame, 
                        unsigned long id,
                        IWindow* parent);
   ~CWndBattleShipBoard();
   
protected:
   CWndPlayerCoordinate*      m_pRightNeighbor;
   CWndPlayerCoordinate*      m_pLeftNeighbor;
   CWndPlayerCoordinate*      m_pUpNeighbor;
   CWndPlayerCoordinate*      m_pDownNeighbor;
   CWndBattleShipGamePiece*   m_pShipBeingPlaced;

   //Holds the array of mines for the game
   MineCollectionType         m_MineArray;

   Boolean                    m_bPenalty;
   int                        m_nMinesLeft;
   int                        m_iBitmapWidth, m_iBitmapHeight;
   int                        m_ixStartingPoint, m_iyStartingPoint;

   Sound*                     m_pSound;

public:
   virtual void Initialize();
   CWndBattleShipGamePiece* GetShipBeingPlaced() { return m_pShipBeingPlaced; }
   CMine* CreateNewMine(IPoint pPoint, Boolean bVisible);
 
   Boolean GetPenalty() { return m_bPenalty; }
   Boolean IsValidCoordinate(CBattleShipCoordinate* pCoord);
   Boolean CheckForPenalty();

   void    SetShipBeingPlaced(CWndBattleShipGamePiece* pShip) { m_pShipBeingPlaced = pShip; }
   void    SetMinesLeft(int nLeft) { m_nMinesLeft = nLeft; }
   void    SetPenalty(Boolean bPenalty) { m_bPenalty = bPenalty; }
   void    HitMine(int);

protected:
   void CreateShips();   
   void DeleteShips();   
   void DeleteMines(); 
   void HideMines(); 
};
#endif 

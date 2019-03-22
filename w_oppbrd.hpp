// CWndOpponentBoard - Computer player's Battleship game board: graphical component
//
#ifndef __WOPPONENTBOARD_H__
#define __WOPPONENTBOARD_H__ 

class CWndOpponentCoordinate;
#include "w_batbrd.hpp"
#include "w_oppcrd.hpp"
#include "stack.hpp"

   
class CWndOpponentBoard : public CWndBattleShipBoard
{
// Implementation
public:
   CWndOpponentBoard(CBattleShipGame* CGame, 
                     unsigned long id, 
                     IWindow* parent);
   ~CWndOpponentBoard();

// Attributes
private:
   CWndOpponentCoordinate*     pCoordinate;
   CWndOpponentCoordinate*     m_CoordinateArray[100];

   CBattleShipGame*        m_Game;
   CWndOpponentCoordinate* m_pAnchorCoordinate;
   CWndOpponentCoordinate* m_pRightNeighbor;
   CWndOpponentCoordinate* m_pLeftNeighbor;
   CWndOpponentCoordinate* m_pUpNeighbor;
   CWndOpponentCoordinate* m_pDownNeighbor;
   stack                   m_GuessStack;     //so you cannot choose the same coord more than once //dsb
   stack                   m_HitStack;       //to track your hits (smart opponent) //dsb


// Operations
public:
   void Initialize();

   Boolean  SetShipOnBoard(UCHAR ucChosenDirection);
   UCHAR FitShipOnBoard(CWndOpponentCoordinate* pCoord);
   Boolean  IsAnchorCoord(CWndOpponentCoordinate* pCoord) { return (pCoord == m_pAnchorCoordinate); }
   CWndOpponentCoordinate* GetChosenCoordinate(IPoint*);
   Boolean isAlreadyGuessed(IPoint);                         
   Boolean isAlreadyHit(IPoint);                            
   void pushGuess(IPoint iPoint) {m_GuessStack.push(iPoint);}
   void pushHit(IPoint iPoint) {m_HitStack.push(iPoint);}    
   
private:

   Boolean DoesShipFit(int nWhere);
   CBattleShipCoordinate* GetNeighbor(CWndOpponentCoordinate* pCoord, int nWhere);
   int  GetCoordinateIndex(CWndOpponentCoordinate* pCoord, int nWhere=0);
   int  GetCoordinateIndex(IPoint* pIPoint) { return( (pIPoint->y()*10) + pIPoint->x() ); }
   Boolean IsObstruction(CWndOpponentCoordinate* pCoord, int nWhere);
};
#endif

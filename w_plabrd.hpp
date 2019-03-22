// cWndPlayerBoard - Human player's Battleship game board: graphical component
//
#ifndef __WPLAYERBOARD_H__
#define __WPLAYERBOARD_H__

class CWndPlayerBoard;

#include "w_batbrd.hpp"
#include "w_placrd.hpp"

class CWndPlayerBoard : public CWndBattleShipBoard
{
// Implementation
public:
   CWndPlayerBoard(  CBattleShipGame* CGame, 
                     unsigned long id, 
                     IWindow* parent);
  ~CWndPlayerBoard();

// Attributes
private:
   CWndPlayerCoordinate*     pCoordinate;
   CWndPlayerCoordinate*     m_CoordinateArray[100];
   CWndPlayerCoordinate*     m_pAnchorCoordinate;
      
// Operations
public:
   Boolean  SetShipOnBoard(CWndPlayerCoordinate* pCoord);
   Boolean  IsAnchorCoord(CWndPlayerCoordinate* pCoord) { return (pCoord == m_pAnchorCoordinate); }
   Boolean  FireOn(IPoint ipoint);

   void Initialize();
   void FitShipOnBoard(CWndPlayerCoordinate* pCoord);
   void HideGamePieces();
   void SinkShip();

private:
   Boolean DoesShipFit(int nWhere);
   Boolean IsObstruction(CWndPlayerCoordinate* pCoord, int nWhere);

   CBattleShipCoordinate* GetNeighbor(CWndPlayerCoordinate* pCoord, int nWhere);
   int GetCoordinateIndex(CWndPlayerCoordinate* pCoord, int nWhere=0);
};
#endif

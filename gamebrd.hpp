// CGameBoard - abstract game board class
//
#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

class CGameBoard
{
// Implementation
public:
   CGameBoard();
   ~CGameBoard();

// Attributes
public:

// Operations
public:
   virtual void Initialize() = 0;
};
#endif

// CBattleShipBoard - abstract game board class
//

#ifndef __BATTLEBOARD_H__
#define __BATTLEBOARD_H__

class CBattleShipBoard;       //Forward declarations

#include "batshpgm.hpp"
//#include "gamebrd.hpp"
#include "ships.hpp"

#define HERE   0x00
#define RIGHT  0x01
#define LEFT   0x02
#define UP     0x04     
#define DOWN   0x08

class CBattleShipBoard : public CGameBoard
{
// Implementation
public:
   CBattleShipBoard(CBattleShipGame* m_pGame);
   ~CBattleShipBoard();
   
// Attributes
protected:
   CBattleShipGame*  m_pGame;
   CBattleShip*      m_BattleShip;  
   CCarrier*         m_Carrier;
   CPTBoat*          m_PTBoat;
   CDestroyer*       m_Destroyer;
   CSubmarine*       m_Submarine;
   int               m_nNumShipsLeftToSink;

// Operations
public:
   virtual void Initialize() = 0;

   // get private ship members
   CCarrier* GetCarrier() { return m_Carrier; }
   CBattleShip* GetBattleShip() { return m_BattleShip; }
   CDestroyer* GetDestroyer() { return m_Destroyer; }
   CSubmarine* GetSubmarine() { return m_Submarine; }
   CPTBoat* GetPTBoat() { return m_PTBoat; }
   int GetNumberShipsLeftToSink() { return m_nNumShipsLeftToSink; }
   void SetNumberShipsLeftToSink() { m_nNumShipsLeftToSink--; }

protected:
   Boolean DoesShipFit(int nWhere);

};
#endif 

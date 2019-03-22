// CBattleShipCoordinate - Specific BattleShip coordinate
//
#ifndef __BATTLECOORD_H__
#define __BATTLECOORD_H__
                    
class CBattleShipGame;
class CBattleShipGamePiece;

#include <iwindow.hpp>
#include "gamecord.hpp"
#include "w_batgp.hpp"
#include "sound.hpp"

class CBattleShipCoordinate : public CGameCoordinate
{
// Implementation
public:
   CBattleShipCoordinate();
   ~CBattleShipCoordinate();

// Attributes
protected:
   CBattleShipGame*           m_pGame;
   IPoint                     m_cPoint;
   Boolean                    m_bIsOccupied;
   int                        m_CoordWidth;
   int                        m_CoordHeight;
   CWndBattleShipGamePiece*   m_pBattleShipGamePiece;
   Sound*                     m_sound;

   void     Miss();  //dsb
   void     button1Down();
   
// Operations
public:
   void Initialize();

   int GetWidth()     const { return m_CoordWidth; }
   int GetHeight()    const { return m_CoordHeight; }
   IPoint             GetPoint() { return m_cPoint;}
   Boolean            IsOccupied() { return m_bIsOccupied; }
   void               SetOccupied(Boolean bOccupied) 
                                 { m_bIsOccupied = bOccupied; }
};
#endif

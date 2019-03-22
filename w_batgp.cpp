// CWndBattleShipGamePiece - windows abstraction of BattleShip Game Piece.
//

#include "batshpgm.hpp"
#include "battle.h"


/**************************************************************
* Constructor
**************************************************************/
CWndBattleShipGamePiece::CWndBattleShipGamePiece(CBattleShipGame* pGame,
                                                 Sound* pSound,
                                                 unsigned long id,
                                                 IWindow* parent,
                                                 unsigned long bitmapId,
                                                 const IRectangle& initial)
                        : IBitmapControl( id, parent, parent, 
                                          bitmapId, initial)
{
   m_pGame  = pGame;
   m_pSound = pSound;
   show(false);
}

/**************************************************************
* Destructor
**************************************************************/
CWndBattleShipGamePiece::~CWndBattleShipGamePiece()
{
}
 
void CWndBattleShipGamePiece::Initialize()
{
   show(false);
   m_bSunk = false;
}

/****************************************************************
* Function:    CWndBattleShipGamePiece
*
* Purpose      Will decrement the number of open targets on the game
*              piece that was hit.  It will play the sound appropriate 
*              for the board that contain the game piece.  If the ship is
*              sunk,  it will display the ship and bring up a messagebox
*              about who sunk which ship.
*              
*
* Returns      NULL - If a ship was sunk or the gamepiece was a mine
*              Pointer to this game piece - otherwise
****************************************************************/
CWndBattleShipGamePiece* CWndBattleShipGamePiece::Hit(IPoint point, int a_caller)
{

   //We do not want to sink mines or decrement open target counts 
   // for mines
   if (m_nShipType == MINE)
   { 
      m_pSound->playSound("mine.wav"); 
      return NULL;
   }

   if (m_bSunk)
      return NULL;
        
   assert(m_nOpenTargets > 0);
   m_nOpenTargets -= 1;

   if ( m_pGame->GetSound() ) 
   {
      switch (a_caller)
      {
       case PLAYERBOARD:
         m_pSound->playSound("xplode1.wav"); 
         break;
      
       case OPPONENTBOARD:
         m_pSound->playSound("explosio.wav"); 
         break;
      }
   }

   // check for sink
   if (m_nOpenTargets == 0)
   {

      m_bSunk = true;
      show(true);
      refresh();

      // build sink message (note: the names stored in the objects serve
      // double duty as bitmap file names; because of 8.3, we have to 
      // 'fixup' BATTLESHIP and DESTROYER
      IString csMsg;
      switch (a_caller)
      {
       case PLAYERBOARD:
         csMsg = "Your opponent sank your ";
         break;
      
       case OPPONENTBOARD:
         csMsg = "You sank your opponents ";
         break;
      }

      IString csName = this->GetShipName();
      if (csName.includes( "BATTLE" ))
         csMsg += "BATTLESHIP";
      else
      if (csName.includes( "DESTROY" ))
            csMsg += "DESTROYER";
         else
            csMsg += csName;
          
      csMsg += " !";
      m_pGame->SetInfoareaMessage(csMsg);

      //Turn the sound on if configured that way
      if ( m_pGame->GetSound() ) 
         m_pSound->playSound("bubbles.wav"); 
   }

   return this;
}


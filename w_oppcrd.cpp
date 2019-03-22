/****************************************************************
* CWndOpponentCoordinate - Graphical BattleShip coordinate
*
*
* This is the "game square" of the battle ship game.  
****************************************************************/

#include "battle.h"
#include "batshpgm.hpp"
//#include "w_oppCrd.hpp"
//#include "gamepiec.hpp"

class CWndOpponentBoard;
                     

// CBattleShipCoordinate Constructor
CWndOpponentCoordinate::CWndOpponentCoordinate(CWndOpponentBoard* pParent, 
                        IPoint& cPnt, 
                        CBattleShipGame* cGame,
                        Sound* pSound,
                        unsigned long id,
                        unsigned long bitmapId,
                        const IRectangle& initial)
         : IBitmapControl(id, pParent, pParent, bitmapId, initial)
{
   m_pParent = pParent;                // Pointer to the board
   m_cPoint = cPnt;                    // This is the row and column of this coord
   m_pGame = cGame;                    // Save a pointer to the game itself
   m_pBattleShipGamePiece = NULL;      // To start, there are no game pieces on this coord
   
   /******************************************************************
   * Add the handlers to this window
   ******************************************************************/
   ((IMouseHandler*)this)->handleEventsFor(this);
   ((IPaintHandler*)this)->handleEventsFor(this);
   ((AMouseMoveHandler*)this)->handleEventsFor(this);

   //save a pointer to the sound class
   m_sound = pSound;
}


CWndOpponentCoordinate::~CWndOpponentCoordinate()
{
}

/****************************************************************
* Function:    Initialize
*
* Purpose      Set the coordinate back to its initial state
* Returns      Nothing
****************************************************************/
void CWndOpponentCoordinate::Initialize()
{
   setBitmap(BLANK);
         
   // reset known stuff
   if (m_pBattleShipGamePiece)
      m_pBattleShipGamePiece = NULL;

   //This tells the coordinate that there is no game piece occupying it.
   SetShipOnCoordinate(NULL);

   m_bIsOccupied = FALSE;
}

/****************************************************************
* Function: button1Down
* Parms:    none
* 
* Purpose      This occurs on the left mouse button press.  If we 
*           are in ship placement mode,  we need to display the
*           selection buttons.  Otherwise,  we need to determine
*           if a ship is on our 'square'.  If so,  call its hit
*           function.  Otherwise,  show a miss square.
*
* Returns      nothing
****************************************************************/
void CWndOpponentCoordinate::button1Down()
{
   // if at any time player ended game, return
   if (m_pGame->GetGameOver()) 
      return;

   // If we are placing ships then load the select bitmap button, 
   // else call the "hit" member function.
   int nGameMode = m_pGame->GetGameMode();
   switch(nGameMode)
      {               
      case PREGAME:
         break;
         
      case SETUPGAME:   // already done
         break;
   
      case PLAYGAME:    // must be firing at this point
          if(m_pParent->isAlreadyGuessed(m_cPoint)) // have we guessed this one yet?
          {
             DosBeep(BEEPFREQ, BEEPDURATION);  //if already guessed,  beep and get out!
             return;                          // do not want to Invalidate to show wrong bitmap
          }

          //Tell the parent board to save the guess in its stack
          m_pParent->pushGuess( m_cPoint );         //dsb
         
         //if there there is a game piece here,  call the hit function         
         if(m_pBattleShipGamePiece)
            Hit();       
         else    
         {
            Miss();     
            refresh();
         }

         //Call the game to decide whether to switch turns or give me another
         //  turn based on a penalty.
         m_pGame->DecidePlayerTurn(OPPONENTBOARD);

         break;

      default:
         break;
      }
}


/****************************************************************
* Function:    Miss
*
* Purpose      Handles the actions when a Miss is registered
* Returns      Nothing
****************************************************************/
void CWndOpponentCoordinate::Miss()       //dsb
{     
   setBitmap(WATER);  //must be a miss
   refresh();         //make the bitmap show!
   return;
}

Boolean CWndOpponentCoordinate::paintWindow(IPaintEvent &)
{
   Boolean stopProcessingEvent = false;

   return stopProcessingEvent;
}


/*****************************************************************************
* Function: mouseClicked
* Parms:    event - info about which mouse button was pressed
* Purpose:  Process the mouse messages generated from the square
* Returns:  false - so someone else can process the message
*****************************************************************************/
Boolean CWndOpponentCoordinate::mouseClicked(IMouseClickEvent &event)
{
  if ( event.mouseButton() == IMouseClickEvent::button1 &&
       event.mouseAction() == IMouseClickEvent::down )
  {
    button1Down();
  }
  else if ( event.mouseButton() == IMouseClickEvent::button1 &&
            event.mouseAction() == IMouseClickEvent::up )
  {
//    button1Up();
  }
  else if ( event.mouseButton() == IMouseClickEvent::button2 &&
            event.mouseAction() == IMouseClickEvent::down )
  {
//    button2Down();
  }
  return false;         // Allow someone else to also process.
}


/****************************************************************
* Function:    Hit
*
* Purpose      Handles the actions when a hit is registered
* Returns      Nothing
****************************************************************/
void CWndOpponentCoordinate::Hit()       //dsb
{
   //Call the hit function for the particular game piece that was on this
   //  coordinate.      
   m_pBattleShipGamePiece->Hit(m_cPoint, OPPONENTBOARD);

   // handle a mine
   if (m_pBattleShipGamePiece->GetShipType() == MINE)
   {
      Mine();
      return;
   }

   //If the piece is now sunk, the game may be over.
   if (m_pBattleShipGamePiece->IsShipSunk())
   {
      // decrement the number of ships on the board
      m_pParent->SetNumberShipsLeftToSink();

      //End the game if there are no more game pieces to sink
      if (m_pParent->GetNumberShipsLeftToSink() == 0)
         m_pGame->SetGameOver(OPPONENTBOARD);
   }
   else
   {
      setBitmap(HITMARK);
      refresh();       //make the bitmap show!
   }

}

/****************************************************************
* Function:    Mine
*
* Purpose      Handles the actions when a mine is registered
* Returns      Nothing
****************************************************************/
Boolean CWndOpponentCoordinate::Mine()
{  
   setBitmap(MINE);
   show(true);
   refresh();

   //We let the board handle the mines.  This will display a message that a 
   // mine was hit and register a penalty with the respective board.
   m_pParent->HitMine(OPPONENTBOARD);
   
   return false;
}

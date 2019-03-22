/****************************************************************
* CWndPlayerCoordinate - Graphical BattleShip coordinate
*
*
* This is the "game square" of the battle ship game.  
****************************************************************/

#include "battle.h"
#include "batshpgm.hpp"
#include <bsedos.h>

Boolean CWndPlayerCoordinate::m_bDirSelect = false;

/////////////////////////////////////////////////////////////////////////////
// CPlayerCoordinate Constructor

CWndPlayerCoordinate::CWndPlayerCoordinate(CWndPlayerBoard* pParent, 
                        IPoint& cPnt, 
                        CBattleShipGame* pGame,
                        Sound* pSound,
                        unsigned long id,
                        unsigned long bitmapId,
                        const IRectangle& initial)
         : IBitmapControl(id, pParent, pParent, bitmapId, initial)
{
   m_pParent = pParent;               // Pointer to the board
   m_cPoint = cPnt;                   // This is the row and column of this coord
   m_pGame = pGame;                   // Save a pointer to the game itself
   m_pBattleShipGamePiece = NULL;     // To start, there are no game pieces on this coord

   /******************************************************************
   * Add the handlers to this window
   ******************************************************************/
   ((IMouseHandler*)this)->handleEventsFor(this);
   ((IPaintHandler*)this)->handleEventsFor(this);
   ((AMouseMoveHandler*)this)->handleEventsFor(this);

   //save a pointer to some sound
   m_sound = pSound;
}

CWndPlayerCoordinate::~CWndPlayerCoordinate()
{
}

/****************************************************************
* Function:    Initialize
*
* Purpose      Set the coordinate back to its initial state
* Returns      Nothing
****************************************************************/
void CWndPlayerCoordinate::Initialize()
{
   m_bDirSelect = false;

   //set the bitmap back to its original image
   setBitmap(BLANK);

   // reset known stuff
   if (m_pBattleShipGamePiece)
      m_pBattleShipGamePiece = NULL;

   //This tells the coordinate that there is no game piece occupying it.
   this->SetShipOnCoordinate(NULL);
   m_bIsOccupied = false;
}



/****************************************************************
* Function:    SetShipOnCoordinate
*
* Purpose      Sets a boolean indicating whether a gamepiece is
*              occupying this coordinate or not.  It also save a
*              pointer to that game piece.
*
* Returns      Nothing
****************************************************************/
void CWndPlayerCoordinate::SetShipOnCoordinate(CWndBattleShipGamePiece* pGamePiece)
{
   //save a pointer to the game piece on this coordinate.
   m_pBattleShipGamePiece = pGamePiece;
   
   if (pGamePiece) 
      SetOccupied(true);
   else 
      SetOccupied(false);
}


/****************************************************************
* Function:    Miss
*
* Purpose      Handles the actions when a Miss is registered
* Returns      Nothing
****************************************************************/
void CWndPlayerCoordinate::Miss() 
{  
   DosBeep(BEEPFREQ, BEEPDURATION);
   DosSleep(500);      // Go to sleep for .5 second to give the 
                       // sound a chance to finish
   setBitmap(WATER);
   show(true);
   refresh();
}


Boolean CWndPlayerCoordinate::paintWindow(IPaintEvent &)
{
   Boolean stopProcessingEvent = false;

   return stopProcessingEvent;
}


/****************************************************************
* Function:    button1Down
* Parms:    
* 
* Purpose   This occurs on the left mouse button press.  If we 
*           are in ship placement mode,  we need to display the
*           selection buttons.  Otherwise,  we need to determine
*           if a ship is on our coordinate.  If so,  call its hit
*           function.  Otherwise,  show a miss square.
*
* Returns      nothing
****************************************************************/
void CWndPlayerCoordinate::button1Down()
{
   // if at any time player ended game, return
   if (m_pGame->GetGameOver() == true) return;

   // If we are placing ships then load the select bitmap button,  
   // else call the "hit" member function.
   int nGameMode = m_pGame->GetGameMode();
   static Boolean bLayingMines = false;
   static int nMineCount = 0;
   int nType;
   
   switch(nGameMode)
   {               
      case PREGAME:
         break;
      
      // Place ships
      case SETUPGAME:
         // if not player 1's turn, leave
         if (m_pGame->GetPlayerTurn() != PLAYER1)
            return;

         // check if laying mines and finished ships
         if (m_pGame->GetLayMineMode() && bLayingMines)
         {
            if (IsOccupied())
            {
               //do not let them choose the same coordinate twice
               DosBeep(BEEPFREQ, BEEPDURATION);
               return;
            }
               
            /****************************************************************
            * Create a new visible mine and stick it on the list
            ****************************************************************/
            IPoint pPoint = this->GetPoint();
            CMine* pMine = m_pParent->CreateNewMine(pPoint, true);
            nMineCount++;

            m_pParent->SetMinesLeft( m_pGame->GetNumberOfMines() - nMineCount );
            this->SetShipOnCoordinate(pMine);

            //If we are done laying mines,  let the other player set their
            //  stuff up.
            if (nMineCount == m_pGame->GetNumberOfMines())
            {
               bLayingMines = false;
               nMineCount = 0;

               //Hide the game pieces before starting play
               m_pParent->HideGamePieces();

               m_pGame->Player2Setup();
            }
        
            return;
         }


         // mark the bow of the ship and tell the board to make sure the ship
         //  will fit on the board in some fashion.
         if (!m_bDirSelect)
         {
            // if already used, leave the function
            if (IsOccupied())
               return;
               
            setBitmap(SELBUTN);

            //This will display the arrows indicating the directions the ship
            //  will fit on the board.
            m_pParent->FitShipOnBoard(this);
            m_bDirSelect = true;
            refresh();
            break;
         }

         // don't waste time if this is an occupied coordinate or not an arrow
         if (m_pParent->IsAnchorCoord(this) || (!m_pParent->IsValidCoordinate(this)))
            return;

         //This will actually place the ship on the board.  It will inform all the
         // affected coordinates who need to record the fact that this game piece
         // is now on their coordinate.
         if (m_pParent->SetShipOnBoard(this))
         {
            m_bDirSelect = false;

            // setup for next ship
            CWndBattleShipGamePiece* pShip = ((CWndPlayerBoard*)m_pParent)->GetShipBeingPlaced();
            nType = pShip->GetShipType();

            //Show the ship you just placed.
            pShip->show(true);
            pShip->refresh();

            //This sets up the help on the bottom of the screen so the player knows
            // which ship they are in the process of placing.
            switch (nType)
            {
               case eCARRIER:
                  m_pParent->SetShipBeingPlaced( m_pParent->GetBattleShip() );
                  m_pGame->SetInfoareaMessage("Place BattleShip.");
                  break;

               case eBATTLESHIP:
                  m_pParent->SetShipBeingPlaced( m_pParent->GetDestroyer() );
                  m_pGame->SetInfoareaMessage("Place Destroyer.");
                  break;

               case eDESTROYER:
                  m_pParent->SetShipBeingPlaced( m_pParent->GetSubmarine() );
                  m_pGame->SetInfoareaMessage("Place Submarine.");
                  break;

               case eSUBMARINE:
                  m_pParent->SetShipBeingPlaced( m_pParent->GetPTBoat() );
                  m_pGame->SetInfoareaMessage("Place PTBoat.");
                  break;
               
               case ePTBOAT:
                  if (m_pGame->GetLayMineMode())
                  {
                     m_pGame->SetInfoareaMessage("Lay mines.");
                     bLayingMines = true;
                  }
                  else
                  {
                     m_pGame->Player2Setup();
                     bLayingMines = false;
                  }
                  break;

               default: 
                  break;
            }
         }
         break;
   
      case PLAYGAME:   //must be firing at this point
         break;
      default:
         break;
   }
} 


/*****************************************************************************
* Function: mouseClicked
* Parms:    event - info about which mouse button was pressed
* Purpose:  Process the mouse messages generated from the square
* Returns:  false - so someone else can process the message
*****************************************************************************/
Boolean CWndPlayerCoordinate::mouseClicked(IMouseClickEvent &event)
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
Boolean CWndPlayerCoordinate::Hit()   
{  
   Boolean isHit = false;
   static IString csStaticShipName;
    
   //take care of decrementing available targets, etc.
   m_pBattleShipGamePiece->Hit(m_cPoint, PLAYERBOARD);

   // handle a mine
   if (m_pBattleShipGamePiece->GetShipType() == MINE)
   {
      this->Mine();
      return (false);
   }

   //Lets check to see if the piece we just hit is sunk
   if (m_pBattleShipGamePiece->IsShipSunk())
   {
      m_pParent->SinkShip();
      csStaticShipName = '\0';   //We want to empty out this holding var so the code at the
                                 //  bottom of this function works OK
   }
   else 
   {
      //allow the HIT bitmap to show
      setBitmap(HITMARK);
      refresh();
      
      // save the fact that a hit was registered
      isHit = true;   
   } 
   
   //If we are hitting a different ship than before,  clear the stack and 
   // stop tracking.  This takes some of the smarts out of the game but
   //  makes it easier to keep track of where we are. 
   IString csNewShipName;
   csNewShipName = m_pBattleShipGamePiece->GetShipName();
   
   if(csStaticShipName != csNewShipName)
   {
      if( csStaticShipName.isAlphabetic())  //is this string empty??
      {
         m_pGame->GetOpponent()->ClearHitStack();
         isHit = true;
      }
      csStaticShipName = m_pBattleShipGamePiece->GetShipName();
   }
   return isHit;
}

/****************************************************************
* Function:    Mine
*
* Purpose      Handles the actions when a mine is registered
* Returns      Nothing
****************************************************************/
Boolean CWndPlayerCoordinate::Mine()
{  
   setBitmap(MINEEXPL);
   show(true);
   refresh();

   m_pParent->HitMine(PLAYERBOARD);

   return false;
}


/****************************************************************
* Function:    FireOn
*
* Purpose      Handles the affect of an opponent firing on this 
*              coordinate.
* Returns      true - a ship was hit,  false otherwise
****************************************************************/
Boolean CWndPlayerCoordinate::FireOn()
{     
   Boolean isHit = false;
   
   // if at any time player ended game, return
   if (m_pGame->GetGameOver()) 
      return false;

   if(m_pBattleShipGamePiece)
      isHit = this->Hit();
   else
      this->Miss();

//   IString ls_coord;
//   ls_coord = "Last guessed coord = " + m_cPoint.asString();
//   ITRACE_DEVELOP( ls_coord);
//   fflush(stdout);

   return isHit;  //if a ship was hit,  this will be true
}


// CBattleShipGame - Specific BattleShip Game Class
//

#ifndef _ITRACE_
#include <itrace.hpp>
#endif

#include "batshpgm.hpp"
#include "options.hpp"
#include "battle.h"
#include <ifont.hpp>                    //IFont class                         V3
#include <ifont.hpp>                    //IFont class                         V3

#include  "about.h"
#include  "about.hpp"

/////////////////////////////////////////////////////////////////////////////
// CBattleShipGame

CBattleShipGame::CBattleShipGame(
      int defaultNumShips,
      unsigned long id, 
      const IFrameWindow::Style & style, 
      const char * title)
   : IFrameWindow(title, id, IFrameWindow::defaultStyle() 
                                           | IFrameWindow::minimizedIcon),
      Client(FID_CLIENT, this, this),
      color(IColor::darkGray),
      help(IResourceId(HLP_BATTLEAPP), this),
      menuBar(id, this),
      infoArea(this)
{


/*---------------------- Setup the Information Area ----------------------|   V5
|  Change the size of the information area using the maximum height of    |   V5
|    a character in the current font.                                     |   V5
|------------------------------------------------------------------------*/ //V5
   setExtensionSize(&infoArea, IFont(&infoArea).maxCharHeight());            //V5
   SetInfoareaMessage("BattleShip Game");

// We are just starting the game at this point
   m_GameMode = PREGAME;
   m_nNumberOfShips = defaultNumShips;
   m_nNumberOfMines = 5; 
   m_nTurnsPerRound = 1;
   m_bsoundOn = true;
   m_sPlayerName = "you";
   m_nNumberOfTurnsTaken = 0;

   /***********************************************
   * Attach a client area to the frame.
   ***********************************************/
   this->setClient(&Client);
   Client.setColor(color);

// Construct the sound class
   try
   {
      m_pSound = new Sound;
   }
   catch (IException& exc)
   {
      IString msg = "Could not open the wave audio device.  The sound capabilities will be disabled. ";
      if ( exc.isRecoverable() ) 
      {
         msg += "This is recoverable ";
         msg += exc.name();
      }
      else
      {
         msg += "This is NOT recoverable ";
         msg += exc.name();
      }
      IMessageBox(this).show(msg, IMessageBox::information);
      this->SetSound(false);
   }

// Construct the 2 game boards
   try{
      m_pPlayerBoard = new CWndPlayerBoard(this, 100, &Client);
   }
   catch(IException& exc)
   {
      IMessageBox abortIt(this);
      abortIt.setTitle("Exception Caught in Batshpgm.cpp creating Player Board");
      abortIt.show(exc.text(), IMessageBox::okButton);
   }

   try{
         m_pOpponentBoard = new CWndOpponentBoard(this, 101, &Client);
   }
   catch(IException& exc)
   {
      IMessageBox abortIt(this);
      abortIt.setTitle("Exception Caught in Batshpgm.cpp creating Opponent Board");
      abortIt.show(exc.text(), IMessageBox::okButton);
   }
                            
// Construct the opponent class
   try{
      m_pOpponent = new COpponent(this);
   }
   catch(IException& exc)
   {
      IMessageBox abortIt(this);
      abortIt.setTitle("Exception Caught in Batshpgm.cpp creating Opponent");
      abortIt.show(exc.text(), IMessageBox::okButton);
   }

   //initialize the game options here
   m_PlayerTurn = PLAYER1;
   m_bLayMines = true;
   m_bGameOver = false;
   m_bSmartOpponent = true;
   m_nSmartOpponent = 1;

   //syntax is as follows:
   // child window,scolumn/row, # of cols and rows
   Client
      .addToCell(m_pPlayerBoard, 2,2,2,2)       //Player Board control
      .addToCell(m_pOpponentBoard, 5,2,2,2);    //Opponent Board control

   /***************************************
   * Set up the layout of the canvas
   ***************************************/
   Client.setColumnWidth(6, IMultiCellCanvas::defaultCell().width(), false);

   Client
      .setRowHeight(1, 15, false)
      .setRowHeight(2, 100, false)
      .setRowHeight(3, 95, false)
      .setRowHeight(4, 15, false)
      .setRowHeight(5, 25, false)
      .setRowHeight(6, 5, false)
      .setRowHeight(7, 15, false)
      .setRowHeight(8, 35, false);

   m_pPlayerBoard->setMinimumSize(ISize(200, 200));
   m_pOpponentBoard->setMinimumSize(ISize(200, 200));

   /**********************************
   * Size the frame according to the
   * client window.
   **********************************/
   Client.setMinimumSize(ISize(450,330));
   ISize clientSize(Client.minimumSize());
   moveSizeToClient(IRectangle( IPoint(10, 80), clientSize));

//Put the picture of the ship on the bottom of the window.  The bitmap
// is located in the battle.dll file located in the current directory
   m_iBitmapShip = new IBitmapControl(
                     1, 
                     this, 
                     this, 
                     IResourceId(2001, IDynamicLinkLibrary("battle")), 
                     IRectangle(IPoint(10,25),ISize(440, 103)));

   m_iBitmapShip->setBackgroundColor(IColor::darkGray);
   m_iBitmapShip->setAlignment(IStaticText::bottomCenter);
   m_iBitmapShip->enable(false);

   /******************************************************************
   * Add the handlers to this window
   ******************************************************************/
   addHandler((ICommandHandler *)this);
   helpHandler.handleEventsFor(this);
  
   // set the library name and window title for the help window
   help.addLibraries("battle.hlp")
       .setTitle(WND_BATTLEWIN)
       .associateWindow(this);


   //Enable tracing in the program.  To use it redirect the 
   //  battle.exe to a filename e.g. battle.exe > dave.err
   //  Make sure environment has set iclui_trace=ON
   ITrace::enableTrace();
   ITrace::enableWriteLineNumber();
   ITrace::enableWritePrefix();
   ITrace::writeToStandardOutput();
}

CBattleShipGame::~CBattleShipGame()
{
   if (m_iBitmapShip)
      delete m_iBitmapShip;

   if (m_pPlayerBoard)
      delete m_pPlayerBoard;

   if (m_pOpponentBoard)
      delete m_pOpponentBoard;

   if (m_pOpponent)
      delete m_pOpponent;

   if ( m_pSound ) 
      delete m_pSound;
}

/*****************************************************************************
* Function: Initialize
*
* Purpose:  Calls all the major game components telling them to initialize
*           themselves.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::Initialize()
{
   IFUNCTRACE_DEVELOP();
   m_pPlayerBoard->Initialize();
   m_pOpponentBoard->Initialize();
   m_pOpponent->Initialize();        //Clear out the already guessed stack //dsb

   m_bGameOver = false;
   m_PlayerTurn = PLAYER1;
}

/*****************************************************************************
* Function: StartGame
*
* Purpose:  Set the game mode to SETUPGAME and calls the initialize function.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::StartGame()
{
   IFUNCTRACE_DEVELOP();

   //We are placing ships when we start a new game
   SetGameMode(SETUPGAME);   // inline function
   this->Initialize();
}

/*****************************************************************************
* Function: EndGame
*
* Purpose:  Sets a variable to indicate the game is over.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::EndGame()
{
   m_bGameOver = true;
   SetInfoareaMessage("Game Over.");
}

/*****************************************************************************
* Function: PauseGame
*
* Purpose:  This would eventually be used if a timer was part of the game
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::PauseGame()
{
}


/*****************************************************************************
* Function: SetGameOver
*
* Purpose:  Display a message as to who won the game,  and play a sound.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::SetGameOver(int a_caller)
{ 
   IString ls_msg;

   //Turn the sound on if configured that way
   if ( this->GetSound()) 
      m_pSound->playSound("waah.wav"); 

   switch (a_caller)
   {
    case PLAYERBOARD:
      ls_msg = "Hey " +  m_sPlayerName + ",  your opponent has won the game...you loser!!";
      IMessageBox(this).show(ls_msg, IMessageBox::information);
      break;
   
    case OPPONENTBOARD:
      ls_msg = "Hey " +  m_sPlayerName + ", You've won the game !!";
      IMessageBox(IWindow::desktopWindow()).show(ls_msg, IMessageBox::information);
      break;
   }
   this->EndGame();
}


//------------------------------------------------------------------------------
// CBattleShipGame :: defaultTitle
//------------------------------------------------------------------------------
//#pragma export (CBattleShipGame::defaultTitle())
IString CBattleShipGame::defaultTitle()
{
   return("Battle Ship");
}


/*****************************************************************************
* Function: command
* Parms:    event
* Purpose:  process the menu items
* Returns:  false
*****************************************************************************/
Boolean CBattleShipGame::command(ICommandEvent& event)
{
   Boolean stopProcessingEvent = false;
   int li_rc;

   switch (event.commandId())
   {
    case MI_BATTLEWIN_GAME_NEW:
      StartGame();

      //Move this later!!
      m_nSmartOpponent = (m_nSmartOpponent != 1);
      break;

    case MI_BATTLEWIN_GAME_END_GAME:
      this->EndGame();
      break;

    case MI_BATTLEWIN_GAME_EXIT:
      WinPostMsg(handle(), WM_CLOSE, 0L, 0L);
      break;

    case  MI_BATTLEWIN_OPTIONS:
      li_rc = gameOptions();
      if ( li_rc != 1 ) 
         WinPostMsg(handle(), WM_CLOSE, 0L, 0L);
      break;

    case MI_HELP_CONTENTS:
      help.show(IHelpWindow::contents);
      break;

    //case SC_HELPEXTENDED:
    // break;

    case MI_HELP_ABOUT:
       aboutBox();
       break;

      default:
         break;
   }
   return stopProcessingEvent;
}


/*****************************************************************************
* Function: SetInfoareaMessage
*
* Purpose:  Display the passed in string in the main window info area.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::SetInfoareaMessage(IString msg)
{
   infoArea.setInactiveText(msg);  
} 


/*****************************************************************************
* Function: gameOptions
*
* Purpose:  Call the notebook control generated by visual builder so the player
*           can set up the game options.
*
* Returns:  nothing
*****************************************************************************/
int CBattleShipGame::gameOptions()
{
   IFUNCTRACE_DEVELOP();
   int li_rc = 1;
   Options *iPart;

   IRectangle rect(IPoint(10, 10), ISize(396, 309));
   IMessageBox::Response resp = IMessageBox::unknown;

   do 
   {
      try 
      {
         //Instantiate the notebook control.
         iPart = new Options(VBBASEWINDOWID, IWindow::desktopWindow(), this, rect);
         iPart->initializePart();
      }
      catch (IException& exc) 
      { 
         resp = IMessageBox(this).show(exc);
      }
   }
   while (resp == IMessageBox::retry);

   if (resp == IMessageBox::cancel) 
      li_rc = -1;
   else
   {
      //Show the created control and delete it when the player is done.
      iPart->showModally();
      delete iPart;
   }
   return li_rc;
}


/*****************************************************************************
* Function: aboutBox
* Parms:    none
* Purpose:  Handle the about dialog box
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::aboutBox()
{
   unsigned short value;                 //Return value from dialog

//Create a Text Dialog
   AboutDialog* ADlg;
   try 
   {
      ADlg = new AboutDialog(this, dlg_about, this); 
   }
   catch (IException& exc)
   {
      IString msg = "Could not open the about box.";
      msg += exc.name();

      IMessageBox(this).show(msg, IMessageBox::information);

      //This will log the exception data to a trace file
      //tracing must be on and the program output redirected to a
      // file on startup e.g. battle > bat.trc
      exc.logExceptionData();
      return;
   }

   ADlg->showModally();            //Show this Text Dialog as Modal
   value=ADlg->result();           //Get result (eg OK or Cancel)

   delete ADlg;                    //Delete textDialog
}


/*****************************************************************************
* Function: SetPlayerName
* Parms:    IString as_playerName
* Purpose:  This sets a member variable on the game that is used to 
*           personalize some of the message boxes used in the game.
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::SetPlayerName(IString as_playerName)   
{
   //This clears out the existing entry,  for some reason I had to use
   // the += operator to expand the name from "you" which was in the
   // constructor.
   m_sPlayerName = "";
   
   //If there is no name entered,  we will default the name to "you".
   if (as_playerName.isWhiteSpace())
      m_sPlayerName += "you";
   else
      m_sPlayerName += as_playerName.stripTrailing();
}


/*****************************************************************************
* Function: Player2Setup
*
* Purpose:  After player1 is done placing his/her ships,  this function is
*           called to tell the computer opponent to place its ships.  It will
*           also start the game by setting the game mode and taking the first
*           turn. (player 1 takes the first turn)
*           
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::Player2Setup()
{
   IString ls_msg;
   
   m_pOpponent->PlaceShips();
   if (m_bLayMines)
      m_pOpponent->PlaceMines();
   
   // After all the ships and mines have been placed,  Hide them
   m_pPlayerBoard->HideGamePieces();
   ls_msg = "OK " + m_sPlayerName + ", the opponent's ships are placed. Take a shot on the Opponent Board.";
   IMessageBox(this).show(ls_msg, IMessageBox::information);

   // message player
   SetInfoareaMessage("Start game.");

   this->SetGameMode(PLAYGAME);
   this->TakeTurn();
   return;
}


/*****************************************************************************
* Function: TakeTurn
*
* Purpose:  This is called from the opponent class and the opponent coordinate
*           class.  Depending on if we are setting up the game or actually 
*           playing it,  it will do diferent things.  Once we are playing the
*           game,  this will actually handle whose turn it is to fire and call
*           a function in the opponent class to tell them to fire when it is 
*           their turn.
*
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::TakeTurn()
{
   if (m_PlayerTurn == PLAYER1)  //PLAYER1 = Human player
   {
      //I am not sure I want to erase the last message on the screen
      //SetInfoareaMessage("Take shot.");
   }
   else
   {
      ITRACE_DEVELOP( "First Opponent Shot");
      m_pOpponent->TakeShot();

      //If PLAYER1 hit a mine previously,  give the computer two shots
      // Only do this if we did not just hit a mine!
      if (this->GetOpponentBoard()->GetPenalty())        
      {
         ITRACE_DEVELOP( "Opponent Penalty Shot");
         this->GetOpponentBoard()->SetPenalty(false);
         m_pOpponent->TakeShot();
      }
   }
}


/*****************************************************************************
* Function: DecidePlayerTurn
*
* Purpose:  After each player fires, we need to decide whose turn it is next. 
*           This is based on whether any penalties are registered on either 
*           board.  If no penalties are registered,  each player gets on turn
*           If a penalty is registered on one or both of the boards,  this will
*           set it up so the other player gets two turns (make the penalty player
*           lose a turn)
*           
* Returns:  nothing
*****************************************************************************/
void CBattleShipGame::DecidePlayerTurn(int a_caller)
{
   // When it is the PLAYER1 turn,  we will get to guess twice if there is 
   // currently a penalty lodged against PLAYER2. We force this by not toggling
   // the turn.  The toggleturn function that calls this will also check for the
   // penalty lodged against PLAYER2 and will take another shot if there is a
   // penalty registered on the OpponentBoard.  (That is where PLAYER2 penalties
   // are lodged.
   if ( a_caller == PLAYERBOARD ) 
   {
      if( this->GetOpponentBoard()->GetPenalty())
         return;
   }

   // If the opponent is calling,  we need to check to see if the compuer
   // hit a mine in the previous turn.  If so,  PLAYER2 will get two turns.  We
   // force this by clearing the penalty and failing to toggle the turn.
   if ( a_caller == OPPONENTBOARD ) 
   {
      if( this->GetPlayerBoard()->GetPenalty())
      {
         this->GetPlayerBoard()->SetPenalty(false);
         return;
      } 
   }

   //This keeps track of the number of turns per round.  If you exceed your
   // limit - pass the turn to the next player.  Keep in mind that if a penalty
   // was encountered above,  you will in effect have an extra turn.
   if(++m_nNumberOfTurnsTaken == m_nTurnsPerRound)
   {
      m_nNumberOfTurnsTaken = 0;    //reset the number of turns
      m_PlayerTurn = !m_PlayerTurn; //switch players
   }

   this->TakeTurn();                //tell someone to take a shot
}




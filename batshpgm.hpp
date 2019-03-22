// CBattleShipGame - Specific BattleShip board game class
//
#ifndef __BATTLEGAME_H__
#define __BATTLEGAME_H__

#define INCL_WIN
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdio.h>

#include  <iframe.hpp>
#include  <iinfoa.hpp>           /* IInfoArea class header      */
#include  <imenubar.hpp>         /* IMenu Stuff                 */
#include  <icmdhdr.hpp>          /* ICommandHandler             */
#include  <icanvas.hpp>          /* Canvas class stuff          */
#include  <imcelcv.hpp>          /* Multicell Canvas class      */
#include  <iaccel.hpp>           /* Menu accelerator stuff      */
#include  <ipushbut.hpp>         /* push button stuff           */
#include  <ibmpctl.hpp>          /* Bitmap Stuff                */
#include  <imsgbox.hpp>          /* MessageBox Class            */

#include <assert.h>              /* Assert Functionality        */
#include <ihelp.hpp>
#include <ihelphdr.hpp>


#include <igbitmap.hpp>
#include  <ipainhdr.hpp>         /* IPaintHandler               */
#include  <ipainevt.hpp>         /* IPaintEvent                 */

/*----------------------------------------------------------------------------*/
/* Align classes on four byte boundary.                                       */
/*----------------------------------------------------------------------------*/
#pragma pack(4)

class CBattleShipGame;     //Forward declarations
class COpponent;

#include "brdgame.hpp"
#include "w_plabrd.hpp"
#include "w_oppbrd.hpp"  
#include "opponent.hpp"
      
enum {PREGAME, SETUPGAME, PLAYGAME};
enum {PLAYER1, PLAYER2};

class CBattleShipGame : public IFrameWindow,
                        public ICommandHandler,                      
                        public CBoardGame
                        
{
public:
   CBattleShipGame(
      int defaultNumShips=5,
      unsigned long id = WND_BATTLEWIN,
      const IFrameWindow::Style & style = IFrameWindow::defaultStyle(),
      const char * title = defaultTitle()
      );
   ~CBattleShipGame();


// Attributes
private:
   static IString       defaultTitle();

   IMultiCellCanvas     Client;
   IColor               color;
   IBitmapControl       *m_iBitmapShip;
//   IGBitmap             *m_iBitmapShip;
   IMenuBar             menuBar;
   IInfoArea            infoArea; 
   IHelpWindow          help;
   IHelpHandler         helpHandler;

   COpponent*           m_pOpponent;
   CWndPlayerBoard*     m_pPlayerBoard;
   CWndOpponentBoard*   m_pOpponentBoard;
   Sound*               m_pSound;

   Boolean              m_bLayMines;
   Boolean              m_bGameOver;
   Boolean              m_bSmartOpponent;   
   Boolean              m_bsoundOn;
   int                  m_GameMode;
   int                  m_PlayerTurn;
   int                  m_nNumberOfShips;
   int                  m_nNumberOfMines;
   int                  m_nSmartOpponent;
   int                  m_nTurnsPerRound;
   int                  m_nNumberOfTurnsTaken;
   IString              m_sPlayerName;

   /* -------------------------------------------------------- */
   /* declare the event handlers. These event handlers are all */
   /* pure virtual functions in their respective base classes  */
   /* -------------------------------------------------------- */
   virtual Boolean command(ICommandEvent&);

// Operations
protected:
   int      gameOptions();
   void aboutBox();

public:
   int      GetGameMode() { return m_GameMode; }           // Returns the current game state 
   void     SetGameMode(int nMode) {m_GameMode = nMode;}   // Set the current game state
            
   int      GetPlayerTurn()      { return m_PlayerTurn; }  // Returns the player who's turn it is
   void     TakeTurn();                                    // Sets the player who's turn it is
   void     Player2Setup();
                                                           // Returns the player who's turn it is
   Boolean  GetGameOver() { return m_bGameOver; }
   Boolean  GetLayMineMode()  { return m_bLayMines; }
   Boolean  isSmartOpponent() { return m_bSmartOpponent; }
   Boolean  GetSound()  { return m_bsoundOn; }
   int      GetNumberOfShips()   { return m_nNumberOfShips; }
   int      GetNumberOfMines()   { return m_nNumberOfMines; }
   int      GetTurnsPerRound()   { return m_nTurnsPerRound; }
   char *   GetPlayerName()      { return m_sPlayerName; }

   Sound*   getSoundPointer()    { return m_pSound;} 
   void     SetLayMineMode(Boolean bLayMines) { m_bLayMines = bLayMines; }
   void     SetSmartOpponent(Boolean bSmartFlag) { m_bSmartOpponent = bSmartFlag; }
   void     SetNumberOfMines(int numMines)  { m_nNumberOfMines = numMines; }
   void     SetSound(Boolean bSound)  { m_bsoundOn = bSound; }
   void     SetTurnsPerRound(int numTurns)  { m_nTurnsPerRound = numTurns; }
   void     SetPlayerName(IString playerName);
   void     DecidePlayerTurn(int);

   void     SetGameOver(int);
   void     SetInfoareaMessage(IString);
   void     Initialize();
   void     StartGame();
   void     EndGame();
   void     PauseGame();
      
   COpponent*           GetOpponent() { return m_pOpponent;}
   CWndPlayerBoard*     GetPlayerBoard() { return m_pPlayerBoard; }
   CWndOpponentBoard*   GetOpponentBoard() { return m_pOpponentBoard; }

};
#endif


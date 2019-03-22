/*******************************************************************************
* FILE NAME: battle.cpp                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Main program stub for class:                                               *
*******************************************************************************/
#include <iapp.hpp>
#include <imsgbox.hpp>
#include "batshpgm.hpp"

int main(int argc, char ** argv)
{
   CBattleShipGame *m_pBattleShipGame;

   IApplication::current().setArgs(argc, argv);
   IMessageBox::Response resp = IMessageBox::unknown;

   try 
   {
      // instantiate game instance
      m_pBattleShipGame = new CBattleShipGame(5);
   }
   catch (IException& exc) 
   { 
      resp = IMessageBox(IWindow::desktopWindow()).show(exc);
   }

   /******************************************
   * Load the accelerators from the .rc file
   ******************************************/
   IAccelerator accelTable(WND_BATTLEWIN, m_pBattleShipGame);

   //Show the window
   m_pBattleShipGame->setFocus();
   m_pBattleShipGame->show();
   m_pBattleShipGame->setAutoDeleteObject();

   IApplication::current().run();
   return 0;
}  


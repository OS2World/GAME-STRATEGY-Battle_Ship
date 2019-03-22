/*****************************************************************************
* Program:  ABOUT.CPP
* Purpose:  Handles items with the about dialog box
*****************************************************************************/
#include <os2.h>
#include <icmdevt.hpp>                  //ICommandEvent
#include <ireslib.hpp>                  //IResourceLibrary/IResourceId Class
#include <stdlib.h>

#include "about.hpp"                   //AboutDialog Class

/*****************************************************************************
* Function: AboutDialog
* Parms:    owner windows
* Purpose:  Constructor
* Returns:  Nothing
*****************************************************************************/
AboutDialog :: AboutDialog(IWindow * ownerWnd, 
                           unsigned long rid, 
                           IWindow* pbwindow)
             : IFrameWindow(IResourceId(rid), ownerWnd)
{
   ICommandHandler::handleEventsFor(this); //Set self as command event handler
} 

/*****************************************************************************
* Function: ~AboutDialog
* Parms:    none
* Purpose:  Destructor
* Returns:  Nothing
*****************************************************************************/
AboutDialog :: ~AboutDialog()
{
//  ICommandHandler::stopHandlingEventsFor(this);  
} 

/*****************************************************************************
* Function: command
* Parms:    cmdevt
* Purpose:  handle the event for the command button
* Returns:  true - OK was pressed,  false otherwise
*****************************************************************************/
Boolean AboutDialog :: command(ICommandEvent& cmdevt)
{
   switch(cmdevt.commandId()) 
   {
   case DID_OK:
      dismiss(DID_OK);                 //Dismiss Dialog - Allow focus to main
      return(true);                    //Return Processing Completed
      break;
   }
   return(false);                       //Allow Default Processing to occur
}


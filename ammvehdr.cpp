/*****************************************************************************
* Program:  AMMveHdr.CPP
* Purpose:  track WM_MOUSEMOVE messages
*****************************************************************************/
#include <iwindow.hpp>
#define INCL_WININPUT
#include <os2.h>
#include "ammvehdr.hpp"

/*****************************************************************************
* Function: motion
* Parms:    evt
* Purpose:  track the mouse movement - handle WM_MOUSEMOVE event
* Returns:  false
*****************************************************************************/
Boolean AMouseMoveHandler::motion( IEvent &evt )
{
   return false;
}

/*****************************************************************************
* Function: dispatchHandlerEvent
* Parms:    evt
* Purpose:  figure out if we are tracking a mousemove - if so call the motion
*           function
* Returns:  false
*****************************************************************************/
Boolean AMouseMoveHandler::dispatchHandlerEvent( IEvent &evt )
{
   if ( evt.eventId() == WM_MOUSEMOVE ) {
      return motion( evt );
   }
   return false;
} 

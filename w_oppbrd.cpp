// CWndOpponentBoard - Computer player's Battleship game board
//

#include "batshpgm.hpp"
#include "assert.h"
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CComputerBoard

CWndOpponentBoard::CWndOpponentBoard(CBattleShipGame *pGame, 
                                     unsigned long id, 
                                     IWindow* parent)
   : CWndBattleShipBoard(pGame, id, parent)
{
   int k=0;
   IPoint iPoint;
   IRectangle rect(IPoint(10, 10), ISize(200, 200));
   setColor(ICanvas::background, IColor::paleGray);

   m_Game = pGame;
   m_pRightNeighbor = NULL;
   m_pLeftNeighbor = NULL;
   m_pUpNeighbor = NULL;
   m_pDownNeighbor = NULL;

   // Position the coodinates on the board
   for (int i=0; i<10; i++)
   {
      for (int j=0; j<10; j++)
      {
         iPoint = IPoint(j, i);
         try
         {
               pCoordinate = new CWndOpponentCoordinate(this, 
                                                        iPoint, 
                                                        m_pGame,
                                                        m_pSound,
                                                        k, 
                                                        BLANK,
                                                        IRectangle(IPoint(j*COORDWIDTH, i*COORDHEIGHT),
                                                        ISize(COORDWIDTH,COORDHEIGHT)));
         }
         catch(IException& exc)
         {
            IMessageBox abortIt(IWindow::desktopWindow());
            abortIt.setTitle("Exception Caught in w_plabrd.cpp creating coordinates!");
            abortIt.show(exc.text(), IMessageBox::okButton);
         }
         m_CoordinateArray[k] = pCoordinate;
         k++;
      }
   }

   // Instantiate all the ships
   CreateShips();
}

CWndOpponentBoard::~CWndOpponentBoard()
{
   for (int i=0; i<10; i++)
   {
      for (int j=0; j<10; j++)
      {
         pCoordinate = m_CoordinateArray[(i*10)+j];
         delete pCoordinate;
      } 
   }

// Delete the ships   
   DeleteShips();

// Delete the mines
   DeleteMines();
}

void CWndOpponentBoard::Initialize()
{
   IFUNCTRACE_DEVELOP();

   CWndOpponentCoordinate* pCoordinate;

   //Initialize all the ships
   m_Submarine->Initialize();
   m_Carrier->Initialize();
   m_PTBoat->Initialize();
   m_Destroyer->Initialize();
   m_BattleShip->Initialize();
   
   //Call our ancestor's initialize function as well.
   CWndBattleShipBoard::Initialize();
   
   // Delete the mines
   DeleteMines();
   
   
   //Loop through all the coordinates initializing each one
   for (int i=0; i<10; i++)
   {
      for (int j=0; j<10; j++)
      {
         pCoordinate = m_CoordinateArray[(i*10)+j];
         pCoordinate->Initialize();
      }
   }

   //This will clear up any bit maps on the coords   
   refresh();

   //clear out the already guessed values
   m_GuessStack.clear();            
}


/****************************************************************
* Function:    FitShipOnBoard
*
* Purpose      Determine the fit of a ship (neighbors).
*
* Returns      UCHAR
****************************************************************/
UCHAR CWndOpponentBoard::FitShipOnBoard(CWndOpponentCoordinate* pCoord)
{
   UCHAR ucGoodDirections = 0;
   m_pAnchorCoordinate = pCoord;

   IFUNCTRACE_DEVELOP();

   // check if ship fits AND there are no other ships obstructing path
   // (NOTE: no directional bitmaps in opponent's board)
   if (DoesShipFit(RIGHT))
      {
      m_pRightNeighbor = (CWndOpponentCoordinate*) GetNeighbor(m_pAnchorCoordinate, RIGHT);
      ucGoodDirections |= RIGHT;
      }

   if (DoesShipFit(LEFT))
      {
      m_pLeftNeighbor = (CWndOpponentCoordinate*) GetNeighbor(m_pAnchorCoordinate, LEFT);
      ucGoodDirections |= LEFT;
      }

   if (DoesShipFit(UP))
      {
      m_pUpNeighbor = (CWndOpponentCoordinate*) GetNeighbor(m_pAnchorCoordinate, UP);
      ucGoodDirections |= UP;
      }

   if (DoesShipFit(DOWN))
      {
      m_pDownNeighbor = (CWndOpponentCoordinate*) GetNeighbor(m_pAnchorCoordinate, DOWN);
      ucGoodDirections |= DOWN;
      }

   return (ucGoodDirections);
}

/****************************************************************
* Function:    GetNeighbor
*
* Purpose      Locates the surrounding coordinates eligible for 
*              path selection.
*
* Returns      CBattleShipCoordinate* 
****************************************************************/
CBattleShipCoordinate* CWndOpponentBoard::GetNeighbor(CWndOpponentCoordinate* pCoord, int nWhere)
{
   // de-reference the ObArray
   int nIndex = GetCoordinateIndex(pCoord, nWhere);
   assert(nIndex >= 0);

   CBattleShipCoordinate* pNeighbor = m_CoordinateArray[nIndex];
   assert(pNeighbor > 0);

   return (pNeighbor);
}

/****************************************************************
* Function:    GetCoordinateIndex
*
* Purpose      Returns index from array for IPoint.
*
* Returns      int
****************************************************************/
int CWndOpponentBoard::GetCoordinateIndex(CWndOpponentCoordinate* pCoord, int nWhere)
{
   IFUNCTRACE_DEVELOP();

   IPoint pPt = pCoord->GetPoint();
   switch (nWhere)
      {
      case RIGHT:
         return( (pPt.y()*10) + (pPt.x()+1) );
         break;

      case LEFT: //
         return( (pPt.y()*10) + (pPt.x()-1) );
         break;

      case DOWN: //
         return( ((pPt.y()-1)*10) + (pPt.x()) );
         break;

      case UP: //
         return( ((pPt.y()+1)*10) + (pPt.x()) );
         break;
      }
   
   return (0);
}

/****************************************************************
* Function:    DoesShipFit
*
* Purpose      Determines if the ship's size can fit and there's 
*              a clear path.
*
* Returns      Boolean 
****************************************************************/
Boolean CWndOpponentBoard::DoesShipFit(int nWhere)
{                                   
   IFUNCTRACE_DEVELOP();

   IPoint pPt = m_pAnchorCoordinate->GetPoint();
   int len = m_pShipBeingPlaced->GetLength();

   // check for size first to prevent problems in the ObArray
   switch (nWhere)                              
      {
      case RIGHT:
         if ( (pPt.x() + (len-1)) > 9)  // off the board on the right
            return (FALSE);
         break;

      case LEFT:
         if ( (pPt.x() - (len-1)) < 0)  // off the board on the left
            return (FALSE);
         break;

      case DOWN: //
         if ( (pPt.y() - (len-1)) < 0)  // off the board up top
            return (FALSE);
         break;

      case UP: //
         if ( (pPt.y() + (len-1)) > 9)  // off the board down bottom
            return (FALSE);
         break;
      }

   // now check for obstruction
   Boolean bObstruction = TRUE;
   CWndOpponentCoordinate* pCoord = m_pAnchorCoordinate;
   bObstruction = IsObstruction(pCoord, nWhere);
   return ( !bObstruction );
}

/****************************************************************
* Function:    IsObstruction
*
* Purpose      Check for obstruction recursively.
*
* Returns      BOOL
****************************************************************/
Boolean CWndOpponentBoard::IsObstruction(CWndOpponentCoordinate* pCoord, int nWhere)
{
   static int nIndex = 1;
   char ls_buf[40];

   // I left some error checking in here that helps during debugging!
   ITRACE_DEVELOP( _itoa(nIndex, ls_buf, 10) );
   ITRACE_DEVELOP( _itoa(nWhere, ls_buf, 10) );
   if ( !pCoord ) 
   {
      ITRACE_DEVELOP(" pCoord <= 0 ");
      return FALSE;  
   } 
   assert(pCoord > 0);

   //If the coordinate already has something on it,  than return true and reset
   //  the index.
   if (pCoord->IsOccupied())
   {
      nIndex = 1;
      return TRUE;
   }

   // we got to the end of the ship's length without obstruction,
   // reset index for next ship and return false
   if (nIndex >= m_pShipBeingPlaced->GetLength())
   {
      nIndex = 1;
      return FALSE;
   }
   
   // keep calling IsObstruction with the next neighbor
   nIndex++;
   CWndOpponentCoordinate* pNext = (CWndOpponentCoordinate*) GetNeighbor(pCoord, nWhere);

   if (IsObstruction(pNext, nWhere))
   {
      nIndex = 1;
      return TRUE;
   }

   return FALSE;
}

/****************************************************************
* Function:    GetChosenCoordinate
*
* Purpose      When given a IPoint arg., returns the coordinate
*              for that index.
*
* Returns      CWndOpponentCoordinate*
****************************************************************/
CWndOpponentCoordinate* CWndOpponentBoard::GetChosenCoordinate(IPoint* pCPoint)
{
   int nIndex = GetCoordinateIndex(pCPoint);

   CWndOpponentCoordinate* pCoordinate = m_CoordinateArray[nIndex];

   return (pCoordinate);
}

/****************************************************************
* Function:    SetShipOnBoard
*
* Purpose      Use chosen direction to set the direction and 
*                 place the ship.
*
* Returns      BOOL
****************************************************************/
Boolean CWndOpponentBoard::SetShipOnBoard(UCHAR ucChosenDirection)
{
   IFUNCTRACE_DEVELOP();

   int nWhere = ucChosenDirection;

   // place the Anchor first
   CWndOpponentCoordinate* pCoord = m_pAnchorCoordinate;
      
   // run through the neighbors of the selected coordinate and set the ships's
   // bitmaps
   int nShipNumber = m_pShipBeingPlaced->GetHorizontalShipNumber();

   m_ixStartingPoint = ((m_pAnchorCoordinate->GetPoint().x())*COORDWIDTH);
   m_iyStartingPoint = ((m_pAnchorCoordinate->GetPoint().y())*COORDHEIGHT);

   if (nWhere == RIGHT || nWhere == LEFT)
   {
      // figure out the crucial x,y coords
      m_iBitmapWidth = pCoord->GetWidth() * m_pShipBeingPlaced->GetLength();
      m_iBitmapHeight = pCoord->GetHeight();

      // if left arrow chosen, back it off left a ship's length
      if (nWhere == LEFT)
         m_ixStartingPoint -= (pCoord->GetWidth() * 
                              (m_pShipBeingPlaced->GetLength()-1));
   }
   else
   {
      if (nWhere == UP || nWhere == DOWN)
      {
         //the vertical bitmaps are numbered different than the horizontal
         // ones by this defined delta in battle.h
         nShipNumber += VERTICALSHIPDELTA;  

         // figure out the crucial x,y coords
         m_iBitmapWidth = pCoord->GetWidth();
         m_iBitmapHeight = pCoord->GetHeight() * m_pShipBeingPlaced->GetLength();

         // if up arrow chosen, back it off upward a ship's length
         if (nWhere == DOWN)
            m_iyStartingPoint -= pCoord->GetHeight() * 
                                 (m_pShipBeingPlaced->GetLength()-1);
      }
   }

   m_pShipBeingPlaced->setBitmap(nShipNumber);

   // place the Anchor first then run through all the rest
   pCoord = m_pAnchorCoordinate;
   pCoord->SetShipOnCoordinate(m_pShipBeingPlaced);
   for (int i=1; i<m_pShipBeingPlaced->GetLength(); i++)
   {
      CWndOpponentCoordinate* pNextCoord = (CWndOpponentCoordinate*) GetNeighbor(pCoord, nWhere);
      pCoord = pNextCoord;
 
      // set the ship
      pCoord->SetShipOnCoordinate(m_pShipBeingPlaced);
   }

   // move ship button to location of anchor coordinate
   IRectangle rect(IPoint(m_ixStartingPoint, m_iyStartingPoint), 
                   ISize(m_iBitmapWidth, m_iBitmapHeight));
   m_pShipBeingPlaced->moveSizeTo(rect);
   
   // keep ships hidden
   m_pShipBeingPlaced->show(false);

   m_pRightNeighbor = NULL;
   m_pLeftNeighbor = NULL;
   m_pUpNeighbor = NULL;
   m_pDownNeighbor = NULL;
   
   return (1);
}

/****************************************************************
* Function:    isAlreadyGuessed
*
* Purpose      Calls the stack class to see if the point exists
*              on the stack (already been called)
*
* Returns      TRUE - already been called FALSE - new point
****************************************************************/
Boolean CWndOpponentBoard::isAlreadyGuessed(IPoint cPoint)     
{
 if(m_GuessStack.AlreadyGuessed(&m_GuessStack, cPoint) )
    return(TRUE); 
 else
    return(FALSE); 
}   


/****************************************************************
* Function:    isAlreadyHit
*
* Purpose      Calls the stack class to see if the point exists
*              on the hit stack (used for smart opponent)
*
* Returns      TRUE - already been called FALSE - new point
****************************************************************/
Boolean CWndOpponentBoard::isAlreadyHit(IPoint cPoint)  
{
 if(m_HitStack.AlreadyGuessed(&m_HitStack, cPoint) )
    return(TRUE); 
 else
    return(FALSE); 
}   
// CWndPlayerBoard - Human player's Battleship game board
//

#include "batshpgm.hpp"


CWndPlayerBoard::CWndPlayerBoard(CBattleShipGame *pGame, 
                                 unsigned long id, 
                                 IWindow* parent)
   : CWndBattleShipBoard(pGame, id, parent)
{
   int k=0;
   IPoint iPoint;
   IRectangle rect(IPoint(10, 10), ISize(200, 200));
   setColor(ICanvas::background, IColor::paleGray);

   m_pGame = pGame;
   m_pRightNeighbor = NULL;
   m_pLeftNeighbor = NULL;
   m_pUpNeighbor = NULL;
   m_pDownNeighbor = NULL;
   m_nMinesLeft = m_pGame->GetNumberOfMines();

   // Position the coodinates on the board
   for (int i=0; i<10; i++)  //rows
   {
      for (int j=0; j<10; j++) //columns
      {
         iPoint = IPoint(j, i);
         try{
            pCoordinate = new CWndPlayerCoordinate(this, 
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

/****************************************************************
* Function:    ~CWndPlayerBoard()
*
* Purpose      Destructor for the player board.  You must delete
*              all the squares that were instantiated.
*
* Returns      void
****************************************************************/
CWndPlayerBoard::~CWndPlayerBoard()
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

/****************************************************************
* Function:    Initialize
*
* Purpose      Initializes the ships, the player board, and the
*              player coordinates.
*
* Returns      void
****************************************************************/
void CWndPlayerBoard::Initialize()
{
   IFUNCTRACE_DEVELOP();

   //Initialize all the ships
   m_Submarine->Initialize();
   m_Carrier->Initialize();
   m_PTBoat->Initialize();
   m_Destroyer->Initialize();
   m_BattleShip->Initialize();

   // Delete the mines
   DeleteMines();

   //Call our anscestor's initialize function as well   
   CWndBattleShipBoard::Initialize();
   
   CWndPlayerCoordinate* pCoordinate;
   
   for (int i=0; i<10; i++)
   {
      for (int j=0; j<10; j++)
      {
         pCoordinate = m_CoordinateArray[(i*10)+j];
         pCoordinate->Initialize();
      }
   }
   refresh();
}

/****************************************************************
* Function:    FitShipOnBoard
*
* Purpose      Determince the fit of a ship (neighbors).
*
* Returns      void
****************************************************************/
void CWndPlayerBoard::FitShipOnBoard(CWndPlayerCoordinate* pCoord)
{
   IFUNCTRACE_DEVELOP();
   m_pAnchorCoordinate = pCoord;

   // check if ship fits AND there are no other ships obstructing path
   // then set the directional bitmap
   if (DoesShipFit(RIGHT))
   {
      m_pRightNeighbor = (CWndPlayerCoordinate*) GetNeighbor(m_pAnchorCoordinate, RIGHT);
      if (m_pRightNeighbor) 
      {
         m_pRightNeighbor->setBitmap(RIGHTARROW);
         m_pRightNeighbor->refresh();
      } 
   }

   if (DoesShipFit(LEFT))
   {
      m_pLeftNeighbor = (CWndPlayerCoordinate*) GetNeighbor(m_pAnchorCoordinate, LEFT);
      if (m_pLeftNeighbor) 
      {
         m_pLeftNeighbor->setBitmap(LEFTARROW);
         m_pLeftNeighbor->refresh();
      }
   }

   if (DoesShipFit(UP))
   {
      m_pUpNeighbor = (CWndPlayerCoordinate*) GetNeighbor(m_pAnchorCoordinate, UP);
      if (m_pUpNeighbor) 
      {
         m_pUpNeighbor->setBitmap(UPARROW);
         m_pUpNeighbor->refresh();
      }
   }

   if (DoesShipFit(DOWN))
   {
      m_pDownNeighbor = (CWndPlayerCoordinate*) GetNeighbor(m_pAnchorCoordinate, DOWN);
      if (m_pDownNeighbor) 
      {
         m_pDownNeighbor->setBitmap(DOWNARROW);
         m_pDownNeighbor->refresh();
      }
   }
}

/****************************************************************
* Function:    GetNeighbor
*
* Purpose      Locates the surrounding coordinates eligible for 
*              either directional arrows or path selection.
*
* Returns      CBattleShipCoordinate* 
****************************************************************/
CBattleShipCoordinate* CWndPlayerBoard::GetNeighbor(CWndPlayerCoordinate* pCoord, int nWhere)
{
   IFUNCTRACE_DEVELOP();

   // This returns a number from 1 to 100 telling us the coordinate that
   //  is the neighbor in a specified direction of the coordinate passed into 
   //  this function
   int nIndex = GetCoordinateIndex(pCoord, nWhere);

   //A little error checking may save us some day.
   if ( (nIndex < 0) || (nIndex > 100)) 
   {
      ITRACE_DEVELOP(" nIndex is bogus ");
      return (0);
   }

   //return a pointer to the found coordinate
   CBattleShipCoordinate* pNeighbor = m_CoordinateArray[nIndex];
   return (pNeighbor);
}

/****************************************************************
* Function:    GetCoordinateIndex
*
* Purpose      This returns a number from 1 to 100 telling us the coordinate that
*              is the neighbor in a specified direction of the coordinate passed into 
*              this function
*
* Returns      int
****************************************************************/
int CWndPlayerBoard::GetCoordinateIndex(CWndPlayerCoordinate* pCoord, int nWhere)
{
   IFUNCTRACE_DEVELOP();
   IPoint pPt = pCoord->GetPoint();

   switch (nWhere)
      {
      case HERE:
         return( (pPt.y()*10) + pPt.x() );
         break;

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
Boolean CWndPlayerBoard::DoesShipFit(int nWhere)
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
   CWndPlayerCoordinate* pCoord = m_pAnchorCoordinate;
   bObstruction = IsObstruction(pCoord, nWhere);
   return ( !bObstruction );
}

/****************************************************************
* Function:    IsObstruction
*
* Purpose      Check for obstruction recursively.
*
* Returns      Boolean
****************************************************************/
Boolean CWndPlayerBoard::IsObstruction(CWndPlayerCoordinate* pCoord, int nWhere)
{
   static int nIndex = 1;
   // we hit an obstruction in this direction, reset index for next 
   // ship and return true
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
   CWndPlayerCoordinate* pNext = (CWndPlayerCoordinate*) GetNeighbor(pCoord, nWhere);
   if ( pNext ) 
   {
      if (IsObstruction(pNext, nWhere))
      {
         nIndex = 1;
         return TRUE;
      }
   }

   return FALSE;
}

/****************************************************************
* Function:    SetShipOnBoard
*
* Purpose      Use selected arrow coordinate to set the direction
*              and place the ship.
*
* Returns      Boolean
****************************************************************/
Boolean CWndPlayerBoard::SetShipOnBoard(CWndPlayerCoordinate* pCoord)
{
   int nWhere;

   // set nwhere by comparing this coord with the neighbors
   if (pCoord == m_pRightNeighbor)
      nWhere = RIGHT;
   else
      if (pCoord == m_pLeftNeighbor) 
         nWhere = LEFT;
   else
      if (pCoord == m_pUpNeighbor)
         nWhere = UP;
   else
      if (pCoord == m_pDownNeighbor)
         nWhere = DOWN;
   
   // selection made so blank out the neighbors first
   if (m_pRightNeighbor && !m_pRightNeighbor->IsOccupied())
   {
      m_pRightNeighbor->setBitmap(BLANK);
      m_pRightNeighbor->refresh();
   }
   if (m_pLeftNeighbor && !m_pLeftNeighbor->IsOccupied())
   {
      m_pLeftNeighbor->setBitmap(BLANK);
      m_pLeftNeighbor->refresh();
   }
   if (m_pUpNeighbor && !m_pUpNeighbor->IsOccupied()) 
   {
      m_pUpNeighbor->setBitmap(BLANK);
      m_pUpNeighbor->refresh();
   }
   if (m_pDownNeighbor && !m_pDownNeighbor->IsOccupied()) 
   {
      m_pDownNeighbor->setBitmap(BLANK);
      m_pDownNeighbor->refresh();
   }
   
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
         m_ixStartingPoint -= pCoord->GetWidth() * 
                              (m_pShipBeingPlaced->GetLength()-1);
   }
   else
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


   m_pShipBeingPlaced->setBitmap(nShipNumber);

   // place the Anchor first then run through all the rest
   pCoord = m_pAnchorCoordinate;
   pCoord->setBitmap(BLANK);
   pCoord->SetShipOnCoordinate(m_pShipBeingPlaced);
   pCoord->refresh();
   for (int i=1; i<m_pShipBeingPlaced->GetLength(); i++)
   {
      CWndPlayerCoordinate* pNextCoord = (CWndPlayerCoordinate*) GetNeighbor(pCoord, nWhere);
      pCoord = pNextCoord;

      // blank out the remaining arrows on the coordinates
      pCoord->SetShipOnCoordinate(m_pShipBeingPlaced);
      pCoord->setBitmap(BLANK);
      pCoord->refresh();
   }

   // move ship button to location of anchor coordinate
   IRectangle rect(IPoint(m_ixStartingPoint, m_iyStartingPoint), 
                   ISize(m_iBitmapWidth, m_iBitmapHeight));
   m_pShipBeingPlaced->moveSizeTo(rect);
   
   m_pRightNeighbor = NULL;
   m_pLeftNeighbor = NULL;
   m_pUpNeighbor = NULL;
   m_pDownNeighbor = NULL;
   
   return (1);
}

/****************************************************************
* Function:    FireOn
*
* Purpose      The board knows about its coordinates via its
*              coordinate array member variable.  Given a cpoint
*              it will take a shot at the coordinate by calling
*              the coordinates FireOn member function.
*
* Returns      Nothing
****************************************************************/
Boolean CWndPlayerBoard::FireOn(IPoint ipoint)
{   
   Boolean isHit;
   int index = ipoint.y() * 10 + ipoint.x();  //calculate the index into the obarray to use

// get the coordinate address from the array  
   CWndPlayerCoordinate* pCoordinate = m_CoordinateArray[index];         

//Take a shot at the selected coordinate
   isHit = pCoordinate->FireOn();

   return isHit;
}


/****************************************************************
* Function:    HideGamePieces
*
* Purpose      Hide the game pieces that are on the player board
*              It would be no fun if you could see them all
*
* Returns      Nothing
****************************************************************/
void CWndPlayerBoard::HideGamePieces()
{
 //Hide the ships
   m_Submarine->show(false);
   m_Carrier->show(false);
   m_PTBoat->show(false);
   m_Destroyer->show(false);
   m_BattleShip->show(false);

//loop thru the mine collection to hide them as well
   this->HideMines();
}


/****************************************************************
* Function:    SinkShip
*
* Purpose      Handles the actions when a ship is sunk
* Returns      Nothing
****************************************************************/
void CWndPlayerBoard::SinkShip()
{
   //Tell the opponent to clear its hit stack. Also,  if the ship is sunk, 
   // we do not want the caller to push anything on the hit stack.  If we 
   // return false,  the stack is reset and the caller starts over again.
   m_pGame->GetOpponent()->ClearHitStack();

   // decrement the number of ships on the board and see if we need to end 
   //  the game
   this->SetNumberShipsLeftToSink();
   if (this->GetNumberShipsLeftToSink() == 0)
      m_pGame->SetGameOver(PLAYERBOARD);

   return;
}

// Opponent - Opponent class
//

#include "opponent.hpp"
#include "w_oppcrd.hpp"
#include <time.h>

/////////////////////////////////////////////////////////////////////////////
// COpponent constructor

COpponent::COpponent(CBattleShipGame* pGame)
{
   m_GuessStack = new stack();
   m_HitStack = new stack();
   m_pGame = pGame; 
}

// COpponent destructor
COpponent::~COpponent()
{
   delete m_GuessStack;
   delete m_HitStack;
}

/*****************************************************
* Function:    ChooseRandomCoord()
* Parms:       None
* Returns:     A IPoint depicting a random coordinate
*              to choose.
*****************************************************/
IPoint COpponent::ChooseRandomCoord()
{
   int n;
   static unsigned long seed=1;
          
   // mod seed with valid values and OR with 1 to prevent 
   // divide-by-zero
   n = (int) (seed % 100);
   n |= 1;
   seed++;
   
   //generate a seed val for the rand()
   srand( ((unsigned)clock()/n) );  

   // pick a value 0 - 99
   n = rand() % 100;

   // decode value into a IPoint
   IPoint cPt;
   cPt.setX(n%10);
   cPt.setY(n/10);

   return(cPt);
}

/*****************************************************
* Function:    ChooseRandomCoord()
* Parms:       UCHAR
* Returns:     A IPoint depicting a random coordinate
*              to choose.
* Notes:       Overload - chooses a random coordinate
*              from the valid neighbors UCHAR.
*****************************************************/
UCHAR COpponent::ChooseRandomCoord(UCHAR ucValid)
{
   // if only one valid direction, return that one
   if (ucValid == RIGHT || ucValid == LEFT || ucValid == UP || ucValid == DOWN)
      return (ucValid);

   // cycle through the bits in 'random' order (tried to take the factor of
   // precedence out of the result)
   int n=0;
   if (ucValid & DOWN)
      n++;
   if (ucValid & LEFT)
      n++;
   if (ucValid & UP)
      n++;
   if (ucValid & RIGHT)
      n++;

   UCHAR ucDir;
   srand((unsigned)(clock() / ucValid));  // generate a seed val for the rand()   //dsb
   ucDir = (rand() % n);                  // generate a random direction value
 
   // now determine the nth bit selected (mapping random ucDir selection to the
   // actual valid bits in the ucValid mask).  e.g 0,1,2,3 --> 1,2,4,8
   int j=0;
   if (ucValid & RIGHT)
      {
      if (j == ucDir) 
         return(RIGHT);
      j++;
      }
   if (ucValid & LEFT)
      {
      if (j == ucDir) 
         return(LEFT);
      j++;
      }
   if (ucValid & UP)
      {
      if (j == ucDir) 
         return(UP);
      j++;
      }
   if (ucValid & DOWN)
      {
      if (j == ucDir) 
         return(DOWN);
      }
      
   return (0);
}
/*****************************************************
* Function:    Initialize
* Parms:       none
* Purpose:     Clears the guess stack for previously
*              guessed IPoint values
* Returns:     Nothing
*****************************************************/
void COpponent::Initialize()  //dsb
{
   m_GuessStack->clear(); 
   m_HitStack->clear(); 

   //flags to see if we are tracking someone in a particular direction
   m_vertical = FALSE;
   m_horizontal = FALSE;

   return;
}


/*****************************************************
* Function:    PlaceShips
* Parms:       none
* Purpose:     Carte blanche command that the game issues
*              telling the opponent to place his ships.
* Returns:     
*****************************************************/
void COpponent::PlaceShips()
{     
   IFUNCTRACE_DEVELOP();

   // place the carrier
   m_pGame->GetOpponentBoard()->SetShipBeingPlaced( m_pGame->GetOpponentBoard()->GetCarrier() );
   IPoint cPnt;
   CWndOpponentCoordinate* pOppCoord;
   for (int i=0; i<m_pGame->GetNumberOfShips(); i++)
   {
      // Opponent randomly "clicks" the opponent board, gets a square, then
      // uses it to fit his ship on. Set the anchor coord, and determine 
      // valid neighbors on board
      UCHAR ucValidDirections = 0;
      while (ucValidDirections == 0)
      {
         cPnt = ChooseRandomCoord();
         pOppCoord = m_pGame->GetOpponentBoard()->GetChosenCoordinate(&cPnt);
         if (!pOppCoord->IsOccupied())
            ucValidDirections = m_pGame->GetOpponentBoard()->FitShipOnBoard(pOppCoord);
      }
      
      ITRACE_DEVELOP(" About to pick a direction in opponent.cpp ");
      // ...pick a direction
      UCHAR ucValid = ChooseRandomCoord(ucValidDirections);

      ITRACE_DEVELOP(" About to set ship on board in opponent.cpp ");
      // Finally, set the ship
      m_pGame->GetOpponentBoard()->SetShipOnBoard(ucValid);

      // setup for next ship
      int nType = m_pGame->GetOpponentBoard()->GetShipBeingPlaced()->GetShipType();
      switch (nType)
         {
         case eCARRIER:
            ITRACE_DEVELOP(" Set ship on board for carrier ");
            m_pGame->GetOpponentBoard()->SetShipBeingPlaced( m_pGame->GetOpponentBoard()->GetBattleShip() );
            ITRACE_DEVELOP(" Finished setting ship on board for carrier ");
            break;

         case eBATTLESHIP:
            ITRACE_DEVELOP(" Set ship on board for battleship ");
            m_pGame->GetOpponentBoard()->SetShipBeingPlaced( m_pGame->GetOpponentBoard()->GetDestroyer() );
            break;

         case eDESTROYER:
            ITRACE_DEVELOP(" Set ship on board for destroyer ");
            m_pGame->GetOpponentBoard()->SetShipBeingPlaced( m_pGame->GetOpponentBoard()->GetSubmarine() );
            break;

         case eSUBMARINE:
            ITRACE_DEVELOP(" Set ship on board for sub ");
            m_pGame->GetOpponentBoard()->SetShipBeingPlaced( m_pGame->GetOpponentBoard()->GetPTBoat() );
            break;
         
         case ePTBOAT:

            ITRACE_DEVELOP(" Set ship on board for about to lay mines ");
            //if (!m_pGame->GetLayMineMode())
            //{
            //   m_pGame->SetGameMode(PLAYGAME);
            //   m_pGame->Player2Setup();
            //}

            break;

         default: 
            break;
         }
   }
}

/*****************************************************
* Function:    PlaceMines
* Parms:       none
* Purpose:     Carte blanche command that the game issues
*              telling the opponent to place his mines.
* Returns:     
*****************************************************/
void COpponent::PlaceMines()
{
   // Opponent randomly "clicks" the opponent board, gets squares, then
   // uses them to set 'n' mines.
   IPoint cPnt;
   CWndOpponentCoordinate* pOppCoord;
   
   for (int i=0; i<m_pGame->GetNumberOfMines(); i++)
   {
      cPnt = ChooseRandomCoord();
      pOppCoord = m_pGame->GetOpponentBoard()->GetChosenCoordinate(&cPnt);

      // keep choosing until empty square
      while (pOppCoord->IsOccupied())
      {
         cPnt = ChooseRandomCoord();
         pOppCoord = m_pGame->GetOpponentBoard()->GetChosenCoordinate(&cPnt);
      }

      /****************************************************************
      * Create some invisible mines by a parm of FALSE
      ****************************************************************/
      // create a new mine and stick it on the list
      CMine* pMine = m_pGame->GetOpponentBoard()->CreateNewMine(cPnt, false);

      m_pGame->GetOpponentBoard()->SetMinesLeft( m_pGame->GetNumberOfMines() - (i+1));
      pOppCoord->SetShipOnCoordinate(pMine);
   }

//   m_pGame->SetGameMode(PLAYGAME);
//   m_pGame->Player2Setup();

   return;
}



/****************************************************************
* Function:    isCoordAvailable
*
* Purpose      Determines if a coordinate in the given direction
*              relative to a given IPoint is available
*
* Returns      Boolean 
****************************************************************/
Boolean COpponent::isCoordAvailable(int nWhere, IPoint* cPt)
{  
   Boolean isValid = FALSE;
   IPoint cp;

   //save the passed in values   
   int x=cPt->x();
   int y=cPt->y();
   
   //initialize an IPoint value
   cp.setX(0);
   cp.setY(0);
                                    
   // Get the direction passed
   switch (nWhere)                              
      {
      case RIGHT:
         if (x < 9)  // do not go off the board on the right
         {
            cp.setX(x + 1);
            cp.setY(y);
            if(!m_GuessStack->AlreadyGuessed(m_GuessStack, cp))
               isValid = TRUE;
         }
         else 
            cp = IPoint(9, y);  //not valid so set cp to the original value coming in
         break;

      case LEFT:
         if (x > 0)  // do not go off the board on the left
         {
            cp.setX(x - 1);
            cp.setY(y);
            if(!m_GuessStack->AlreadyGuessed(m_GuessStack, cp)) 
               isValid = TRUE;
         }
         else 
            cp = IPoint(0, y);
         break;

      case UP: 
         if (y > 0)  // do not go off the board on the top
         {
            cp.setX(x);
            cp.setY(y - 1);
            if(!m_GuessStack->AlreadyGuessed(m_GuessStack, cp)) 
               isValid = TRUE;
         }
         else 
            cp = IPoint(x, 0);
         break;

      case DOWN: 
         if (y < 9)  // do not go off the board on the bottom
         {
            cp.setX(x);
            cp.setY(y + 1);
            if(!m_GuessStack->AlreadyGuessed(m_GuessStack, cp)) 
               isValid = TRUE;
         }
         else 
            cp = IPoint(x, 9);
         break;
      }

//These are automatically incremented by this function and returned in their altered
// state to the caller.
      cPt->setX(cp.x());
      cPt->setY(cp.y());

   return ( isValid );
}

/*****************************************************
* Function:    VerticalSmartShot
* Parms:       IPoint
* Purpose:     Tries to shoot at a coordinate above the last hit
*              passed to it by the IPoint.  If the above coord is not
*              available, (already guessed) we will try to shoot in the
*              the other vertical direction.
*
* Returns:     Nothing
*****************************************************/
void COpponent::VerticalSmartShot(IPoint cpoint)  //dsb
{
   int i;
   
   if(isCoordAvailable(UP, &cpoint))
   {
      // Fire at the available coordinate above where you currently are
      if(m_pGame->GetPlayerBoard()->FireOn(cpoint))
         PushHit(cpoint);
   }
   else  // must start looking in the down direction
   {
      i = 0;
      while(i < 10)  //Can't have more than 10 squares in the game
      {     
         //find the the first open square downwards and fire at it
         if(isCoordAvailable(DOWN, &cpoint))  
         {
            if (m_pGame->GetPlayerBoard()->FireOn(cpoint))
               PushHit(cpoint);
            break;
         }
         i++;
      }  
      if( i == 10)  // no open squares at this point
      {
         m_vertical = FALSE;
      }
   }
   m_GuessStack->push( cpoint );  //remember this last guess
}

/*****************************************************
* Function:    HorizontalSmartShot
* Parms:       IPoint
* Purpose:     Tries to shoot at a coordinate to the right of the last hit
*              passed to it by the IPoint.  If the above coord is not
*              available, (already guessed) we will try to shoot in the
*              the other horizontal direction.
*
* Returns:     Nothing
*****************************************************/
void COpponent::HorizontalSmartShot(IPoint cpoint)  //dsb
{
   int i;
   
   if(isCoordAvailable(RIGHT, &cpoint))
   {
      // Fire at the available coordinate to the right where you currently are
      if (m_pGame->GetPlayerBoard()->FireOn(cpoint))
         PushHit(cpoint);
   }
   else  // must start looking in the down direction
   {
      i = 0;
      while(i < 10)  //Can't have more than 10 squares in the game
      {     
         //find the the first open square to the left and fire at it
         if(isCoordAvailable(LEFT, &cpoint))  
         {
            if (m_pGame->GetPlayerBoard()->FireOn(cpoint))
               PushHit(cpoint);
            break;
         }
         i++;
      }
      if( i == 10)  // no open squares at this point
      {
         m_horizontal = FALSE;
      }
   }
   m_GuessStack->push( cpoint );  //remember this last guess
}

/*****************************************************
* Function:    TakeShot
* Parms:       none
* Purpose:     Will fire a shot at a coord that has not 
*              already been picked.  
* Returns:     
*****************************************************/
IPoint COpponent::TakeShot()
{     
   Boolean isHit=FALSE;
   IPoint cpoint;

   //initialize these to zeros
   cpoint.setX(0);
   cpoint.setY(0);
            
   if(m_pGame->isSmartOpponent())
   {
      if(SmartShot())    //If there is no smart shot take a regular one!
      {
         //Call the game to decide whether to switch turns or give me another
         //  turn based on a penalty. The opponent fires on the PLAYERBOARD!
         m_pGame->DecidePlayerTurn(PLAYERBOARD);
         return cpoint;
      }
   }
   int i=0;       //prevent an endless loop!!
   while(i<3000)  //keep trying till we find one we haven't guessed yet.
   {              
      cpoint = ChooseRandomCoord();             //get a random coord  
      
   // have we guessed this one yet?  //dsb
      if(!m_GuessStack->AlreadyGuessed(m_GuessStack, cpoint)) 
      {
         m_GuessStack->push( cpoint );           //no - save the guess
         break;
      }
      i++;  //loop back to try another guess
   }  
   
   //See if we are missing shots!
   if (i >=3000)
      IMessageBox(m_pGame).show("The computer could not find a guess on the board!", IMessageBox::information);
      
   isHit = m_pGame->GetPlayerBoard()->FireOn(cpoint);
   
   //If we get a hit,  save it on the hit stack.
   if (isHit)
   {
      ITRACE_DEVELOP( "got a hit - push it on the stack");
      fflush(stdout);
      PushHit(cpoint);
   }

   //Call the game to decide whether to switch turns or give me another
   //  turn based on a penalty. The opponent fires on the PLAYERBOARD!
   m_pGame->DecidePlayerTurn(PLAYERBOARD);
   
   return cpoint; 
}

/*****************************************************
* Function:    SmartShot
* Parms:       none
* Purpose:     Will try to be intelligent about firing at
*              the player board.  For example,  If we are currently tracking
*              someone vertically, continue in that direciton. If we are
*              not tracking someone,  return to the caller to allow it to
*              proceed to fire a random shot.  This function uses a hitstack
*              to keep track of its progress.
*
* Returns:     TRUE if a hit was registered
*****************************************************/
Boolean COpponent::SmartShot() //dsb
{   
   IFUNCTRACE_DEVELOP();

   IPoint cp, cpDir;
   Boolean   isHit;
   
   cp = m_HitStack->top();  //get the last IPoint from the hitstack

   //are we tracking someone vertically?
   if(m_vertical)    
   {
      VerticalSmartShot(cp);  //This will take shots so get out when it is done
      return(TRUE);
   }

   //are we tracking someone horizontally?
   if(m_horizontal)  
   {
      HorizontalSmartShot(cp);   //This will take shots so get out when it is done
      return(TRUE);
   }

   //if there is nothing on the hit stack yet,  allow the caller
   //  to take a random shot.  We do this by returning false
   if (cp.x() == -1)
   {
      ITRACE_DEVELOP( "nothing on the hit stack");
      fflush(stdout);
      return(FALSE);  //allow the caller to take a random shot 
   }
   else
   {  
      ITRACE_DEVELOP( "Got a hit in the smart shot");
      fflush(stdout);
      // At this point,  our last shot was a hit.  We are trying to establish
      //  a direction by picking a shot in another direction.
      cpDir = cp;
      if(isCoordAvailable(RIGHT, &cpDir))  
      {
         isHit = m_pGame->GetPlayerBoard()->FireOn(cpDir);
         if (isHit)
         {
            PushHit(cpDir);         //save the hit
            m_horizontal = TRUE;    //got a second horizontal hit so record that fact
         }
      m_GuessStack->push( cpDir );  //save the guess so we do not choose it again later
      return (TRUE);
      }

      cpDir = cp;
      if(isCoordAvailable(LEFT, &cpDir))  
         {
            isHit = m_pGame->GetPlayerBoard()->FireOn(cpDir);
            if (isHit)
            {
               PushHit(cpDir);       //save the hit
               m_horizontal = TRUE;  //got a second horizontal hit so record that fact
            }
         m_GuessStack->push( cpDir ); //save the guess so we do not choose it again later
         return (TRUE);
         }

      cpDir = cp;
      if(isCoordAvailable(UP, &cpDir))  
         {
            isHit = m_pGame->GetPlayerBoard()->FireOn(cpDir);
            if (isHit)
            {
               PushHit(cpDir);       //save the hit
               m_vertical = TRUE;    //got a second vertical hit so record that fact
            }
         m_GuessStack->push( cpDir ); //save the guess so we do not choose it again later
         return (TRUE);
         }

      cpDir = cp;
      if(isCoordAvailable(DOWN, &cpDir))  
         {
            isHit = m_pGame->GetPlayerBoard()->FireOn(cpDir);
            if (isHit)
            {
               PushHit(cpDir);      //save the hit
               m_vertical = TRUE;   //got a second horizontal hit so record that fact
            }
         m_GuessStack->push( cpDir );   //save the guess so we do not choose it again later
         }
      else
      {
      //If we reach this point and none of the coords were available,  we want to
      // return false so a random guess can take place.
//    if(cpDir == cp)
         ITRACE_DEVELOP( "No coords were available - taking dumb shot");
         fflush(stdout);
         return FALSE;
      }
   }
   return TRUE;
}
   
   
/*****************************************************
* Function:    ClearHitStack
* 
* Purpose:     Will clear the values from the hit stack
* Returns:     Nothing
*****************************************************/
void COpponent::ClearHitStack()
{
   IFUNCTRACE_DEVELOP();

   m_HitStack->clear(); 

   //flags to see if we are tracking someone in a particular direction
   m_vertical = FALSE;
   m_horizontal = FALSE;

   return;
}
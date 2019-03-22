// CBattleShipBoard - BattleShip board base class.
//

#include "battle.h"
#include "batshpgm.hpp"



/****************************************************************
* CBattleShipBoard - constructor
****************************************************************/
CWndBattleShipBoard::CWndBattleShipBoard(CBattleShipGame* pGame, 
                                          unsigned long id, 
                                          IWindow* parent) 
      : ICanvas(id, parent, parent),
        CBattleShipBoard(pGame)
{
   m_pGame = pGame;
   m_pSound = pGame->getSoundPointer();

//Instantiate a mine array - this is a bag collection of mines
   MineCollectionType  m_MineArray;
}

/****************************************************************
* CBattleShipBoard - destructor
****************************************************************/
CWndBattleShipBoard::~CWndBattleShipBoard()
{
}
 
/****************************************************************
* Function:    Initialize
*
* Purpose      The carrier is the first ship that is placed by the
*              player in the game.  We will set a variable accordingly.
*              We want to register how many ships are used in the game
*              and tell the place which ship to place first.
*              
*
* Returns      nothing
****************************************************************/
void CWndBattleShipBoard::Initialize()
{
   m_pShipBeingPlaced = m_Carrier;
   m_bPenalty = false;
   m_nNumShipsLeftToSink = m_pGame->GetNumberOfShips();

   // This is the first message the player ought to see when
   //  a new game begins
   m_pGame->SetInfoareaMessage("Place Aircraft Carrier.");
}

/****************************************************************
* Function:    CreateShips
*
* Purpose      Instantiate all the ships used by the game.
*
* Returns      nothing
****************************************************************/
void CWndBattleShipBoard::CreateShips()
{
   m_Submarine = new CSubmarine(m_pGame, m_pSound, 304, this, 
                                HSUB);
   m_Carrier = new CCarrier(m_pGame,m_pSound, 305, this,
                                HCARRIER); 
   m_PTBoat = new CPTBoat(m_pGame,m_pSound, 306, this,
                                HPTBOAT);
   m_Destroyer = new CDestroyer(m_pGame,m_pSound, 307, this,
                                HDESTROY);
   m_BattleShip = new CBattleShip(m_pGame,m_pSound, 308, this,
                                HBATTLE);
}

/****************************************************************
* Function:    DeleteShips
*
* Purpose      Destroy what thou creates.
*
* Returns      nothing
****************************************************************/
void CWndBattleShipBoard::DeleteShips()
{
   if (m_Submarine)
      delete m_Submarine;
   if (m_Carrier)
      delete m_Carrier;
   if (m_PTBoat)
      delete m_PTBoat;
   if (m_Destroyer)
      delete m_Destroyer;
   if (m_BattleShip)
      delete m_BattleShip;
}

/****************************************************************
* Function:    IsValidCoordinate
*
* Purpose      When the player is in the process of setting ships
*              on the board,  arrows will be displayed indicating 
*              valid directions for the ship to be placed on the 
*              board.  The player coordinate class will call 
*              this function to determine whether of not
*              the player is clicking on one of these arrow bitmap
*              coordinates or not.  
*
* Returns      nothing
****************************************************************/
Boolean CWndBattleShipBoard::IsValidCoordinate(CBattleShipCoordinate* pCoord)
{
   if (pCoord == m_pRightNeighbor)
      return true;
   if (pCoord == m_pLeftNeighbor)
      return true;
   if (pCoord == m_pUpNeighbor)
      return true;
   if (pCoord == m_pDownNeighbor)
      return true;
      
   return false;
}

/****************************************************************
* Function:    DeleteMines
*
* Purpose      We are storing mines in a collection class BAG.
*              We need to iterate through the BAG and delete each
*              instance of the mine that we find.  Finally, tell 
*              the BAG that there are no more elements in it.
*
*              I left some debugging code in here.
*
* Returns      nothing
****************************************************************/
void CWndBattleShipBoard::DeleteMines()
{  
   IFUNCTRACE_DEVELOP();

   if (m_pGame->GetLayMineMode())
   {
      MineCollectionType::Cursor cursor(m_MineArray);

      //Loop through the BAG deleting instances of Mines that we find      
      for ( cursor.setToFirst(); cursor.isValid(); cursor.setToNext() )
      {
         MineObject pMine = m_MineArray.elementAt( cursor );
         if ( pMine ) 
            delete pMine;
      }

      //Tell the BAG that it is now empty
      m_MineArray.removeAll();
   } 
   return;
}


/****************************************************************
* Function:    CreateNewMine
*
* Purpose      Creates a new mine object at the passed in coordinates.  
*              These can be created visible or invisible depending on the
*              passed in variable.  This function will also add the mine to
*              the mine array that corresponds to the board that is in use.
*
* Returns      A pointer to the newly created mine.
****************************************************************/
CMine* CWndBattleShipBoard::CreateNewMine(IPoint pPoint, Boolean bVisible) 
{ 
   IFUNCTRACE_DEVELOP();

   pPoint.setX(pPoint.x() * COORDWIDTH);
   pPoint.setY(pPoint.y() * COORDHEIGHT);

   IRectangle irect = IRectangle( pPoint, ISize(COORDWIDTH,COORDHEIGHT));

   MineObject pMine = new CMine( m_pGame,
                                 m_pSound,
                                 304, 
                                 this, 
                                 MINE,
                                 irect,
                                 bVisible);
   if ( pMine ) 
      m_MineArray.add(pMine);

   return pMine;
}


/****************************************************************
* Function:    HideMines
*
* Purpose      This loops throught collection class BAG telling each
*              mine to hide.
*
* Returns      Nothing
****************************************************************/
void CWndBattleShipBoard::HideMines()
{  
   IFUNCTRACE_DEVELOP();

   if (m_pGame->GetLayMineMode())
   {
      MineCollectionType::Cursor cursor(m_MineArray);
      
      for ( cursor.setToFirst(); cursor.isValid(); cursor.setToNext() )
      {
         MineObject pMine = m_MineArray.elementAt( cursor );
         if ( pMine ) 
            pMine->show(false);
      }
   } 
   return;
}


/****************************************************************
* Function:    HitMine
*
* Purpose      Since each board has to do essentially the same thing
*              when a mine is hit,  it makes sense to put that functionality
*              here.  We want to display the appropriate message on the screen
*              depending on who called us and set a variable indicating whether
*              this particular board is registering a penalty or not.
*
* Returns      Nothing
****************************************************************/
void CWndBattleShipBoard::HitMine(int a_caller)
{
   IString msg;

   //Depending on who called us, make sure to display the correct message
   if ( a_caller == PLAYERBOARD ) 
   {
      msg = "Opponent hit a mine. You get an extra turn.";
   }
   else 
   {
      msg = "You hit a mine. Your opponent will get an extra turn.";
   }

   // if there's no penalty against the board,
   // one is lodged and someone loses a turn
   if (!this->GetPenalty())
   {
      IMessageBox(m_pGame).show(msg, IMessageBox::information);
      this->SetPenalty(true);
   }
//   else
//   {
//      m_pGame->SetInfoareaMessage(msg2);
//      this->SetPenalty(false);
//   }

   return;
} 

/****************************************************************
* Function:    CheckForPenalty
*
* Returns      true  - a penalty is registered for this board
*              false - no penalty is registered here.
****************************************************************/
Boolean CWndBattleShipBoard::CheckForPenalty()
{
   if (this->GetPenalty())
      return true;
   else
      return false;
} 

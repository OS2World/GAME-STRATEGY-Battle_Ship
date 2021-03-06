/*******************************************************************************
* FILE NAME: Options.cpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Class implementation of the class:                                         *
*     Options                                                                  *
* ---------------------------------------------------------------------------- *
* Warning: This file was generated by the VisualAge C++ Visual Builder.        *
* Modifications to this source file will be lost when the part is regenerated. *
*******************************************************************************/

//Using visual builder was the easiest way for me to generate the options
// notebook.  I am not crazy about the code here but it does the trick.


#ifndef _IFRAME_
#include <iframe.hpp>
#endif

#ifndef _ICANVAS_
#include <icanvas.hpp>
#endif

#ifndef _ICOLOR_
#include <icolor.hpp>
#endif

#ifndef _INOTEBK_
#include <inotebk.hpp>
#endif

#ifndef _IRECT_
#include <irect.hpp>
#endif

#ifndef _IPOINT_
#include <ipoint.hpp>
#endif

#ifndef _IFONT_
#include <ifont.hpp>
#endif

#ifndef _IVBNBKPG_
#include <ivbnbkpg.hpp>
#endif

#ifndef _ICHECKBX_
#include <icheckbx.hpp>
#endif

#ifndef _ISPINNUM_
#include <ispinnum.hpp>
#endif

#ifndef _ISTATTXT_
#include <istattxt.hpp>
#endif

#ifndef _IBMPCTL_
#include <ibmpctl.hpp>
#endif

#ifndef _IRESLIB_
#include <ireslib.hpp>
#endif

#ifndef _IENTRYFD_
#include <ientryfd.hpp>
#endif

#ifndef _IICONCTL_
#include <iiconctl.hpp>
#endif

#ifndef _IPUSHBUT_
#include <ipushbut.hpp>
#endif

#ifndef _INOTIFEV_
#include <inotifev.hpp>
#endif

#ifndef _IOBSERVR_
#include <iobservr.hpp>
#endif

#ifndef _ISTDNTFY_
#include <istdntfy.hpp>
#endif

#ifndef _OPTIONS_
#include "Options.hpp"
#endif

#ifndef _IVBDEFS_
#include <ivbdefs.h>
#endif

#ifndef _ITRACE_
#include <itrace.hpp>
#endif





//*****************************************************************************
// Class definition for OptionsConn0
//*****************************************************************************
class OptionsConn0 : public IObserver, public IStandardNotifier {
public:
   virtual  ~OptionsConn0(){};

   //---------------------------------------------------------------------------
   // public member functions
   //---------------------------------------------------------------------------
   void initialize(IPushButton * aSource, IFrameWindow * aTarget)
      {source = aSource; target = aTarget; enableNotification(); };

protected:
   //---------------------------------------------------------------------------
   // protected member functions
   //---------------------------------------------------------------------------
   IObserver & dispatchNotificationEvent(const INotificationEvent & anEvent)
      {
      if (anEvent.notificationId() == IPushButton::buttonClickId)
         {
         IFUNCTRACE_DEVELOP();
         ITRACE_DEVELOP(" firing connection : CB_CANCEL(buttonClickEvent) to W_OPTIONS(close))");
         try {target->close();}
         catch (IException& exc) {};
         }
      return(*this);
      };

private:
   //---------------------------------------------------------------------------
   // private member data
   //---------------------------------------------------------------------------
   IPushButton * source;
   IFrameWindow * target;

};   //OptionsConn0


//*****************************************************************************
// Class definition for OptionsConn1 - This is the OK button
//*****************************************************************************
class OptionsConn1 : public IObserver, public IStandardNotifier {
public:
   OptionsConn1(Options* aOptions){pOptions = aOptions;};
   virtual  ~OptionsConn1(){};

   //---------------------------------------------------------------------------
   // public member functions
   //---------------------------------------------------------------------------
   void initialize(IPushButton * aSource, IFrameWindow * aTarget)
      {source = aSource; target = aTarget; enableNotification(); };

protected:
   //---------------------------------------------------------------------------
   // protected member function for the OK Button
   //---------------------------------------------------------------------------
   IObserver & dispatchNotificationEvent(const INotificationEvent & anEvent)
      {
      if (anEvent.notificationId() == IPushButton::buttonClickId)
         {
         IFUNCTRACE_DEVELOP();
         ITRACE_DEVELOP(" firing connection : CB_OK(buttonClickEvent) to W_OPTIONS(customLogic, \"Saves BattleShip Options\"))");
         try {codeSnippet(&anEvent);}
         catch (IException& exc) {};
         }
      return(*this);
      };

private:
   //---------------------------------------------------------------------------
   // private member functions for the OK button
   //---------------------------------------------------------------------------
   int codeSnippet(const INotificationEvent* event)
   {
      pOptions->saveOptions();
      target->close();
      return(1);
   };

   //---------------------------------------------------------------------------
   // private member data and functions
   //---------------------------------------------------------------------------
   IPushButton * source;
   IFrameWindow * target;
   Options* pOptions;

};   //OptionsConn1


//#pragma export (Options::readyId)
const INotificationId Options::readyId = "Options::readyId";
//------------------------------------------------------------------------------
// Options :: defaultFramingSpec
//------------------------------------------------------------------------------
//#pragma export (Options::defaultFramingSpec())
const IRectangle Options::defaultFramingSpec()
{
   return(IRectangle(IPoint(30, IWindow::desktopWindow()->size().height()-36-309),ISize(396, 309)));
}


//------------------------------------------------------------------------------
// Options :: defaultStyle
//------------------------------------------------------------------------------
//#pragma export (Options::defaultStyle())
const IFrameWindow::Style Options::defaultStyle()
{
   return(IFrameWindow::defaultStyle());
}


//------------------------------------------------------------------------------
// Options :: defaultTitle
//------------------------------------------------------------------------------
//#pragma export (Options::defaultTitle())
IString Options::defaultTitle()
{
   return("BattleShip Options");
}


//------------------------------------------------------------------------------
// Options :: Options
//------------------------------------------------------------------------------
//#pragma export (Options::Options(unsigned long, Window*, IWindow*, const IRectangle&, const IFrameWindow::Style&, const char*))
Options::Options(
      unsigned long id, 
      IWindow* parent, 
      IWindow* owner, 
      const IRectangle& rect, 
      const IFrameWindow::Style& style, 
      const char* title)
   : IFrameWindow(id, parent, owner, rect, style, title)
{

//Save a pointer to the game object so we can let it know about the
//  options we are setting here.
   m_pGame = (CBattleShipGame*)owner;

   iCanvas = new ICanvas(
      IC_FRAME_CLIENT_ID, 
      this, 
      this, 
      IRectangle());
   iNB_OPTIONS = new INotebook(
      id+WNDOFFSET_Options_NB_OPTIONS, 
      iCanvas, 
      iCanvas, 
      IRectangle(IPoint(0,46),ISize(393, 237)));
   iCANVAS_MINE = new ICanvas(
      id+WNDOFFSET_Options_CANVAS_MINE, 
      iNB_OPTIONS, 
      iNB_OPTIONS, 
      IRectangle());
   iCK_MINES = new ICheckBox(
      id+WNDOFFSET_Options_CK_MINES, 
      iCANVAS_MINE, 
      iCANVAS_MINE, 
      IRectangle(IPoint(61,89),ISize(113, 19)), 
      ICheckBox::defaultStyle() | IControl::tabStop | IControl::group);
   iSPIN_NUMBER_OF_MINES = new INumericSpinButton(
      id+WNDOFFSET_Options_SPIN_NUMBER_OF_MINES, 
      iCANVAS_MINE, 
      iCANVAS_MINE, 
      IRectangle(IPoint(217,53),ISize(57, 20)), 
      INumericSpinButton::defaultStyle() & ~IBaseSpinButton::readOnly | IControl::tabStop | IControl::group);
   iST_NUMBER_OF_MINES = new IStaticText(
      id+WNDOFFSET_Options_ST_NUMBER_OF_MINES, 
      iCANVAS_MINE, 
      iCANVAS_MINE, 
      IRectangle(IPoint(61,53),ISize(146, 31)), 
      IStaticText::defaultStyle() & ~IControl::group & ~IControl::tabStop);
   iBITMAP_MINE = new IBitmapControl(
      id+WNDOFFSET_Options_BITMAP_MINE, 
      iCANVAS_MINE, 
      iCANVAS_MINE, 
      IResourceId(2002, IDynamicLinkLibrary("battle")), 
      IRectangle(IPoint(6,112),ISize(30, 30)), 
      IBitmapControl::defaultStyle() & ~IControl::group);
   iTB_MINES = new IVBNotebookPage(iNB_OPTIONS, INotebook::PageSettings::autoPageSize | INotebook::PageSettings::statusTextOn | INotebook::PageSettings::majorTab, iCANVAS_MINE);
   iCANVAS_SOUND = new ICanvas(
      id+WNDOFFSET_Options_CANVAS_SOUND, 
      iNB_OPTIONS, 
      iNB_OPTIONS, 
      IRectangle());
   iCHK_SOUND = new ICheckBox(
      id+WNDOFFSET_Options_CHK_SOUND, 
      iCANVAS_SOUND, 
      iCANVAS_SOUND, 
      IRectangle(IPoint(46,77),ISize(105, 19)), 
      ICheckBox::defaultStyle() | ICheckBox::autoSelect | IControl::group | IControl::tabStop);
   iST_SOUNDTEXT = new IStaticText(
      id+WNDOFFSET_Options_ST_SOUNDTEXT, 
      iCANVAS_SOUND, 
      iCANVAS_SOUND, 
      IRectangle(IPoint(46,20),ISize(260, 49)));
   iBITMAP_SOUND = new IBitmapControl(
      id+WNDOFFSET_Options_BITMAP_SOUND, 
      iCANVAS_SOUND, 
      iCANVAS_SOUND, 
      IResourceId(2003, IDynamicLinkLibrary("battle")), 
      IRectangle(IPoint(6,104),ISize(30, 30)));
   iNBTAB_SOUND = new IVBNotebookPage(iNB_OPTIONS, INotebook::PageSettings::autoPageSize | INotebook::PageSettings::statusTextOn | INotebook::PageSettings::majorTab, iCANVAS_SOUND);
   iCANVAS_PLAYER = new ICanvas(
      id+WNDOFFSET_Options_CANVAS_PLAYER, 
      iNB_OPTIONS, 
      iNB_OPTIONS, 
      IRectangle());
   iST_ENTERNAME = new IStaticText(
      id+WNDOFFSET_Options_ST_ENTERNAME, 
      iCANVAS_PLAYER, 
      iCANVAS_PLAYER, 
      IRectangle(IPoint(23,65),ISize(93, 17)));
   iEF_PLAYER_NAME = new IEntryField(
      id+WNDOFFSET_Options_EF_PLAYER_NAME, 
      iCANVAS_PLAYER, 
      iCANVAS_PLAYER, 
      IRectangle(IPoint(125,65),ISize(161, 21)), 
      IEntryField::defaultStyle() | IControl::group | IControl::tabStop);
   iIconControl1 = new IIconControl(
      id+WNDOFFSET_Options_IconControl1, 
      iCANVAS_PLAYER, 
      iCANVAS_PLAYER, 
      IResourceId(3001, IDynamicLinkLibrary("battle")), 
      IRectangle(IPoint(6,104),ISize(30, 30)));
   iNBTAB_PLAYER = new IVBNotebookPage(iNB_OPTIONS, INotebook::PageSettings::autoPageSize | INotebook::PageSettings::statusTextOn | INotebook::PageSettings::majorTab, iCANVAS_PLAYER);
   iCANVAS_MISC = new ICanvas(
      id+WNDOFFSET_Options_CANVAS_MISC, 
      iNB_OPTIONS, 
      iNB_OPTIONS, 
      IRectangle());
   iCHK_SMARTOPPONENT = new ICheckBox(
      id+WNDOFFSET_Options_CHK_SMARTOPPONENT, 
      iCANVAS_MISC, 
      iCANVAS_MISC, 
      IRectangle(IPoint(47,75),ISize(145, 19)));
   iSPIN_NUMBER_OF_TURNS = new INumericSpinButton(
      id+WNDOFFSET_Options_SPIN_NUMBER_OF_TURNS, 
      iCANVAS_MISC, 
      iCANVAS_MISC, 
      IRectangle(IPoint(190,44),ISize(57, 19)), 
      INumericSpinButton::defaultStyle() & ~IBaseSpinButton::readOnly | IControl::tabStop | IControl::group);
   iST_TURNSROUND = new IStaticText(
      id+WNDOFFSET_Options_ST_TURNSROUND, 
      iCANVAS_MISC, 
      iCANVAS_MISC, 
      IRectangle(IPoint(47,31),ISize(130, 35)));
   iICON_MISC = new IIconControl(
      id+WNDOFFSET_Options_ICON_MISC, 
      iCANVAS_MISC, 
      iCANVAS_MISC, 
      IResourceId(3002, IDynamicLinkLibrary("battle")), 
      IRectangle(IPoint(6,104),ISize(30, 30)));
   iNBTAB_MISC = new IVBNotebookPage(iNB_OPTIONS, INotebook::PageSettings::autoPageSize | INotebook::PageSettings::statusTextOn | INotebook::PageSettings::majorTab, iCANVAS_MISC);
   iCB_OK = new IPushButton(
      id+WNDOFFSET_Options_CB_OK, 
      iCanvas, 
      iCanvas, 
      IRectangle(IPoint(6,10),ISize(71, 26)), 
      IPushButton::defaultStyle() | IPushButton::defaultButton);
   iCB_CANCEL = new IPushButton(
      id+WNDOFFSET_Options_CB_CANCEL, 
      iCanvas, 
      iCanvas, 
      IRectangle(IPoint(92,10),ISize(71, 26)));

   //Instantiate the Cancel button
   conn0 = new OptionsConn0();

   //Instantiate the OK button
   conn1 = new OptionsConn1(this);

   this->setFocus();
   this->setClient(iCanvas);
   iCanvas->setBackgroundColor(IColor(IColor::paleGray));
   iNB_OPTIONS->setTabShape(INotebook::rounded);
   iNB_OPTIONS->setMajorTabSize(ISize(60, 25));
   iNB_OPTIONS->setPageBackgroundColor(IColor(IColor::paleGray));
   iNB_OPTIONS->setOrientation(INotebook::backpagesRightTabsTop);
   iNB_OPTIONS->setMinorTabBackgroundColor(IColor(IColor::paleGray));
   iNB_OPTIONS->setTabTextAlignment(INotebook::center);
   iNB_OPTIONS->setFont(IFont("System VIO", 10).setBold(false).setItalic(false).setUnderscore(false).setStrikeout(false).setOutline(false));
   iNB_OPTIONS->setMajorTabBackgroundColor(IColor(IColor::paleGray));
   iNB_OPTIONS->setBinding(INotebook::spiral);
   iNB_OPTIONS->setStatusTextAlignment(INotebook::right);
   iTB_MINES->setTabText("~Mines");
   iTB_MINES->setStatusText("Mine Options");
   iCANVAS_MINE->setMinimumSize(ISize(318, 141));
   iCANVAS_MINE->setBackgroundColor(IColor(IColor::paleGray));
   iCK_MINES->select(true);
   iCK_MINES->setText("Lay Mines?");
   iSPIN_NUMBER_OF_MINES->setAlignment(IBaseSpinButton::right);
   iSPIN_NUMBER_OF_MINES->setRange(IRange(0, 15));
   iSPIN_NUMBER_OF_MINES->setValue(1);
   iST_NUMBER_OF_MINES->setAlignment(IStaticText::topLeftWrapped);
   iST_NUMBER_OF_MINES->setText("Number of mines to place (1 - 15)");
   iNBTAB_SOUND->setTabText("~Sound");
   iNBTAB_SOUND->setStatusText("Sound Options");
   iCANVAS_SOUND->setMinimumSize(ISize(100, 100));
   iCANVAS_SOUND->setBackgroundColor(IColor(IColor::paleGray));
   iCHK_SOUND->select(true);
   iCHK_SOUND->setText("Sound On?");
   iST_SOUNDTEXT->setAlignment(IStaticText::topLeftWrapped);
   iST_SOUNDTEXT->setText("For this option to work,  you must have an OS/2 compatible sound card installed.");
   iNBTAB_PLAYER->setTabText("~Player");
   iNBTAB_PLAYER->setStatusText("Player information");
   iCANVAS_PLAYER->setMinimumSize(ISize(100, 100));
   iCANVAS_PLAYER->setBackgroundColor(IColor(IColor::paleGray));
   iST_ENTERNAME->setAlignment(IStaticText::topLeftWrapped);
   iST_ENTERNAME->setText("Player name");
   iNBTAB_MISC->setTabText("M~isc");
   iNBTAB_MISC->setStatusText("Miscellaneous game options");
   iCANVAS_MISC->setMinimumSize(ISize(100, 100));
   iCANVAS_MISC->setBackgroundColor(IColor(IColor::paleGray));
   iCHK_SMARTOPPONENT->select(true);
   iCHK_SMARTOPPONENT->setText("Smart Opponent");
   iSPIN_NUMBER_OF_TURNS->setAlignment(IBaseSpinButton::right);
   iSPIN_NUMBER_OF_TURNS->setRange(IRange(1, 5));
   iSPIN_NUMBER_OF_TURNS->setValue(1);
   iST_TURNSROUND->setAlignment(IStaticText::topLeftWrapped);
   iST_TURNSROUND->setText("Number of turns per round");
   iCB_OK->setText("~Ok");
   iCB_CANCEL->setText("~Cancel");

   getOptions();

}     //end constructor


//------------------------------------------------------------------------------
// Options :: ~Options
//------------------------------------------------------------------------------
//#pragma export (Options::~Options())
Options::~Options()
{
   conn0->stopHandlingNotificationsFor(*iCB_CANCEL);
   conn1->stopHandlingNotificationsFor(*iCB_OK);

   delete conn0;
   delete conn1;


   delete iCanvas;
   delete iNB_OPTIONS;
   delete iTB_MINES;
   delete iCANVAS_MINE;
   delete iCK_MINES;
   delete iSPIN_NUMBER_OF_MINES;
   delete iST_NUMBER_OF_MINES;
   delete iBITMAP_MINE;
   delete iNBTAB_SOUND;
   delete iCANVAS_SOUND;
   delete iCHK_SOUND;
   delete iST_SOUNDTEXT;
   delete iBITMAP_SOUND;
   delete iNBTAB_PLAYER;
   delete iCANVAS_PLAYER;
   delete iST_ENTERNAME;
   delete iEF_PLAYER_NAME;
   delete iIconControl1;
   delete iNBTAB_MISC;
   delete iCANVAS_MISC;
   delete iCHK_SMARTOPPONENT;
   delete iSPIN_NUMBER_OF_TURNS;
   delete iST_TURNSROUND;
   delete iICON_MISC;
   delete iCB_OK;
   delete iCB_CANCEL;
}

//------------------------------------------------------------------------------
// Options :: initializePart
//------------------------------------------------------------------------------
//#pragma export (Options::initializePart())
Options & Options::initializePart()
{
   makeConnections();
   notifyObservers(INotificationEvent(readyId, *this));
   return *this;
}


//------------------------------------------------------------------------------
// Options :: makeConnections
//------------------------------------------------------------------------------
//#pragma export (Options::makeConnections())
Boolean Options::makeConnections()
{
   this->enableNotification();
   iCanvas->enableNotification();
   iNB_OPTIONS->enableNotification();
   iTB_MINES->enableNotification();
   iCANVAS_MINE->enableNotification();
   iCK_MINES->enableNotification();
   iSPIN_NUMBER_OF_MINES->enableNotification();
   iST_NUMBER_OF_MINES->enableNotification();
   iBITMAP_MINE->enableNotification();
   iNBTAB_SOUND->enableNotification();
   iCANVAS_SOUND->enableNotification();
   iCHK_SOUND->enableNotification();
   iST_SOUNDTEXT->enableNotification();
   iBITMAP_SOUND->enableNotification();
   iNBTAB_PLAYER->enableNotification();
   iCANVAS_PLAYER->enableNotification();
   iST_ENTERNAME->enableNotification();
   iEF_PLAYER_NAME->enableNotification();
   iIconControl1->enableNotification();
   iNBTAB_MISC->enableNotification();
   iCANVAS_MISC->enableNotification();
   iCHK_SMARTOPPONENT->enableNotification();
   iSPIN_NUMBER_OF_TURNS->enableNotification();
   iST_TURNSROUND->enableNotification();
   iICON_MISC->enableNotification();

   iCB_OK->enableNotification();
   iCB_CANCEL->enableNotification();

   conn0->initialize(iCB_CANCEL, this);
   conn0->handleNotificationsFor(*iCB_CANCEL);

   conn1->initialize(iCB_OK, this);
   conn1->handleNotificationsFor(*iCB_OK);

   return true;
}



/*****************************************************************************
* Function: saveOptions()
* Parms:    none
* Purpose:  Will call the appropriate "set" functions in the game object
*           to save the values keyed in the notebook control.
*
* Returns:  Nothing
*****************************************************************************/
void Options::saveOptions()
{
   IFUNCTRACE_DEVELOP();
   m_pGame->SetLayMineMode(iCK_MINES->isSelected());
   m_pGame->SetSmartOpponent(iCHK_SMARTOPPONENT->isSelected());
   m_pGame->SetNumberOfMines(iSPIN_NUMBER_OF_MINES->value());
   m_pGame->SetSound(iCHK_SOUND->isSelected());
   m_pGame->SetTurnsPerRound(iSPIN_NUMBER_OF_TURNS->value());

   //Save the new name to the game object.
   m_pGame->SetPlayerName(iEF_PLAYER_NAME->text());
   return;  
}

/*****************************************************************************
* Function: getOptions()
* Parms:    none
* Purpose:  Will call the appropriate "get" functions in the game object
*           to retrieve the values so we can set them in the notebook control.
*
* Returns:  Nothing
*****************************************************************************/
void Options::getOptions()
{
   IFUNCTRACE_DEVELOP();

   if(m_pGame->GetLayMineMode())
      iCK_MINES->select();
   else
      iCK_MINES->deselect();

   if(m_pGame->isSmartOpponent())
      iCHK_SMARTOPPONENT->select();
   else
      iCHK_SMARTOPPONENT->deselect();  

   iSPIN_NUMBER_OF_MINES->spinTo(m_pGame->GetNumberOfMines());

   if(m_pGame->GetSound())
      iCHK_SOUND->select();
   else
      iCHK_SOUND->deselect();

   iSPIN_NUMBER_OF_TURNS->spinTo(m_pGame->GetTurnsPerRound());

   iEF_PLAYER_NAME->setText(m_pGame->GetPlayerName());

   return;  
}


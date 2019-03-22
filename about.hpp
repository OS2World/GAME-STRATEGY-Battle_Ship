#ifndef ABOUT_HPP
#define ABOUT_HPP

#include <iframe.hpp>                   //IFrameWindow Class (Parent)
#include <icmdhdr.hpp>                  //ICommandHandler (Parent)


//**************************************************************************
// Class:   AboutDialog                    
//                                         
// Purpose: Dialog window for the About Box
//**************************************************************************
class AboutDialog : public IFrameWindow, public ICommandHandler
{
public:
  AboutDialog (IWindow * ownerWnd, unsigned long rid, IWindow* pbwindow) ;
  ~AboutDialog();

protected:
  virtual Boolean
  command(ICommandEvent& cmdevt);     //Process the dialog command events

private:
};

#endif



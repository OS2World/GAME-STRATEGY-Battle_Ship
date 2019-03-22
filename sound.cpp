/*****************************************************************************
* Program:  SOUND.CPP
* Purpose:  handles the playing of .WAV files
*****************************************************************************/
#include "sound.hpp"
#include  <iwindow.hpp>          /* Window Classes             */
#include  <imsgbox.hpp>          /* MessageBox Class            */


/*****************************************************************************
* Function: Sound
* Parms:    none
* Purpose:  Constructor - instantiate the WAV audio device 
* Returns:  Nothing
*****************************************************************************/
Sound::Sound()
{
   wavPlayer = new IMMWaveAudio(true);
}

/*****************************************************************************
* Function: ~Sound
* Parms:    none
* Purpose:  Destructor - delete the WAV audio device 
* Returns:  Nothing
*****************************************************************************/
Sound::~Sound()
{
   if(wavPlayer) 
      delete wavPlayer;
}


/*****************************************************************************
* Function: playSound
* Parms:    fileName - filename of the .wav file to play
* Purpose:  calls the IBM class lib functions to load a .WAV file and play it
* Returns:  Nothing
*
* I am not sure how I want to handle this exception.  I want this to be object
* to not have any visual components - messagebox. Maybe the caller should 
* catch this??
*****************************************************************************/
void Sound::playSound(IString fileName)
{
   try 
   {
      wavPlayer->loadOnThread(fileName, true);
   }
   catch (IException& exc)
   {
      IString msg = "Could not play the specified sound. ";
      msg += exc.name();

      IMessageBox(IWindow::desktopWindow()).show(msg, IMessageBox::information);
   }
   wavPlayer->play();
   DosSleep(1000);      // Go to sleep for 1 second to give the 
                           // sound a chance to finish
}                       



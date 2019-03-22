#ifndef __SOUND_HPP__
#define __SOUND_HPP__

//#include "battle.h"
//#include "batshpgm.hpp"

#define INCL_DOSPROCESS
#include <os2.h>
#include <immwave.hpp>

#define NOWAIT 0X01
#define WAIT 0X02


//**************************************************************************
// Class:   Sound
//                                                                         *
// Purpose: Provide .wav file support to an application
//**************************************************************************
class Sound 
{
public:
  Sound();
  ~Sound();
  void playSound(IString fileName);

protected:

private:
  IMMWaveAudio *wavPlayer;
};

#endif



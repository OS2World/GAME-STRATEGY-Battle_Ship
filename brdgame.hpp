// CBoardGame - abstract board game class
//
#ifndef __BOARDGAME_H__
#define __BOARDGAME_H__

#include "gamebrd.hpp"

class CBoardGame
{
// Implementation
public:
   CBoardGame();
   virtual ~CBoardGame();

// Attributes
public:

// Operations
public:
   virtual void Initialize() = 0;
   virtual void StartGame() = 0;
   virtual void EndGame() = 0;
       
};
#endif



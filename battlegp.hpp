// CBattleShipGamePiece - Specific BattleShip game piece
//
#ifndef __BATTLESHIPGAMEPIECE_H__
#define __BATTLESHIPGAMEPIECE_H__

class CBattleShipCoordinate;

#include "gamepiec.hpp"
#include <istring.hpp>
#include <ipoint.hpp>

enum {eCARRIER, eBATTLESHIP, eDESTROYER, eSUBMARINE, ePTBOAT, eMINE};

class CBattleShipGamePiece : public CGamePiece
{
// Implementation
public:
   CBattleShipGamePiece();
   ~CBattleShipGamePiece();

// Attributes
protected:
   int      m_nLength;
   int      m_nOpenTargets;
   int      m_nShipType;
   int      m_nHorizontalShipNumber;
   IString  m_csShipName;
   Boolean  m_bSunk;

// Operations
public:
   void     Initialize();
   int      GetLength()    { return m_nLength; }
   IString& GetShipName()  { return m_csShipName; }
   int      GetHorizontalShipNumber() { return m_nHorizontalShipNumber; }
   int      GetShipType()  { return m_nShipType; }
   Boolean  IsShipSunk();

protected:
   CBattleShipGamePiece* Hit(IPoint point);
};
#endif

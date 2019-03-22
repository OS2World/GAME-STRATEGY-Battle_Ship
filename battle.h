#include "battle.rch"

//defines for the speaker beeps
#define BEEPFREQ       100L       /* Beep frequency, in hertz          */
#define BEEPDURATION   50L        /* Duration of beep, in milliseconds */

//The height and width of the game coordinates
#define COORDHEIGHT 20
#define COORDWIDTH  20

//Constants to represent the player or opponent boards
#define PLAYERBOARD   0
#define OPPONENTBOARD 1
                    
//this defines the numeric difference between the horizontal
//  ship numbers and their vertical counterparts.
#define VERTICALSHIPDELTA  100

#define WATER       200
#define MINE        201
#define MINEEXPL    202
#define HITMARK     203
#define BLANK       204
#define SELBUTN     205
#define RIGHTARROW  206
#define LEFTARROW   207
#define UPARROW     208
#define DOWNARROW   209
#define BATTLESHIP  210

//The horizontal bitmaps have numbers exactly 100 less
// than their vertical counterparts.
#define HBATTLE     211
#define HCARRIER    212
#define HDESTROY    213
#define HSUB        214
#define HPTBOAT     215

#define VBATTLE     311
#define VCARRIER    312
#define VDESTROY    313
#define VSUB        314
#define VPTBOAT     315

//#define VBATTLE     HBATTLE  + VERTICALSHIPDELTA
//#define VCARRIER    HCARRIER + VERTICALSHIPDELTA
//#define VDESTROY    HDESTROY + VERTICALSHIPDELTA
//#define VSUB        HSUB     + VERTICALSHIPDELTA
//#define VPTBOAT     HPTBOAT  + VERTICALSHIPDELTA

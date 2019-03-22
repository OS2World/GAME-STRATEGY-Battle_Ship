:userdoc.
:docprof toc=123456.
:title.battle Game Help System 

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

:h1 res=1.Introduction

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:hp7.Introduction
.br
:ehp7.This program was originally written by David Buchwald and myself (David 
Boudah) in Microsoft Windows using Microsoft Visual C++ and MFC&per.  It was 
written as a programming project for an object-oriented class at school&per.  I 
then ported the program to OS/2 and in the process rewrote a good portion of 
the application&per.
:p.
The original game is played on two separate plastic frames, each of which has 
a horizontal and a vertical playing surface&per.  The horizontal surface is used 
for both defensive ship placement and the marking of each of your opponents 
shots with white pegs to register a "miss" and red pegs to register a "hit"&per. 
 The vertical surface is used for your offensive shots against your 
opponent&per.
:p.
Each player's fleet consists of 5 ships&colon. aircraft carrier, destroyer, 
battleship, submarine, and a PT boat&per.  Each player distributes their fleet 
randomly around the horizontal surface&per.  A player then takes a "shot" by 
specifying a row and column location (i&per.e&per. a letter and number combination - 
A1 to J10)&per.  The opponent then responds with "hit" or "miss" appropriately&per.  
When all the targets on a given ship are hit,  the ship is considered sunk&per.  
The player that sinks his opponent's entire fleet is the winner&per.
:p.
In this implementation, the left board is the human player's board and the 
right is the computer's&per. Each board consists of 100 individual squares in a 
10-by-10 matrix&per.  
:p.
:hp7.System :link reftype=hd res=5.Sounds:elink.:ehp7. 
.br
The sound is provided via the OS/2 multimedia classes&per.  You will notice 
different sounds are played when different game pieces are hit,  and when 
the game is over&per.

.br

:h1 res=2.Playing the Game

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:hp7.Starting Out
.br
:ehp7.When a new game starts, the human player will be prompted to arrange his or 
her ships on the board&per.  The player will do this by clicking the mouse button 
on any one of the 100 coordinates available in order to place the bow of the 
ship on the board&per. The player will then be prompted with directional indicators to 
select this ship's direction (N, S, E, W)&per. The player will repeat this operation for 
the remaining ships, wait for the computer to place its ships, and then 
start the game&per.  The game will not allow overlapping ships&per.  
:p.
As previously 
mentioned, shots are taken by both players on their opponents respective 
boards&per.  The human player does this by selecting an opponent's coordinate 
with the left mouse button&per.  The computer selects the human player's 
coordinate automatically as if with the mouse&per.  If the shot is a miss, a 
bitmap of water will be displayed&per.  If the shot is a hit, a red dot 
bitmap will be displayed&per.  The first player to sink all the opponents 
ships wins the game&per.
:p.
:hp7.Tip
.br
:ehp7.After the computer scores a hit on a game piece,  it will always choose the next 
series of squares based on the following&colon.
:ul compact.
:li.
guess to the right of the hit
:li.
guess to the left of the hit
:li.
guess on the bottom of the hit
:li.
guess on the top of the hit
Once the computer detects a straight-line pattern of hits,  it will continue
in that direction until it misses,  or the ship is sunk&per.  A strategy might be
to place the mines at the ends of the ship&per.  Once the computer is tracking its
"hits",  it will surely hit one of your mines!
.br
 

.br

:h1 res=3.Features

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
The BattleShip game has a variety of options to alter standard play and make 
the game more interesting&per.  The following is a list of the current game 
options and their descriptions&per.
:ul compact.
:li.
:link reftype=hd res=5.Sound:elink.&colon. an option to play various WAV files that depict misses or explosions 
(or insults)&per. Sound is provided via the OS/2 multimedia classes&per.  You can even 
change the sounds by substituting your favorite &per.WAV files in place of the ones 
used by the system
.br
:li.
Lay mines&colon. place not only ships, but additional obstacles for your opponent 
in the form of mines&per.  If a player selects a coordinate that is occupied by a 
mine, the player loses a turn
.br
:li.
Smart opponent&colon. as previously mentioned, the game will allow exact guesses 
(hits) by the computer every time&per.  For each shot the computer takes, the 
human player takes 5 (or some configurable value)&per.  Thus, the human player 
races the computer to win the game
.br
:li.
Configurable number of turns&colon. the ability to change the number turns taken at 
a time be each player
.br
:li.
:link reftype=hd res=5.Sound:elink. is provided via the OS/2 multimedia classes&per.  You can turn the sounds 
on and off by selecting the options/settings dialog box&per.  You can even change 
the sounds by substituting your favorite &per.WAV files in place of the ones used 
by the system:eul.


.br

:h1 res=4.Keys and Mouse actions

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:hp2.Left mouse button:ehp2.     - used to select squares on the game board&per.  
:p.
F1              Help Menu&per.
.br
F3              Exit the program&per.
.br
<Ctrl-E>        End the game&per.
.br
<Ctrl-N>        New game&per.
.br
<Ctrl-O>        Settings dialog box&per.

.br

:h1 res=5.Troubleshooting :hp7.Sound



:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:ehp7.The system sounds might be disabled if you are currently running any 
DOS/Windows applications&per.  I found that on my machine if I simply closed the 
DOS-based application,  the sound:i1 id=i1.sound
 worked just fine&per.

.br

:h1 res=6.Development Environment

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:hp7.System
.br
:ehp7.The battle game was developed on a Dell XPS90 computer running OS/2 WARP 
v4&per.0&per.  The :link reftype=hd res=5.sound:elink. card in the development computer is a Media Vision Pro 
Audio 16&per.  The two lines in the config&per.sys for the sound configuration are 
as follows&colon. &per.
:p.
DEVICE=f&colon.\MVPRODD&per.SYS /I&colon.11 /D&colon.6 /S&colon.1,220,1,5 /N&colon.PAS161$
.br
DEVICE=d&colon.\MMOS2\AUDIOVDD&per.SYS PAS161$
:p.
The timestamp of the driver that I used in development is as follows&colon.
:p.
MVPRODD&per.SYS    59480  12-25-93   2&colon.04p
:p.
:hp7.Compiler
.br
:ehp7.The C++ compiler used is the IBM VisualAge C++ compiler v3&per.0 with the following 
CSD levels&colon. 
:ul compact.
:li.
CTC306
:li.
CTU304
:li.
CTS306
:li.
CTO306
:eul.

.br
:hp7.Help System
.br
:ehp7.The help system was developed using the MAKEIPF help compiler developed by&colon. 
:p.
 Dr&per. Martin Vieregg 
.br
 Hubertusstr&per. 26 
.br
 D-85521 Ottobrunn 
.br
 Germany   
.br
 Compuserve 100661,626  

.br

:h1 res=7.Registration

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
This product is released as Shareware&per.  If you like the product,  please 
register with the author by sending $5&per.00 to&colon.
:p.
David Boudah
.br
180 Cottage Road
.br
Enfield, CT 06082
.br
Compuserve ID - 73163,3657
.br
InterNet - dboudah@ibm&per.net
:p.
:hp7.Note
.br
:ehp7.Supporting Shareware only encourages the author to continue to supply 
products into the market&per.

.br

:h1 res=8.Warranty

:font facename=Courier size=12x7 codepage=437.:color fc=default bc=default.

.br
:hp7.Disclaimer
.br
:ehp7.This software is sold as is, without any warranty as to performance or any 
other warranties whether expressed or implied&per.  Because of the many hardware 
and software environments into which this program may be used, no warranty 
of fitness for a particular purpose is offered&per.  The user must assume the 
entire risk of using the program&per.  Any liability of the seller will be 
limited exclusively to product replacement or the refund of the registration 
fee&per.
.br
:euserdoc.

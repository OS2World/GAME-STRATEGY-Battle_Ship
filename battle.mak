# battle.mak:
#
# Makefile for the battle application

# tools and command lines
CPP       = icc
LINK      = icc
RC        = rc
RLINK     = rc

# This one shuts off precompiled headers(si) and turns on browsing (fb)
# CPPOPTS   = -C+ /Gm+ /Gd+ -Tdp -N5 -Ti+ -O- -DIC_TRACE_DEVELOP -Wgen -W3 -Q+ /Fi /Fb
# LINKOPTS  = /de /noi /align:4 /OPTF /BROWSE

#These are the DEBUGGING compile options
# CPPOPTS   = -C+ /Gm+ /Gd+ -Tdp -N5 -Ti+ -O- -DIC_TRACE_DEVELOP -Wgen -W3 -Q+ /Fi /Si 
# LINKOPTS  = /de /noi /align:4 /OPTF

#These are the RELEASE compile options
CPPOPTS   = -C+ -Gm+ -Gd- -N15 -Oc+ -DIC_TRACE_DEVELOP -Wgen -W3 -Q+ /Fi /Si
LINKOPTS  =  /noi /align:4 /OPTF

RCOPTS    = -r

# targets
MAIN_TARGET = battle.exe
MAP_NAME = battle.map
OBJS = battle.obj \
batshpgm.obj \
brdgame.obj \
gamebrd.obj \
gamecord.obj \
battlbrd.obj \
batlcord.obj \
w_batbrd.obj \
w_plabrd.obj \
w_placrd.obj \
w_oppcrd.obj \
w_batgp.obj  \
w_oppbrd.obj \
gamepiec.obj \
battlegp.obj  \
destroy.obj  \
battlshp.obj \
carrier.obj  \
sub.obj      \
ptboat.obj   \
mine.obj     \
sound.obj    \
opponent.obj \
stack.obj    \
options.obj    \
about.obj    \
ammvehdr.obj 

LIBS = os2386.lib

.SUFFIXES : .cpp .rc .obj .exe .ipf .hlp


#
# implicit rules
#
{.}.dlg.res:
  $(RC) $(RCOPTS) .\$*.rc

{.}.rc.res:
  $(RC) $(RCOPTS) .\$*.rc

{.}.ipf.hlp:
  ipfc $*.ipf

{.}.cpp.obj:
  $(CPP) $(CPPOPTS) .\$*.cpp


#
# explicit rules
#

ALL : battle.exe


#battle.exe : $(OBJS) battle.mak battle.res
#    $(LINK) @<<
# /Q /Tdp /B"$(LINKOPTS)"
# /Fe"$(MAIN_TARGET)"
# $(OBJS)
#
# battle.def
#<<
#   $(RLINK) $(RLINKOPTS) battle.res $*.exe


battle.exe : $(OBJS) battle.mak battle.res
    $(LINK) @<<
 /Gm+ /Gd+ -Tdp -N5 -Ti+ /Q+ /Fi /Si
 /B"$(LINKOPTS)"
 /Fe"$(MAIN_TARGET)"
 $(OBJS)

 battle.def
<<
   $(RLINK) $(RLINKOPTS) battle.res $*.exe

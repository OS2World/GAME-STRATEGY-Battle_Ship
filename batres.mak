##########################################################
# Makefile to build a C++ DLL for the BattleShip App
##########################################################

##########################################################
# Define variables for makefile
##########################################################
GCPPFLAGS=/Ge- /Gd+ /Gm- /I.

##########################################################
# Definitions for GCPPFLAGS (compile options):
##########################################################
# /c   = perform compile only
# /Ge- = create a DLL (/Ge+ to create an EXE)
# /Ti+ = generate debugger information
# /Gd- = statically link runtime functions (why??)
# /Gm+ = multi-thread capability
# /Gn+ = not providing linker info about default libraries
#        (in object).  All libraries must be explicitly
#        specified at link time
# /Ft  = generate files for template resolution and put
#        them in the specified directory
# /Tdp = consider all files to be C++ files
# /I   = control which paths are searched when the
#        compiler looks for user #include files.  These 
#        paths are searched before those given in the 
#        INCLUDE environment variable.  The format is:
#             I  path[;path][;path]...
##########################################################

all:          main

main:           battle.dll

##########################################################
# List of dependency files for the DLL.
# NOTE:  the compilation ordering is determined by the
#        dependency ordering.
##########################################################
battle.dll:    batres.def \
                  batres.res \
                batres.obj
##########################################################
# When any of the DLL dependency files change, invoke the
# linker to rebuild the DLL.
##########################################################
                icc $(GCPPFLAGS) batres.obj \
                    /Febattle.dll /Fmbattle.map \
                    os2386.lib cppom30i.lib \
                    batres.def

##########################################################
# compile the .rc file with the Toolkit's Resource
# Compiler to create a .RES file (/r option).
##########################################################
                rc /r batres.rc

##########################################################
# use the Resource Compiler again to add/bind the
# resources to the DLL.
##########################################################
                rc batres.res battle.dll


##########################################################
# Statements to compile each non-visual C++ file for the Rap
##########################################################
batres.obj:       batres.cpp  
                 icc -c $(GCPPFLAGS) batres.cpp

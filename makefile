 #
 #  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 #  Soundblaster with MPU-401 UART compatible interfaces.
 #  Copyright (C) 2011  Kyle Delaney
 #
 #  This file is a part of BASS.
 #
 #  BASS is free software: you can redistribute it and/or modify
 #  it under the terms of the GNU General Public License as published by
 #  the Free Software Foundation, either version 3 of the License, or
 #  (at your option) any later version.
 #
 #  BASS is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU General Public License for more details.
 #
 #  You should have received a copy of the GNU General Public License
 #  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 #  You may contact the author at <dr.kylstein@gmail.com>
 #
platform = DOS
CC = wcc
CPP = wpp
CFLAGS = -zW
res1_flags = -bt=dos -30

name = bass
LNK = $(name).lnk
OBJS = main.obj MidiDev.obj MidiDisp.obj BeepInst.obj DebugIns.obj AdlibMelodicInstrument.obj
lnk_dependencies = makefile

#
# this make include file is used to build all the win examples
#
# It assumes that the following make variables are declared by the makefile
# that includes it:
#
#       CC                      the name of the C compiler to use to create
#                               the .obj files
#       CDIR                    directories other than .. to be searched for
#                               .c files
#       CFLAGS                  any compiler flags needed to build the
#                               object files
#       name                    the name of the EXE file to build (without
#                               any extension)
#       LNK                     the name of the linker command file
#       OBJS                    a list of the .obj files needed to build
#                               the EXE
#       resources               a list of all files the .res file is
#                               dependent upon
#       res1_flags              flags to be used by the resource compiler's
#                               first pass
#       res2_flags              flags to be used by the resource compiler's
#                               second pass
#       lnk_dependencies        a list of files the linker command file
#                               depends upon
#       platform                Win32 for Win9x/Me/NT/2K/XP, Win16 for 3.x/Win386
#
# In addition the makefile must declare a procedure called linkit that
# that can be used to add commands to the linker command file

CFLAGS += -I"$(%WATCOM)/h" -I"$(%WATCOM)/lib286" -I"$(%WATCOM)/lib286/dos"

CFLAGS += -zq -oaxt -d2 -w4 -fo=.obj

$(name).exe : $(OBJS) $(LNK)
    wlink @$(LNK)

$(LNK) : $(lnk_dependencies)
    %create $(LNK)
    @%append $(LNK) debug all
    @%append $(LNK) name $(name)
    @%append $(LNK) op map, quiet
    @%make linkit
    @for %i in ($(OBJS)) do @%append $(LNK) file %i


.EXTENSIONS:
.EXTENSIONS: .exe
.EXTENSIONS: .obj
.EXTENSIONS: .c .cpp .h .hpp

.c:..;$(CDIR)
.cpp:..;$(CDIR)


.c.obj :
        $(CC) $(CFLAGS) $[*
	
.cpp.obj :
        $(CPP) $(CFLAGS) $[*

clean: .symbolic
    rm -f *.obj *.err *.exe *.lnk *.res *.rex *.lib *.sym *.map
    rm -f *.lk1 *.mk1 *.mk

linkit : .PROCEDURE
    @%append $(LNK) system dos

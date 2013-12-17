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
name = bass

CC = wcc
CPP = wpp
CFLAGS = -ml
LDFLAGS = -l=DOS -fe=../$(name).exe

CDIR = ../src
HDIR = ../include

OBJS = main.obj MidiDev.obj MidiDisp.obj BeepInst.obj DebugIns.obj AdlibMelodicInstrument.obj OPLDriver.obj
lnk_dependencies = makefile


CFLAGS += -I"$(%WATCOM)/h" -I"$(%WATCOM)/lib286" -I"$(%WATCOM)/lib286/dos" -I"$(HDIR)"
# xd = exception handling disabled
# o: a = global variables are never accessed through pointers, l+ optimize and unroll loops
CFLAGS += -xs -oal+ -fo=.obj

../$(name).exe : $(OBJS)
	wcl $(LDFLAGS) $(OBJS)

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

clean: .SYMBOLIC
	rm -f *.obj *.err ../$(name).exe *.lnk *.res *.rex *.lib *.sym *.map
	rm -f *.lk1 *.mk1 *.mk

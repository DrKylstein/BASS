/*
 *  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 *  Soundblaster with MPU-401 UART compatible interfaces.
 *  Copyright (C) 2011  Kyle Delaney
 *
 *  This file is a part of BASS.
 *
 *  BASS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BASS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  You may contact the author at <dr.kylstein@gmail.com>
 */
#include <conio>
#include <iostream>
#include "MidiDisp.hpp"
#include "BeepInst.hpp"
#include "DebugIns.hpp"
#include "OPLDriver.hpp"
#include "AdlibMelodicInstrument.hpp"
//include <dos.h>
//volatile int clock_ticks;
//void (__interrupt __far *prev_int_1c)();
//define BLIP_COUNT 1 //18ticks = 1second
//~ void __interrupt __far timer_rtn()
//~ {
	//~ ++clock_ticks;
	//~ _chain_intr( prev_int_1c );
//~ }

int main() {
	std::cout << "B.eeper A.dlib S.oundblaster S.ynth. (C) 2013 Kyle Delaney" << std::endl;
	
	//prev_int_1c = _dos_getvect( 0x1c );
	//_dos_setvect( 0x1c, timer_rtn );
	//std::cout << "Timer initalized." << std::endl;
	
	MidiDispatcher midi;
	midi.init();
	std::cout << "Midi initalized." << std::endl;
	
	BeeperInstrument speaker;
	speaker.channel = 0;
	speaker.startingNote = 0;
	speaker.endingNote = 127;
	speaker.transpose = 0;
	midi.addInstrument(&speaker);
	
    OPLDriver oplDriver;
    
	AdlibMelodicInstrument adlib(&oplDriver, 0, 6);
	adlib.channel = 1;
	adlib.startingNote = 0;
	adlib.endingNote = 127;
	adlib.transpose = 0;
	midi.addInstrument(&adlib);
	
	DebugInstrument debug;
	debug.channel = 3;
	debug.startingNote = 0;
	debug.endingNote = 127;
	debug.transpose = 0;
	midi.addInstrument(&debug);
	
	while(true) {
		midi.pollEvents();
		
		//if(clock_ticks > BLIP_COUNT) {
			//midi.updateModulation(clock_ticks);
			//clock_ticks -= BLIP_COUNT;
		//}
		
		if(kbhit()) break;
	}	
	std::cout << "Exiting." << std::endl;
	
	//_dos_setvect( 0x1c, prev_int_1c );
	
	return 0;
}
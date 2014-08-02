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
//include <iostream>
#include <cstring>
#include <vector>
#include "MidiDev.hpp"
#include "MidiDisp.hpp"
#include "BeepInst.hpp"
#include "DebugIns.hpp"
#include "OPLDriver.hpp"
#include "AdlibMelodicInstrument.hpp"
#include "TextScreen.hpp"
#include "AdlibMelodicControlPanel.hpp"
#include "PCKeyboard.hpp"
#include "BeeperControlPanel.hpp"
#include "TextCursor.hpp"
//volatile int clock_ticks;
//void (__interrupt __far *prev_int_1c)();
//define BLIP_COUNT 1 //18ticks = 1second
//~ void __interrupt __far timer_rtn()
//~ {
	//~ ++clock_ticks;
	//~ _chain_intr( prev_int_1c );
//~ }

static const char* buttons[] = {
    "9 Debug",
    "10 Exit",
    0
};



int main() {
	//std::cout << "B.eeper A.dlib S.oundblaster S.ynth. (C) 2013 Kyle Delaney" << std::endl;
	
	MidiDevice mpu401;
	MidiDispatcher midi;
	midi.init(&mpu401);
	//std::cout << "Midi initalized." << std::endl;
	
    TextScreen screen;
    TextCursor cursor;
    
    BeeperControlPanel beeperCtl(screen);
    
    ControlPanel* head = &beeperCtl;
    
	BeeperInstrument speaker;
	speaker.channel = 0;
	speaker.startingNote = 0;
	speaker.endingNote = 127;
	speaker.transpose = 0;
	midi.addInstrument(&speaker);
	
    OPLDriver oplDriver;
    
    AdlibMelodicControlPanel adlibCtl(screen);
    adlibCtl.insertAfter(beeperCtl);
    
	AdlibMelodicInstrument adlib(&oplDriver, 0, 6, &adlibCtl);
	adlib.channel = 1;
	adlib.startingNote = 0;
	adlib.endingNote = 127;
	adlib.transpose = -1;
	midi.addInstrument(&adlib);
	
	DebugInstrument debug;
	debug.channel = 3;
	debug.startingNote = 0;
	debug.endingNote = 127;
	debug.transpose = 0;
	midi.addInstrument(&debug);
	   
       
    std::vector<AbstractInstrument*> instruments;
       
    instruments.push_back(&speaker);
    instruments.push_back(&adlib);
        
    screen.fill(' ', 0x07, 0, 0, 80, 24);
    screen.hbar(0x07, 0, 0, 80);
    screen.print("B.eeper A.dlib S.oundblaster S.ynth. (C) 2014 Kyle Delaney", 0x07, 1, 0);
        
    int x = 0;
    for(int i = 0; buttons[i] != 0; i++) {
        screen.print(buttons[i], 0x30, x,24);
        x += std::strlen(buttons[i]) + 1;
    }
    
    
    for (ControlPanel* p = head; p != 0; p = p->getNext()) {
        p->drawStatic();
    }

    for (std::vector<AbstractInstrument*>::iterator it = instruments.begin() ; it != instruments.end(); ++it) {
        (*it)->resetParameters();
    }
    
    PCKeyboard pckey;
    
    int pos = 0;
    bool moved = true;

    bool oplDebug = false;
    
	while(true) {
        if(pckey.wasPressed(KeySym::f10)) break;
		midi.pollEvents();
        
        if(pckey.wasPressed(KeySym::f9)) {
            oplDebug = !oplDebug;
            if(oplDebug) {
                for(int i = 0; i <= 0xF; i++) {
                    screen.printHex(i, 0x70, 2 + i*3, 7);
                }        
                for(int i = 0; i <= 0xF; i++) {
                    screen.printHex(i, 0x70, 0, 8+i);
                }               
            } else {
                for (ControlPanel* p = head; p != 0; p = p->getNext()) {
                    p->drawStatic();
                }
                for (std::vector<AbstractInstrument*>::iterator it = instruments.begin() ; it != instruments.end(); ++it) {
                    (*it)->resetParameters();
                }
            }
        }
        if(oplDebug) {
            for(int i = 0; i < 0xF6; i++) {
                screen.print("0", 0x07, 2 + (i % 16)*3, i/16 + 8);
                screen.printHex(oplDriver.getReg(i), 0x07, 3 + (i % 16)*3, i/16 + 8);
            }
        }
        
        bool tab = pckey.wasPressed(KeySym::tab);
		if(pckey.wasPressed(KeySym::right) || (tab && 
        !pckey.isHeld(KeySym::left_shift) && 
        !pckey.isHeld(KeySym::right_shift))) {
            pos++;
            moved = true;
        }
		if(pckey.wasPressed(KeySym::left) || (tab && 
        (pckey.isHeld(KeySym::left_shift) || 
        pckey.isHeld(KeySym::right_shift)))) {
            pos--;
            moved = true;
        }
        if(moved) {
            moved = false;
            int rpos = pos;
            for (ControlPanel* p = head; p != 0; p = p->getNext()) {
                if(rpos >= p->getParameterCount()) {
                    rpos -= p->getParameterCount();
                    continue;
                }
                cursor.moveTo(p->getPosition(rpos).first, p->getPosition(rpos).second);
            }
        }

		
	}	
	//std::cout << "Exiting." << std::endl;
	    
    _asm {
        mov ax,3
        int 10h
    }

	return 0;
}
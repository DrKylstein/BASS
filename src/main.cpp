/*
 *  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 *  Soundblaster with MPU-401 UART compatible interfaces.
 *  Copyright (C) 2014  Kyle Delaney
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
#include "MPU.hpp"
#include "MidiBoss.hpp"
#include "BeepVox.hpp"
#include "DebugVox.hpp"
#include "FMDriver.hpp"
#include "FMVox.hpp"
#include "TextMode.hpp"
#include "FMPane.hpp"
#include "PCKeys.hpp"
#include "BeepPane.hpp"
#include "Cursor.hpp"

static const char* buttons[10] = {
    "Help  ",
    "Edit  ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "FM Dbg",
    "Exit  "
};



int main() {
	MPU mpu401;
	MidiBoss midi;
	midi.init(&mpu401);
	
    TextMode screen;
    Cursor cursor;
    
    BeepPane beeperCtl(&screen);
    
    Pane* head = &beeperCtl;
    Pane* tail = &beeperCtl;
    
	BeepVox speaker(&beeperCtl);
    speaker.setParameter(BeepVox::P_CC_CHANNEL, 0);
    speaker.setParameter(BeepVox::P_NOTE_CHANNEL, 0);
	speaker.startingNote = 0;
	speaker.endingNote = 127;
	speaker.transpose = 0;
	midi.addInstrument(&speaker);
	
    FMDriver oplDriver;
    
    for(int i = 0; i < 2; i++) {
        FMPane* adlibCtl = new FMPane(&screen);
        adlibCtl->insertAfter(*tail); tail = adlibCtl;
        FMVox* adlib = new FMVox(&oplDriver, i*3, 3, adlibCtl);
        adlibCtl->setVoice(adlib);
        adlib->setParameter(FMVox::P_CC_CHANNEL, 1+i);
        adlib->setParameter(FMVox::P_NOTE_CHANNEL, 1+i);
        adlib->startingNote = 0;
        adlib->endingNote = 127;
        adlib->transpose = 0;
        midi.addInstrument(adlib);
    }
    for(int i = 0; i < 3; i++) {
        FMPane* adlibCtl = new FMPane(&screen);
        adlibCtl->insertAfter(*tail); tail = adlibCtl;
        FMVox* adlib = new FMVox(&oplDriver, 3+i, 1, adlibCtl);
        adlibCtl->setVoice(adlib);
        adlib->setParameter(FMVox::P_CC_CHANNEL, 3+i);
        adlib->setParameter(FMVox::P_NOTE_CHANNEL, 3+i);
        adlib->startingNote = 0;
        adlib->endingNote = 127;
        adlib->transpose = 0;
        midi.addInstrument(adlib);
    }
        
	//DebugVox debug;
	//debug.channel = 3;
	//debug.startingNote = 0;
	//debug.endingNote = 127;
	//debug.transpose = 0;
	//midi.addInstrument(&debug);
	   
    screen.fill(' ', 0x07, 0, 0, 80, 24);
    screen.hbar(0x07, 0, 0, 80);
    screen.print("B.eeper A.dlib S.oundblaster S.ynth. (C) 2014 Kyle Delaney", 0x07, 1, 0);
        
    int x = 0;
    for(int i = 0; i < 10; i++) {
        screen.print(i+1,0x07,x,24);
        if(i < 10) {
            x++;
        } else {
            x+=2;
        }
        screen.print(buttons[i], 0x30, x,24);
        x += std::strlen(buttons[i]) + (i<8?1:2);
    }
    
    
    for (Pane* p = head; p != 0; p = p->getNext()) {
        p->drawStatic();
        p->redrawParameters();
    }
    
    PCKeys pckey;
    
    Pane* currentPane = head;
    int pos = 0;
    cursor.moveTo(currentPane->getPosition(pos).first, 
        currentPane->getPosition(pos).second);
    
    bool oplDebug = false;
    bool editMode = false;
    int editValue = 0;
    
	while(true) {
        if(pckey.wasPressed(KeySym::f10)) break;
		midi.pollEvents();
        if(!editMode) {
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
                    screen.fill(' ',0x07,0,0,80,24);
                    for (Pane* p = head; p != 0; p = p->getNext()) {
                        p->drawStatic();
                        p->redrawParameters();
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
                if(pos < currentPane->getParameterCount()-1) {
                    pos++;
                    cursor.moveTo(currentPane->getPosition(pos).first, 
                        currentPane->getPosition(pos).second);
                }
            }
            if(pckey.wasPressed(KeySym::left) || (tab && 
            (pckey.isHeld(KeySym::left_shift) || 
            pckey.isHeld(KeySym::right_shift)))) {
                if(pos > 0) {
                    pos--;
                    cursor.moveTo(currentPane->getPosition(pos).first, 
                        currentPane->getPosition(pos).second);
                }
            }
            if(pckey.wasPressed(KeySym::down) || 
            pckey.wasPressed(KeySym::page_down)) {
                if(currentPane->getNext()) {
                    currentPane = currentPane->getNext();
                    pos = 0;
                    cursor.moveTo(currentPane->getPosition(pos).first, 
                        currentPane->getPosition(pos).second);
                }
            }
            if(pckey.wasPressed(KeySym::up) || pckey.wasPressed(KeySym::page_up)) {
                if(currentPane->getPrevious()) {
                    currentPane = currentPane->getPrevious();
                    pos = 0;
                    cursor.moveTo(currentPane->getPosition(pos).first, 
                        currentPane->getPosition(pos).second);
                }
            }
            if(pckey.wasPressed(KeySym::f2)) {
                editMode = true;
                editValue = 0;
                screen.print(">",0x07,0,23);
                screen.print(editValue, 0x07, 4, 23);
                cursor.setHeight(7);
            }
        } else {
            if(pckey.wasPressed(KeySym::enter)) {
                editMode = false;
                screen.fill(' ', 0x07, 0, 23, 5, 1);
                currentPane->submitParameter(pos, editValue);
                cursor.setHeight(1);
            } else if(pckey.wasPressed(KeySym::backspace)) {
                    editValue /= 10;
                    screen.fill(' ', 0x07, 1, 23, 4, 1);
                    screen.print(editValue, 0x07, 4, 23);
            } else if(editValue < 127) {
                int digit = pckey.getDigit();
                if(digit != -1 && (editValue*10 + digit) < 128) {
                    editValue *= 10;
                    editValue += digit;
                    screen.print(editValue, 0x07, 4, 23);            
                }
            }
        }
        

	}	
	return 0;
}
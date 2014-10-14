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
#include "Timer.hpp"

static const char* buttons[10] = {
    "Help  ",
    "Params",
    "Debug ",
    "ScrSav",
    "      ",
    "      ",
    "      ",
    "      ",
    "      ",
    "Exit  "
};

int main() {
    Timer timer(1000);
	MPU mpu401;
	MidiBoss midi;
	midi.init(&mpu401);
	
    TextMode helpPage(0);
    helpPage.fill(' ', 0x2F, 0, 0, 80, 23);
    helpPage.box(0x2F, 0, 0, 80, 23);

    TextMode screen(1);
    
    TextMode debugPage(2);
    debugPage.fill(' ', 0x07, 0, 0, 80, 24);
    for(int i = 0; i <= 0xF; i++) {
        debugPage.printHex(i, 0x70, 2 + i*3, 0);
    }
    for(int i = 0; i <= 0xF; i++) {
        debugPage.printHex(i, 0x70, 0, 1+i);
    }
    
    TextMode screenSaver(3);
    screenSaver.fill(' ', 0x07, 0, 0, 80, 25);

    BeepPane beeperCtl(&screen);
    
    Pane* head = &beeperCtl;
    Pane* tail = &beeperCtl;
    
	BeepVox speaker(&beeperCtl);
    beeperCtl.setVoice(&speaker);
    speaker.setParameter(Vox::P_CC_CHANNEL, 0);
    speaker.setParameter(Vox::P_NOTE_CHANNEL, 0);
	speaker.setParameter(Vox::P_FIRST_KEY, 0);
	speaker.setParameter(Vox::P_LAST_KEY, 127);
	speaker.setParameter(Vox::P_TRANSPOSE, 0);
	midi.addInstrument(&speaker);
    
    FMDriver oplDriver;
    
    for(int i = 0; i < 2; i++) {
        FMPane* adlibCtl = new FMPane(&screen);
        adlibCtl->insertAfter(*tail); tail = adlibCtl;
        FMVox* adlib = new FMVox(&oplDriver, i*3, 3, adlibCtl);
        if(i == 0) {
            for(int j = 0; j < 19; j++) {
                helpPage.print(j, 0x2F, 2, j+1);
                helpPage.print(adlib->getParameterName(j), 0x2F, 4, j+1);
                helpPage.print(adlib->getParameterMin(j), 0x2F, 34, j+1);
                helpPage.print(adlib->getParameterMax(j), 0x2F, 38, j+1);
            }
            for(int j = 19; j < FMVox::PARAMETER_COUNT; j++) {
                helpPage.print(j, 0x2F, 41, j+1-19);
                helpPage.print(adlib->getParameterName(j), 0x2F, 43, j+1-19);
                helpPage.print(adlib->getParameterMax(j), 0x2F, 78, j+1-19);
                helpPage.print(adlib->getParameterMin(j), 0x2F, 74, j+1-19);
            }
        }
        adlibCtl->setVoice(adlib);
        adlib->setParameter(FMVox::P_CC_CHANNEL, 1+i);
        adlib->setParameter(FMVox::P_NOTE_CHANNEL, 1+i);
        adlib->setParameter(Vox::P_FIRST_KEY, 0);
        adlib->setParameter(Vox::P_LAST_KEY, 127);
        adlib->setParameter(Vox::P_TRANSPOSE, 0);
        midi.addInstrument(adlib);
    }
    for(int i = 0; i < 3; i++) {
        FMPane* adlibCtl = new FMPane(&screen);
        adlibCtl->insertAfter(*tail); tail = adlibCtl;
        FMVox* adlib = new FMVox(&oplDriver, 3+i, 1, adlibCtl);
        adlibCtl->setVoice(adlib);
        adlib->setParameter(FMVox::P_CC_CHANNEL, 3+i);
        adlib->setParameter(FMVox::P_NOTE_CHANNEL, 3+i);
        adlib->setParameter(Vox::P_FIRST_KEY, 0);
        adlib->setParameter(Vox::P_LAST_KEY, 127);
        adlib->setParameter(Vox::P_TRANSPOSE, 0);
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
    helpPage.print("B.eeper A.dlib S.oundblaster S.ynth. (C) 2014 Kyle Delaney", 0x2F, 1, 0);
        
    int x = 0;
    for(int i = 0; i < 10; i++) {
        screen.print(i+1,0x07,x,24);
        helpPage.print(i+1,0x07,x,24);
        debugPage.print(i+1,0x07,x,24);
        if(i < 10) {
            x++;
        } else {
            x+=2;
        }
        screen.print(buttons[i], 0x30, x,24);
        helpPage.print(buttons[i], 0x30, x,24);
        debugPage.print(buttons[i], 0x30, x,24);
        x += std::strlen(buttons[i]) + (i<8?1:2);
    }
    
    
    for (Pane* p = head; p != 0; p = p->getNext()) {
        p->drawStatic();
        p->redrawParameters();
    }
    
    PCKeys pckey;
    
    Pane* currentPane = head;
    int pos = 0;
    screen.moveCursorTo(currentPane->getPosition(pos).first, 
        currentPane->getPosition(pos).second);
    
    enum {
        PG_HELP,
        PG_MAIN,
        PG_DEBUG,
        PG_SCREENSAVER
    } page = PG_MAIN;
    int editValue = 0;
    bool editMode = false;
    
    Timer::tics_t lastTics = timer.getTics();
    Timer::tics_t interval = 0;
    int scrsavI = 0;
    
    int matrixX = 0;
    int matrixY = 0;
    
	while(true) {
        if(pckey.wasPressed(KeySym::f10)) break;
		midi.pollEvents();
        switch(page) {
            case PG_MAIN:
                if(!editMode) {
                    bool tab = pckey.wasPressed(KeySym::tab);
                    if(pckey.wasPressed(KeySym::right) || (tab && 
                    !pckey.isHeld(KeySym::left_shift) && 
                    !pckey.isHeld(KeySym::right_shift))) {
                        if(pos < currentPane->getParameterCount()-1) {
                            pos++;
                            screen.moveCursorTo(currentPane->getPosition(pos).first, 
                                currentPane->getPosition(pos).second);
                        }
                    }
                    if(pckey.wasPressed(KeySym::left) || (tab && 
                    (pckey.isHeld(KeySym::left_shift) || 
                    pckey.isHeld(KeySym::right_shift)))) {
                        if(pos > 0) {
                            pos--;
                            screen.moveCursorTo(currentPane->getPosition(pos).first, 
                                currentPane->getPosition(pos).second);
                        }
                    }
                    if(pckey.wasPressed(KeySym::down) || 
                    pckey.wasPressed(KeySym::page_down)) {
                        if(currentPane->getNext()) {
                            currentPane = currentPane->getNext();
                            pos = 0;
                            screen.moveCursorTo(currentPane->getPosition(pos).first, 
                                currentPane->getPosition(pos).second);
                        }
                    }
                    if(pckey.wasPressed(KeySym::up) || pckey.wasPressed(KeySym::page_up)) {
                        if(currentPane->getPrevious()) {
                            currentPane = currentPane->getPrevious();
                            pos = 0;
                            screen.moveCursorTo(currentPane->getPosition(pos).first, 
                                currentPane->getPosition(pos).second);
                        }
                    }
                    if(pckey.wasPressed(KeySym::enter)) {
                        editMode = true;
                        editValue = 0;
                        screen.print(">",0x07,0,23);
                        screen.print(editValue, 0x07, 4, 23);
                        screen.setCursorHeight(7);
                    }
                } else {
                    if(pckey.wasPressed(KeySym::enter)) {
                        editMode = false;
                        screen.fill(' ', 0x07, 0, 23, 5, 1);
                        currentPane->submitParameter(pos, editValue);
                        screen.setCursorHeight(1);
                    } else if(pckey.wasPressed(KeySym::backspace)) {
                        editValue /= 10;
                        screen.fill(' ', 0x07, 1, 23, 4, 1);
                        screen.print(editValue, 0x07, 4, 23);
                    } else if(pckey.wasPressed(KeySym::minus)) {
                        editValue *= -1;
                        screen.fill(' ', 0x07, 1, 23, 4, 1);
                        screen.print(editValue, 0x07, 4, 23);
                    } else {
                        int digit = pckey.getDigit();
                        if(digit != -1) {
                            editValue *= 10;
                            editValue += digit * (editValue < 0?-1:1);
                            screen.print(editValue, 0x07, 4, 23);            
                        }
                    }
                }
            case PG_SCREENSAVER:
                interval = timer.getTics() - lastTics;
                if(interval > timer.second()/12) {
                    if(scrsavI > 2000) {
                        screenSaver.fill(' ', 0x07, 0, 0, 80, 25);
                        scrsavI = 0;
                    }
                    int random = matrixX+lastTics+scrsavI;
                    if(matrixY > 2) {
                        screenSaver.print((char)(random++), 0x08, matrixX, matrixY-3);
                    }
                    if(matrixY > 1) {
                        screenSaver.print((char)(random++), 0x02, matrixX, matrixY-2);
                    }
                    if(matrixY > 0) {
                        screenSaver.print((char)(random++), 0x0A, matrixX, matrixY-1);
                    }
                    screenSaver.print((char)(random), 0x0F, matrixX, matrixY);
                    scrsavI++;
                    matrixY++;
                    if(matrixY == 25 || matrixY == random % 25) {
                        matrixY = 0;
                        matrixX = random % 80;
                    }
                    lastTics = timer.getTics();
                }
            case PG_DEBUG:
                for(int i = 0; i < 0xF6; i++) {
                    debugPage.print("0", 0x07, 2 + (i % 16)*3, i/16 + 1);
                    debugPage.printHex(oplDriver.getReg(i), 0x07, 3 + (i % 16)*3, i/16 + 1);
                }
        }
        if(!editMode) {
            if(pckey.wasPressed(KeySym::f1)) {
                page = PG_HELP;
                helpPage.activate();
            }
            if(pckey.wasPressed(KeySym::f2)) {
                page = PG_MAIN;
                screen.activate();
            }
            if(pckey.wasPressed(KeySym::f3)) {
                page = PG_DEBUG;
                debugPage.activate();
            }
            if(pckey.wasPressed(KeySym::f4)) {
                page = PG_SCREENSAVER;
                screenSaver.activate();
                lastTics = timer.getTics();
            }
        }
        

	}	
    helpPage.activate();
    screen.moveCursorTo(79,24);
	return 0;
}
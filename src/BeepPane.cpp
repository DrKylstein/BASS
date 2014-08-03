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
#include "BeepPane.hpp"

static const unsigned char BeepPane::_positions[BeepPane::PARAMETER_COUNT][2] = {
    {77,0}
};

BeepPane::BeepPane(TextMode* screen): _screen(screen), _lastPos(-1) {
    _clearLinks();
}

BeepPane::~BeepPane() {
    dettach();
}

void BeepPane::updateParameter(int id, int value) {
    if(id >= PARAMETER_COUNT) return;
    _values[id] = value;
    _screen->print("00",0x82,_positions[id][0],_positions[id][1]+getTop());
    _screen->print(value,0x82,_positions[id][0]+1,_positions[id][1]+getTop());
}

void BeepPane::drawStatic() {
    _screen->box(0x07, 0, getTop(), 80, 3);
    _screen->print("Beeper", 0x07, 1,getTop());
}

void BeepPane::redrawParameters() {
    for(int id = 0; id < PARAMETER_COUNT; id++) {
        _screen->print("00",0x82,_positions[id][0],_positions[id][1]+getTop());
        _screen->print(_values[id],0x82,_positions[id][0]+1,_positions[id][1]+getTop());
    }
}

int BeepPane::getParameterCount() {
    return 0;
}
int BeepPane::getBottom() {
    return getTop() + 3;
}

std::pair<int, int> BeepPane::getPosition(int item) {
    return std::pair<int,int>(0,0);
}

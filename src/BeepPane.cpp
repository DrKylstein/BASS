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
#include "BeepVox.hpp"
#include "BeepPane.hpp"

static const unsigned char BeepPane::_positions[BeepPane::PARAMETER_COUNT][2] = {
    {4,1},{11,1},{18, 1},{25, 1},{32, 1}
};

static const char* BeepPane::_labels[BeepPane::PARAMETER_COUNT] = {
    "Not",
    "CC",
    "+",
    "1st",
    "Lst"
};

BeepPane::BeepPane(TextMode* screen): _screen(screen), _lastPos(-1) {
    _clearLinks();
    _voice = 0;
}

BeepPane::~BeepPane() {
    dettach();
}

void BeepPane::updateParameter(int id, int value) {
    if(id >= PARAMETER_COUNT) return;
    _values[id] = value;
    switch(id) {
        case BeepVox::P_NOTE_CHANNEL:
        case BeepVox::P_CC_CHANNEL:
            value++;
    }
    _screen->print("   ", 0x0F, _positions[id][0]-1,   _positions[id][1]+getTop());
    _screen->print(value, 0x0F, _positions[id][0]+1, _positions[id][1]+getTop());
}

void BeepPane::setVoice(BeepVox* voice) {
    _voice = voice;
}
void BeepPane::submitParameter(int id, int value) {
    if(id >= PARAMETER_COUNT) return;
    if(_voice != 0) {
        _voice->setParameter(id, value);
    }
}

void BeepPane::drawStatic() {
    _screen->hbar(0x2E, 0, getTop(), 80);
    _screen->hbar(0x2E, 0, getBottom(), 80);
    _screen->fill(' ', 0x2E,0, getTop()+1, 80, getBottom()-getTop()-1);
    _screen->print("Beeper", 0x2E, 1,     getTop());
    for(int i =0; i < PARAMETER_COUNT; i++) {
        _screen->print(_labels[i], 0x2E, i*7, 1 + getTop());
    }
}

void BeepPane::redrawParameters() {
    for(int id = 0; id < PARAMETER_COUNT; id++) {
        updateParameter(id, _values[id]);
    }
}

int BeepPane::getParameterCount() {
    return PARAMETER_COUNT;
}
int BeepPane::getBottom() {
    return getTop() + 2;
}

std::pair<int, int> BeepPane::getPosition(int item) {
    return std::pair<int,int>(_positions[item][0],_positions[item][1]);
}

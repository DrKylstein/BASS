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
#include "FMPane.hpp"

static const unsigned char FMPane::_positions[FMPane::PARAMETER_COUNT][2] = {
    {77,0},
    {6,2},{10,2},{14,2},{18,2},{22,2},{26,2}, {30,2},{34,2},{38,2},{42,2},
    {6,3},{10,3},{14,3},{18,3},{22,3},{26,3}, {30,3},{34,3},{38,3},{42,3}, 
    {46,2},{50,2}, {54,2},{58,2}
};

static const char* labels[] = {
    "Atk","Dcy","Stn","Rls","Vol","Frq","Trm","Vib","Hld", "Wav",
    "AM","Fbk","TD","VD"
};

FMPane::FMPane(TextMode* screen) {
    _clearLinks();
    _screen = screen;
    for(int i = 0; i < PARAMETER_COUNT; i++) {
        _values[i] = 0;
    }
}

std::pair<int, int> FMPane::getPosition(int item) {
    return std::pair<int,int>(_positions[item][0], _positions[item][1]+getTop());
}


FMPane::~FMPane() {
    dettach();
}

void FMPane::updateParameter(int id, int value) {
    if(id >= PARAMETER_COUNT) return;
    _values[id] = value;
    _screen->print("00",0x82,_positions[id][0],_positions[id][1]+getTop());
    _screen->print(value,0x82,_positions[id][0]+1,_positions[id][1]+getTop());
}

void FMPane::drawStatic() {
    _screen->box(0x07, 0, getTop(), 80, 5);
    _screen->print("Adlib", 0x07, 1, getTop());
    _screen->print("OP1",0x07,2,getTop()+2);
    _screen->print("OP1",0x07,2,getTop()+3);
    for(int i = 0; i < 14; i++) {
        _screen->print(labels[i], 0x07, 6 + i*4, 1 + getTop());
    }
    for(int i = 0; i < PARAMETER_COUNT; i++) {
        _screen->print("00",0x82,_positions[i][0],_positions[i][1]+getTop());
    }
}

void FMPane::redrawParameters() {
    for(int id = 0; id < PARAMETER_COUNT; id++) {
        _screen->print("00",0x82,_positions[id][0],_positions[id][1]+getTop());
        _screen->print(_values[id],0x82,_positions[id][0]+1,_positions[id][1]+getTop());
    }
}


int FMPane::getParameterCount() {
    return PARAMETER_COUNT;
}

int FMPane::getBottom() {
    return getTop() + 5;
}

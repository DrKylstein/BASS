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
#include "FMVox.hpp"
#include "FMPane.hpp"

static const unsigned char FMPane::_positions[FMPane::PARAMETER_COUNT][2] = {
    {4,1},{4,2},{12,1},{12,2},{20,1},{20,2},
    {28,1},{32,1},{36,1},{40,1},{44,1},{48,1},{52,1},{56,1},{60,1},{64,1},
    {28,2},{32,2},{36,2},{40,2},{44,2},{48,2},{52,2},{56,2},{60,2},{64,2} 
};

static const char* labels[] = {
    "Atk","Dcy","Stn","Rls","Vol","Frq","Trm","Vib","Hld", "Wav"
};
static const char* moreLabels[] = {
    "Not","CC","AM","Fbk","TD","VD"
};

FMPane::FMPane(TextMode* screen) {
    _clearLinks();
    _screen = screen;
    for(int i = 0; i < PARAMETER_COUNT; i++) {
        _values[i] = 0;
    }
    _voice = 0;
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
    _screen->print("00",0x0F,_positions[id][0],_positions[id][1]+getTop());
    _screen->print(value,0x0F,_positions[id][0]+1,_positions[id][1]+getTop());
}

void FMPane::setVoice(FMVox* voice) {
    _voice = voice;
}

void FMPane::submitParameter(int id, int value) {
    if(_voice != 0) 
        _voice->setParameter(id, value);
}

void FMPane::drawStatic() {
    _screen->hbar(0x4E, 0, getTop(), 80);
    _screen->hbar(0x4E, 0, getBottom(), 80);
    _screen->fill(' ', 0x4E,0, getTop()+1, 80, getBottom()-getTop()-1);
    _screen->print("Adlib", 0x4E,  1, getTop());
    _screen->print("Mod",   0x4E, 24, getTop()+1);
    _screen->print("Car",   0x4E, 24, getTop()+2);
    
    for(int i = 0; i < 6; i++) {
        _screen->print(moreLabels[i], 0x4E, (i/2)*8, 1 + getTop() + i%2);
    }
    for(int i = 0; i < 10; i++) {
        _screen->print(labels[i], 0x4E, 28 + i*4, getTop());
    }
    for(int i = 0; i < PARAMETER_COUNT; i++) {
        _screen->print("00",0x0F,_positions[i][0],_positions[i][1]+getTop());
    }
}

void FMPane::redrawParameters() {
    for(int id = 0; id < PARAMETER_COUNT; id++) {
        updateParameter(id, _values[id]);
    } 
}


int FMPane::getParameterCount() {
    return PARAMETER_COUNT;
}

int FMPane::getBottom() {
    return getTop() + 3;
}

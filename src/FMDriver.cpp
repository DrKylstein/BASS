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
#include <conio.h>
#include "FMDriver.hpp"

using std::uint8_t;

/*static const uint8_t OPERATOR_MAP {
    0, 3, 1, 4, 2, 5, 6, 9, 7, 10, 8, 11, 12, 15, 13, 16, 14, 17, 18,
    21, 19, 22, 20, 23, 24, 27, 25, 28, 26, 29, 30, 33, 31, 34, 32, 35
};*/
static const uint8_t OPERATOR_MAP[] = {
    0x00, 0x03, 0x01, 0x04, 0x02, 0x05, 0x08, 0x0B, 0x09, 
    0x0C, 0x0A, 0x0D, 0x10, 0x13, 0x11, 0x14, 0x12, 0x15
    //18, 21, 19, 22, 20, 23, 24, 27, 25, 28, 26, 29, 30, 33, 31, 34, 32, 35
};

FMDriver::FMDriver() {
    _ioBase = 0x220;
	reset();
}
FMDriver::~FMDriver() {
	reset();
}
void FMDriver::reset() {
	for(int i =0; i < 0xF6; ++i) {
        _regs[i] = 0;
		write(i,0);
	}
    _regs[1] = 0x20;
    _update(1);
}
int FMDriver::read(int reg) {
	outp(_ioBase, reg); //index write
	for(int i = 0; i < 6; ++i) { //delay loop
		inp(_ioBase);
	}
	return inp(_ioBase+1); //data write
}
void FMDriver::_update(int reg) {
    write(reg, _regs[reg]);
}
void FMDriver::write(int reg, int value) {
	outp(_ioBase, reg); //index write
	for(int i = 0; i < 6; ++i) { //delay loop
		inp(_ioBase);
	}
    //std::cout << std::setbase(16) << (int)reg << ":" << (int)value << std::endl;
    outp(_ioBase+1, value); //data write
	for(int i = 0; i < 36; ++i) { //more delay
		inp(_ioBase);
	}
}
int FMDriver::_opIndex(int ch, int op) {
    return OPERATOR_MAP[ch*2 + op];
}
void FMDriver::_setBit(int reg, int bit, bool value) {
    int s = ((int)value) << bit;
    int m = (1 << bit) ^ 0xFF;
    _regs[reg] = (_regs[reg] & m) | s;
}

void FMDriver::setAM(int ch, bool am) {
    _regs[0xC0+ch] = (_regs[0xC0+ch]&0xFE) | (int)am;
    _update(0xC0+ch);
}
void FMDriver::setFeedback(int ch, int factor) {
    _regs[0xC0+ch] = (_regs[0xC0+ch]&0x01) | (factor << 1);
    _update(0xC0+ch);
}

void FMDriver::setVolume(int ch, int op, int level) {
    _regs[0x40+_opIndex(ch, op)] = level & 0x3F;
    _update(0x40+_opIndex(ch, op));
}

void FMDriver::setAttack(int ch, int op, int attack) {
    _regs[0x60+_opIndex(ch, op)] = (_regs[0x60+_opIndex(ch, op)] & 0xF) | ((attack & 0xF) << 4);
    _update(0x60+_opIndex(ch, op));
}
void FMDriver::setDecay(int ch, int op, int decay) {
    _regs[0x60+_opIndex(ch, op)] = (_regs[0x60+_opIndex(ch, op)] & 0xF0) | (decay & 0xF);
    _update(0x60+_opIndex(ch, op));
}
void FMDriver::setSustain(int ch, int op, int sustain) {
    _regs[0x80+_opIndex(ch, op)] = (_regs[0x80+_opIndex(ch, op)] & 0xF) | ((sustain & 0xF) << 4);
    _update(0x80+_opIndex(ch, op));
}
void FMDriver::setRelease(int ch, int op, int release) {
    _regs[0x80+_opIndex(ch, op)] = (_regs[0x80+_opIndex(ch, op)] & 0xF0) | (release & 0xF);
    _update(0x80+_opIndex(ch, op));
}

void FMDriver::keyOn(int ch, int freq) {
    _regs[0xA0+ch] = freq & 0xFF;
    _regs[0xB0+ch] = ((freq >> 8) & 0x1F) | 0x20;
    _update(0xA0+ch);
    _update(0xB0+ch);
}
void FMDriver::setFrequency(int ch, int freq) {
    _regs[0xA0+ch] = freq & 0xFF;
    _regs[0xB0+ch] = _regs[0xB0+ch] & 0x20 | ((freq >> 8) & 0x1F);
    _update(0xA0+ch);
    _update(0xB0+ch);
}
void FMDriver::keyOff(int ch) {
    _regs[0xB0+ch] &= 0x1F;
    _update(0xB0+ch);
}

void FMDriver::setTremolo(int ch, int op, bool tremolo) {
    _setBit(0x20+_opIndex(ch,op), 7, tremolo);
    _update(0x20+_opIndex(ch,op)); 
}
void FMDriver::setVibrato(int ch, int op, bool vibrato) {
    _setBit(0x20+_opIndex(ch,op), 6, vibrato);
    _update(0x20+_opIndex(ch,op)); 
}
void FMDriver::setHold(int ch, int op, bool sustain) {
    _setBit(0x20+_opIndex(ch,op), 5, sustain);
    _update(0x20+_opIndex(ch,op)); 
}
void FMDriver::setScaling(int ch, int op, bool ksr) {
    _setBit(0x20+_opIndex(ch,op), 4, ksr);
    _update(0x20+_opIndex(ch,op)); 
}
void FMDriver::setFreqMult(int ch, int op, int fmult) {
    _regs[0x20+_opIndex(ch, op)] = (_regs[0x20+_opIndex(ch, op)] & 0xF0) | (fmult & 0x0F);
    _update(0x20+_opIndex(ch, op));
}
void FMDriver::setWaveform(int ch, int op, int type) {
    _regs[0xE0+_opIndex(ch, op)] = type & 0x03; //top bit only works on OPL3
}

void FMDriver::setTremoloDepth(bool high) {
    _setBit(0xBD, 7, high);
    _update(0xBD);
}
void FMDriver::setVibratoDepth(bool high) {
    _setBit(0xBD, 6, high);
    _update(0xBD);
}


int FMDriver::getReg(int id) {
    return _regs[id];
}

#include <conio.h>
#include "OPLDriver.hpp"

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

OPLDriver::OPLDriver() {
    _ioBase = 0x220;
	reset();
}
OPLDriver::~OPLDriver() {
	reset();
}
void OPLDriver::reset() {
	for(int i =0; i < 0xF6; ++i) {
        _regs[i] = 0;
		write(i,0);
	}
}
int OPLDriver::read(int reg) {
	outp(_ioBase, reg); //index write
	for(int i = 0; i < 6; ++i) { //delay loop
		inp(_ioBase);
	}
	return inp(_ioBase+1); //data write
}
void OPLDriver::_update(int reg) {
    write(reg, _regs[reg]);
}
void OPLDriver::write(int reg, int value) {
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
int OPLDriver::_opIndex(int ch, int op) {
    return OPERATOR_MAP[ch*2 + op];
}
void OPLDriver::_setBit(int reg, int bit, bool value) {
    int s = ((int)value) << bit;
    int m = (1 << bit) ^ 0xFF;
    _regs[reg] = (_regs[reg] & m) | s;
}

void OPLDriver::setAM(int ch, bool am) {
    _regs[0xC0+ch] = (_regs[0xC0+ch]&0xFE) | (int)am;
    _update(0xC0+ch);
}
void OPLDriver::setFeedback(int ch, int factor) {
    _regs[0xC0+ch] = (_regs[0xC0+ch]&0x01) | (factor << 1);
    _update(0xC0+ch);
}

void OPLDriver::setVolume(int ch, int op, int level) {
    _regs[0x40+_opIndex(ch, op)] = level & 0x3F;
    _update(0x40+_opIndex(ch, op));
}

void OPLDriver::setAttack(int ch, int op, int attack) {
    _regs[0x60+_opIndex(ch, op)] = (_regs[0x60+_opIndex(ch, op)] & 0xF) | ((attack & 0xF) << 4);
    _update(0x60+_opIndex(ch, op));
}
void OPLDriver::setDecay(int ch, int op, int decay) {
    _regs[0x60+_opIndex(ch, op)] = (_regs[0x60+_opIndex(ch, op)] & 0xF0) | (decay & 0xF);
    _update(0x60+_opIndex(ch, op));
}
void OPLDriver::setSustain(int ch, int op, int sustain) {
    _regs[0x80+_opIndex(ch, op)] = (_regs[0x80+_opIndex(ch, op)] & 0xF) | ((sustain & 0xF) << 4);
    _update(0x80+_opIndex(ch, op));
}
void OPLDriver::setRelease(int ch, int op, int release) {
    _regs[0x80+_opIndex(ch, op)] = (_regs[0x80+_opIndex(ch, op)] & 0xF0) | (release & 0xF);
    _update(0x80+_opIndex(ch, op));
}

void OPLDriver::keyOn(int ch, int freq) {
    _regs[0xA0+ch] = freq & 0xFF;
    _regs[0xB0+ch] = (freq >> 8) | 0x20;
    _update(0xA0+ch);
    _update(0xB0+ch);
}
void OPLDriver::keyOff(int ch) {
    _regs[0xB0+ch] &= 0x1F;
    _update(0xB0+ch);
}

void OPLDriver::setTremolo(int ch, int op, bool tremolo) {
    _setBit(0x20+_opIndex(ch,op), 7, tremolo);
    _update(0x20+_opIndex(ch,op)); 
}
void OPLDriver::setVibrato(int ch, int op, bool vibrato) {
    _setBit(0x20+_opIndex(ch,op), 6, vibrato);
    _update(0x20+_opIndex(ch,op)); 
}
void OPLDriver::setHold(int ch, int op, bool sustain) {
    _setBit(0x20+_opIndex(ch,op), 5, sustain);
    _update(0x20+_opIndex(ch,op)); 
}
void OPLDriver::setScaling(int ch, int op, bool ksr) {
    _setBit(0x20+_opIndex(ch,op), 4, ksr);
    _update(0x20+_opIndex(ch,op)); 
}
void OPLDriver::setFreqMult(int ch, int op, int fmult) {
    _regs[0x20+_opIndex(ch, op)] = (_regs[0x20+_opIndex(ch, op)] & 0xF0) | (fmult & 0x0F);
    _update(0x20+_opIndex(ch, op));
}

void OPLDriver::setTremoloDepth(bool high) {
    _setBit(0xBD, 7, high);
    _update(0xBD);
}
void OPLDriver::setVibratoDepth(bool high) {
    _setBit(0xBD, 6, high);
    _update(0xBD);
}


int OPLDriver::getReg(int id) {
    return _regs[id];
}

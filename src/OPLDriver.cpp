#include <conio.h>
//include <iostream>
//include <iomanip>
#include "OPLDriver.hpp"

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
    silence();
	reset();
}
void OPLDriver::reset() {
	for(int i =0; i < 0xF5; ++i) {
		write(i,0);
	}
}
uint8_t OPLDriver::read(uint8_t reg) {
	outp(_ioBase, reg); //index write
	for(int i = 0; i < 6; ++i) { //delay loop
		inp(_ioBase);
	}
	return inp(_ioBase+1); //data write
}
void OPLDriver::write(uint8_t reg, uint8_t value) {
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
void OPLDriver::silence() {
	for(int i = 0; i < CHANNEL_COUNT; ++i) {
        keyOff(i);
	}
}
void OPLDriver::setMode(int channel, SynthMode mode) {
    write(0xC0+channel, mode);
}
void OPLDriver::setVolume(int channel, int op, int level) {
    int realOp = OPERATOR_MAP[channel*2 + op];
    write(0x40+realOp, MAX_VOLUME-level);
}
void OPLDriver::setADSR(int channel, int op, int attack, int decay, int sustain, int release) {
    int realOp = OPERATOR_MAP[channel*2 + op];
    write(0x60+realOp, (attack << 4) | decay);
    write(0x80+realOp, (sustain << 4) | release);
}
void OPLDriver::keyOn(int channel, uint16_t freq) {
    write(0xA0+channel, freq & 0xFF);
    write(0xB0+channel, (freq >> 8) | 0x20);
}
void OPLDriver::keyOff(int channel) {
    write(0xB0+channel, 0x00);
}

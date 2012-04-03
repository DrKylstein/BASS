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
#include "MidiDev.hpp"
#include <conio>
#include <cassert>
bool MidiDevice::isDetected() {
	return _hardwareOk;
}
bool MidiDevice::dataReady() {
	if(_hardwareOk)
		return !(inp(0x331) & 0x80);
	return false;
}
unsigned char MidiDevice::read() {
	if(dataReady())
		return inp(0x330);
	return 0xFF;
}
MidiDevice::MidiDevice() {	
	//Hardware initialization for MPU401
	_hardwareOk = false;
	//read status before setting mode
	while(inp(0x331) & 0x40) {}
	// reset mode
	outp(0x331, 0xFF);
	for(int i = 0; i < 0xFFFF; ++i) {
		status = inp(0x331);
		if(!(status & 0x80)) {
			data = inp(0x330);
			if(data == 0xFE) {
				_hardwareOk = true;
				break;
			}
		}
	}
	if(_hardwareOk) {
		_hardwareOk = false;
		//read status before setting mode
		while(inp(0x331) & 0x40) {}
		//set UART mode
		outp(0x331, 0x3F);
		for(int i = 0; i < 0xFFFF; ++i) {
			status = inp(0x331);
			if(!(status & 0x80)) {
				data = inp(0x330);
				if(data == 0xFE) {
					_hardwareOk = true;
					break;
				}
			}
		}
	}
}
MidiDevice::~MidiDevice() {
	if(_hardwareOk) {
		//read status before setting mode
		while(inp(0x331) & 0x40) {}
		// reset mode
		outp(0x331, 0xFF);
		for(int i = 0; i < 0xFFFF; ++i) {
			status = inp(0x331);
			if(!(status & 0x80)) {
				data = inp(0x330);
				if(data == 0xFE) break;
			}
		}
	}
}
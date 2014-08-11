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
#include "MidiBoss.hpp"
#include "MPU.hpp"
#include "Vox.hpp"
#include <iostream>

#define NOTE_ON 0x90
#define NOTE_OFF 0x80
#define CC_CHANGE 0xB0
#define PITCHBEND 0xE0
typedef std::vector<Vox*>::iterator InstrIter;

void MidiBoss::addInstrument(Vox* p) {
	_instruments.push_back(p);
}
void MidiBoss::updateModulation(int ticks) {
	for(InstrIter it = _instruments.begin(); it != _instruments.end(); ++it) {
		(*it)->update(ticks);
	}
}
void MidiBoss::pollEvents() {
	if(_dev->dataReady()) {
		unsigned char midi_byte = _dev->read();
		if(midi_byte == 0xF8) {
			updateModulation(1);
			return;
		}
		int i;
		switch(_state) {
			case BYTE_CHANNEL:
				if( (midi_byte >= 0x80) && (midi_byte < 0xF0) ) { 
					_channel = midi_byte & 0x0F;
					_command = midi_byte & 0xF0;
					_state = BYTE_NOTE;
				}
				break;
			case BYTE_NOTE:
				_note = midi_byte;
				_state = BYTE_VELOCITY;
				break;
			case BYTE_VELOCITY:
				_velocity = midi_byte;
				_offset = (int(_note) | ( int(_velocity) << 7)) - 8192;
				switch(_command) {
					case NOTE_OFF:
						_velocity = 0; //note-off and note-on with zero velocity are synonyms.
					case NOTE_ON:
						for(InstrIter it = _instruments.begin(); it != _instruments.end(); ++it) {
							if((*it)->getParameter(Vox::P_NOTE_CHANNEL) == _channel && _note >= (*it)->getParameter(Vox::P_FIRST_KEY) && _note <= (*it)->getParameter(Vox::P_LAST_KEY)) {
								if(_velocity ==0) {
									(*it)->stopNote(_note + (*it)->getParameter(Vox::P_TRANSPOSE)*12);
								} else {
									(*it)->playNote(_note + (*it)->getParameter(Vox::P_TRANSPOSE)*12, _velocity);
								}
							}
						}
						break;
                    case CC_CHANGE:
						for(InstrIter it = _instruments.begin(); it != _instruments.end(); ++it) {
							if((*it)->getParameter(Vox::P_CC_CHANNEL) == _channel) {
								(*it)->setParameter(_note, _velocity + (*it)->getParameterMin(_note)); //id and position of continous controller
							}
						}
                        break;
					case PITCHBEND:
						for(InstrIter it = _instruments.begin(); it != _instruments.end(); ++it) {
							if((*it)->getParameter(Vox::P_NOTE_CHANNEL) == _channel) {
								(*it)->pitchBend(_offset);
							}
						}
				}
				_state = BYTE_CHANNEL;
		}
	}
}
void MidiBoss::init(MPU* dev) {
	_dev = dev;
}
MidiBoss::MidiBoss() {
	_state = BYTE_CHANNEL;
}
MidiBoss::~MidiBoss() {
}

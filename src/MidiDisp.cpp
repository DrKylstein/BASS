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
#include "MidiDisp.hpp"
#include "MidiDev.hpp"
#include "AbstInst.hpp"
#include <iostream>
void MidiDispatcher::addInstrument(AbstractInstrument* p) {
	if(_numInstruments < MAXINSTS) {
		_instruments[_numInstruments] = p;
		++_numInstruments;
	}
}
void MidiDispatcher::updateModulation(int ticks) {
	for(int i = 0; i < _numInstruments; ++i) {
		_instruments[i]->update(ticks);
	}
}
void MidiDispatcher::pollEvents() {
	if(_dev->dataReady()) {
		unsigned char midi_byte = _dev->read();
		if(midi_byte == 0xF8) {
			//std::cout << "tick!" << std::endl;
			updateModulation(1);
			return;
		}
		int i;
		switch(_state) {
			case 0:
				//std::cout << int(_command) << ", " << std::endl;
				if( (midi_byte >= 0x80) && (midi_byte < 0xF0) ) { 
					_channel = midi_byte & 0x0F;
					_command = midi_byte & 0xF0;
					++_state;
				}
				break;
			case 1:
				_note = midi_byte;
				//std::cout << int(_note) << ", " << std::endl;
				++_state;
				break;
			case 2:
				_velocity = midi_byte;
				_offset = (int(_note) | ( int(_velocity) << 7)) - 8192;
				//std::cout << int(_velocity) << std::endl;
				switch(_command) {
					case 0x80:
						_velocity = 0; //note-off and note-on with zero velocity are synonyms.
					case 0x90:
						for(i=0; i < _numInstruments; ++i) {
							if(_instruments[i]->channel == _channel && _note >= _instruments[i]->startingNote && _note <= _instruments[i]->endingNote) {
								if(_velocity ==0) {
									//std::cout << "stop note on " << i << std::endl;
									_instruments[i]->stopNote(_note + _instruments[i]->transpose);
								} else {
									//std::cout << "start note on " << i << std::endl;
									_instruments[i]->playNote(_note + _instruments[i]->transpose, _velocity);
								}
							}
						}
						break;
                    case 0xB0:
						for(i=0; i < _numInstruments; ++i) {
							if(_instruments[i]->channel == _channel) {
								_instruments[i]->cc(_note, _velocity); //id and position of continous controller
							}
						}
                        break;
					case 0xE0:
						for(i=0; i < _numInstruments; ++i) {
							if(_instruments[i]->channel == _channel) {
								_instruments[i]->pitchBend(_offset);
							}
						}
						//break;
				}
				_state = 0;
		}
	}
}
void MidiDispatcher::init(MidiDevice* dev) {
	_dev = dev;
	if(_dev->isDetected()) {
		std::cout << "Using MPU401." <<std::endl;
	} else {
		std::cout << "No Midi hardware detected!" << std::endl;
	}
}
MidiDispatcher::MidiDispatcher() {
	//_dev = new MidiDevice();
	_state = 0;
	_numInstruments = 0;
}
MidiDispatcher::~MidiDispatcher() {
}

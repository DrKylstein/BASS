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
void MidiDispatcher::init() {
	_dev = new MidiDevice();
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
	if(_dev != 0) delete _dev;
}

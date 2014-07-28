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
#ifndef MIDIDISPATCHER_HPP
#define MIDIDISPATCHER_HPP
#include <vector>
class MidiDevice;
class AbstractInstrument;
class MidiDispatcher {
	public:
		void init(MidiDevice* dev);
		void addInstrument(AbstractInstrument*);
		void pollEvents();
		void updateModulation(int ticks);
	
		MidiDispatcher();
		~MidiDispatcher();
	
	private:
		std::vector<AbstractInstrument*> _instruments;
		MidiDevice* _dev;
        enum {
            BYTE_CHANNEL,
            BYTE_NOTE,
            BYTE_VELOCITY
		} _state;
	
		unsigned char _channel;
		unsigned char _command;
		unsigned char _note;
		unsigned char _velocity;
		signed int _offset;
};
#endif

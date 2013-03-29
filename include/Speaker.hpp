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
#ifndef SPEAKER_HPP
#define SPEAKER_HPP
#include <conio>
#define PIT_COUNTER_TWO	0x42
#define PIT_MODE			0x43
#define PPI_CONTROL		0x61

class Speaker {	
	public:
		inline void setFrequency(unsigned long int freq) {
			setTimer( 1193180 / freq );
		}
		inline void setTimer(unsigned short int t) {
			bool noteState = _noteOn;
			disconnect();
			outp(PIT_MODE, 0xB6);
			outp(PIT_COUNTER_TWO, t & 0xFF);
			outp(PIT_COUNTER_TWO, (t & 0xFF00) >> 8);
			if(noteState) {connect();}
		}
		inline void disconnect() {
			if(_noteOn) {
				outp(PPI_CONTROL, inp(PPI_CONTROL) & 0xFC);
				_noteOn = false;
			}
		}
		inline void connect() {
			if(!_noteOn) {
				outp(PPI_CONTROL, inp(PPI_CONTROL) | 0x03);
				_noteOn = true;
			}
		}
		inline bool isConnected() {return _noteOn;}
		inline Speaker() {
			_noteOn = false;
		}
		inline ~Speaker() {
			disconnect();
		}
		
	private:
		bool _noteOn;
};
#endif
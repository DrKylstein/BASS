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
#ifndef BEEPER_INSTRUMENT_HPP
#define BEEPER_INSTRUMENT_HPP
#include "Speaker.hpp"
#include "AbstInst.hpp"
class Speaker;
class BeeperInstrument: public AbstractInstrument {
	public:
		void playNote(unsigned char note, unsigned char velocity);
		void stopNote(unsigned char note);
		void pitchBend(signed int offset);
		void pressureChangeNote(unsigned char note, unsigned char pressure);
		void silence();
		void update(int ticks);
	
		BeeperInstrument();
		~BeeperInstrument();
	private:
		static const unsigned short int _timingTable[2048];
		Speaker _speaker;
		unsigned char _currentNote;
		signed short _currentBend;
		unsigned int _tremoloStep;
};
#endif

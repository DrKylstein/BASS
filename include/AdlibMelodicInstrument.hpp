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
#ifndef ADLIB_MELODIC_INSTRUMENT_HPP
#define ADLIB_MELODIC_INSTRUMENT_HPP
#include "OPLDriver.hpp"
#include "AbstInst.hpp"
#define MAX_POLYPHONY 9
class AdlibMelodicInstrument: public AbstractInstrument {
	public:
		void playNote(unsigned char note, unsigned char velocity);
		void stopNote(unsigned char note);
		void pitchBend(signed int offset);
		void pressureChangeNote(unsigned char note, unsigned char pressure);
		void silence();
        void cc(unsigned char id, unsigned char value);
	
		AdlibMelodicInstrument(OPLDriver* driver, int firstChannel, int channelCount);
		~AdlibMelodicInstrument();
	private:
		unsigned char _notes[MAX_POLYPHONY]; //list of all the currently playing notes
		unsigned char _ages[MAX_POLYPHONY]; //age of corresponding notes, 0 is the oldest.
		int _notesHeld;
		OPLDriver* _driver;
        int _firstChannel, _channelCount;
        unsigned char _attack[2], _decay[2], _sustain[2], _release[2], _fmFactor;
        unsigned char _freqMult[2];
        bool _sustainEnable[2], _fmEnable;
        void _updateEnvelope();
        void _updateFlags();
        void _updateFM();
    
};
#endif

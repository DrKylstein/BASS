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
#include "ControlPanel.hpp"
#define MAX_POLYPHONY 9


class AdlibMelodicInstrument: public AbstractInstrument {
	public:
		void playNote(unsigned char note, unsigned char velocity);
		void stopNote(unsigned char note);
		void pitchBend(signed int offset);
		void pressureChangeNote(unsigned char note, unsigned char pressure);
		void silence();
        void cc(unsigned char id, unsigned char value);
        void setParameter(unsigned char id, unsigned char value);
        void resetParameters();
    
        static const int PARAMETER_COUNT = 22;
    
		AdlibMelodicInstrument(OPLDriver* driver, int firstChannel, int channelCount, ControlPanel* panel);
		~AdlibMelodicInstrument();
	private:
		unsigned char _notes[MAX_POLYPHONY]; //list of all the currently playing notes
		unsigned char _ages[MAX_POLYPHONY]; //age of corresponding notes, 0 is the oldest.
		int _notesHeld;
		OPLDriver* _driver;
        int _firstChannel, _channelCount;
        int _currentProgram;
        ControlPanel* _panel;
};
#endif

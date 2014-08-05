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
#ifndef FMVOX_HPP
#define FMVOX_HPP
#include "FMDriver.hpp"
#include "Vox.hpp"
#include "Pane.hpp"
#define MAX_POLYPHONY 9


class FMVox: public Vox {
	public:
		void playNote(unsigned char note, unsigned char velocity);
		void stopNote(unsigned char note);
		void pitchBend(signed int offset);
		void pressureChangeNote(unsigned char note, unsigned char pressure);
		void silence();
        void cc(unsigned char id, unsigned char value);
        void setParameter(int id, int value);
        void resetParameters();
    
        enum {
            P_AM = P_CUSTOM,
            P_FEEDBACK,
            P_TREMOLO_DEPTH,
            P_VIBRATO_DEPTH,
            P_MOD_ATTACK,
            P_MOD_DECAY,
            P_MOD_SUSTAIN,
            P_MOD_RELEASE,
            P_MOD_VOLUME,
            P_MOD_FREQMULT,
            P_MOD_WAVE,
            P_MOD_TREMOLO,
            P_MOD_VIBRATO,
            P_MOD_HOLD,
            P_CARRIER_ATTACK,
            P_CARRIER_DECAY,
            P_CARRIER_SUSTAIN,
            P_CARRIER_RELEASE,
            P_CARRIER_VOLUME,
            P_CARRIER_FREQMULT,
            P_CARRIER_WAVE,
            P_CARRIER_TREMOLO,
            P_CARRIER_VIBRATO,
            P_CARRIER_HOLD,
            PARAMETER_COUNT
        };
    
		FMVox(FMDriver* driver, int firstChannel, int channelCount, Pane* panel);
		~FMVox();
	private:
		unsigned char _notes[MAX_POLYPHONY]; //list of all the currently playing notes
		unsigned char _ages[MAX_POLYPHONY]; //age of corresponding notes, 0 is the oldest.
		int _notesHeld;
        int _bend;
		FMDriver* _driver;
        int _firstChannel, _channelCount;
        int _currentProgram;
        Pane* _panel;
};
#endif

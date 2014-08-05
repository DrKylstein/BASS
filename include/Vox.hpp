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
#ifndef VOX_HPP
#define VOX_HPP
class Vox {
	public:
		virtual void playNote(unsigned char note, unsigned char velocity) = 0;
		virtual void stopNote(unsigned char note) = 0;
		virtual void silence() = 0;
    
		virtual void pitchBend(signed int offset) {};
		virtual void pressureChangeNote(unsigned char note, unsigned char pressure) {};
        virtual void cc(unsigned char id, unsigned char value) {};
		virtual void update(int ticks) {};
        virtual void programChange(int program) {};
            
        virtual void resetParameters() {};
        virtual void setParameter(int id, unsigned char value) {};
            
		unsigned char channel, ccChannel, startingNote, endingNote, transpose;
};
#endif

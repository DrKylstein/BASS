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
        //abstract
		virtual void playNote(unsigned char note, unsigned char velocity) = 0;
		virtual void stopNote(unsigned char note) = 0;
		virtual void silence() = 0;
		virtual void pitchBend(signed int offset) = 0;
    
        //abstract optional
		virtual void pressureChangeNote(unsigned char note, unsigned char pressure) {};
		virtual void update(int ticks) {};
        
        //concrete
        int getParameterMax(int id);
        int getParameterMin(int id);
        void setParameter(int id, int value);
        int getParameter(int id);
            
        enum {
            P_NOTE_CHANNEL,
            P_CC_CHANNEL,
            P_TRANSPOSE,
            P_FIRST_KEY,
            P_LAST_KEY,
            P_CUSTOM
        };

    protected:
        virtual int getCustomParameterMax(int id) = 0;
        virtual int getCustomParameterMin(int id) = 0;
        virtual void updateParameterDisplay(int id, int value) = 0;
        virtual void setCustomParameter(int id, int value) = 0;
        virtual int getCustomParameter(int id) = 0;
    
    private:
        int constrain(int v, int l, int h);
        unsigned char channel, ccChannel, startingNote, endingNote;
        int transpose;
};
#endif

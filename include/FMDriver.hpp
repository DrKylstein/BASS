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
#ifndef FMDRIVER_HPP
#define FMDRIVER_HPP
#include <cstdint>
class FMDriver {
    public:
        static const int CHANNEL_COUNT = 9;
        static const int OPERATOR_COUNT = 18;
        static const int MAX_VOLUME = 0x3F;
        FMDriver();
        ~FMDriver();
        void reset();
    
        void setTremoloDepth(bool high);
        void setVibratoDepth(bool low);
    
        void keyOn(int channel, int freq);
        void keyOff(int channel);
        void setFrequency(int channel, int freq);
        void setAM(int channel, bool am);
    
        void setFeedback(int channel, int factor);
        void setVolume(int channel, int op, int level);
        void setAttack(int channel, int op, int attack);
        void setDecay(int channel, int op, int decay);
        void setSustain(int channel, int op, int sustain);
        void setRelease(int channel, int op, int release);
        void setTremolo(int channel, int op, bool tremolo);
        void setVibrato(int channel, int op, bool vibrato);
        void setHold(int channel, int op, bool sustain);
        void setScaling(int channel, int op, bool ksr);
        void setFreqMult(int channel, int op, int fmult);
        void setWaveform(int channel, int op, int type);
        
        
        //for debugging only
        int getReg(int id);
        
    private:
        void write(int reg, int value);
        int read(int reg);
        void _update(int reg);
        int _opIndex(int ch, int op);
        void _setBit(int reg, int bit, bool value);
        std::uint16_t _ioBase;
        std::uint8_t _regs[0xF6];
    
};
#endif

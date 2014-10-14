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
#ifndef BEEPPANE_HPP
#define BEEPPANE_HPP
#include "Pane.hpp"
class BeepVox;
class BeepPane : public Pane {
    public:
        BeepPane(TextMode* screen);
        ~BeepPane();
        void updateParameter(int id, int value);
        void drawStatic();
        void redrawParameters();
        int getBottom();
    
        std::pair<int, int> getPosition(int item);
        int getParameterCount();
        void submitParameter(int id, int value);
    
        void setVoice(BeepVox* voice);
    private:
        static const int PARAMETER_COUNT = 5;
        static const unsigned char _positions[BeepPane::PARAMETER_COUNT][2];
        static const char* BeepPane::_labels[BeepPane::PARAMETER_COUNT];
        TextMode* _screen;
        int _lastPos;
        int _values[PARAMETER_COUNT];
        BeepVox* _voice;
};
#endif
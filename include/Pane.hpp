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
#ifndef PANE_HPP
#define PANE_HPP
#include "TextMode.hpp"
#include <utility>
class Pane {
    public:
        virtual void updateParameter(int id, int value) = 0;
        virtual void drawStatic() = 0;
        virtual int getBottom() = 0;
        int getTop();
    
        virtual std::pair<int, int> getPosition(int item) = 0;
        virtual int getParameterCount() = 0;
    
        void insertAfter(Pane& p);
        void dettach();
        Pane* getNext();
        Pane* getPrevious();
    protected:
        void _clearLinks();
    private:
        Pane* _next;
        Pane* _previous;
};
#endif
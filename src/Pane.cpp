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
#include "Pane.hpp"
int Pane::getTop() {
    if(getPrevious())
        return getPrevious()->getBottom();
    return 0;
}

void Pane::insertAfter(Pane& p) {
    _next = p._next;
    _previous = &p;
    p._next = this;
}
void Pane::dettach() {
    _next->_previous = _previous;
    _previous->_next = _next;
    _next = 0;
    _previous = 0;
}
Pane* Pane::getNext() {
    return _next;
}
Pane* Pane::getPrevious() {
    return _previous;
}

void Pane::_clearLinks() {
    _next = _previous = 0;
}

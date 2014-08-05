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
#include "Cursor.hpp"
using std::uint8_t;
Cursor::Cursor() {
    uint8_t x, y;
    uint8_t top, bottom;
    _asm {
        mov ah, 03h
        mov bh, 00h
        int 10h
        mov x, dl
        mov y, dh
        mov top, ch
        mov bottom, cl
    }
    _x = x;
    _y = y;
    _top = top;
    _bottom = bottom;
}
void Cursor::moveTo(uint8_t x, uint8_t y) {
    _x = x;
    _y = y;
    _asm {
        mov ah, 2
        mov bh, 0
        mov dl, x
        mov dh, y
        int 10h
    }
}
void Cursor::moveBy(uint8_t x, uint8_t y) {
    moveTo(_x+x,_y+y);
}
void Cursor::hide() {
    _asm {
        mov ah, 1h
        mov ch, 00100000b
        mov cl, 0
        int 10h
    }
}
void Cursor::show() {
    uint8_t top = _top;
    uint8_t bottom = _bottom;
    _asm {
        mov ah, 1h
        mov ch, top
        mov cl, bottom
        int 10h
    }
}
void Cursor::setHeight(int h) {
    _top = _bottom - h;
    uint8_t top = _top;
    uint8_t bottom = _bottom;
    _asm {
        mov ah, 1h
        mov ch, top
        mov cl, bottom
        int 10h
    }
}
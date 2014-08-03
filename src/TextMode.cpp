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
#include "TextMode.hpp"
#include <dos.h>

using std::strlen;

TextMode::TextMode() {
    _asm {
        mov bl, 0
        mov ax, 1003h
        int 10h
    }
    mScreen = (uint16_t far*)MK_FP(0xB800,0);
}

void TextMode::print(std::string str, uint8_t attrib, int x, int y) {
    int i = 0;
    for (std::string::iterator it=str.begin(); it!=str.end(); ++it) {
        mScreen[y*80 + x + i++] = (*it) | ((uint16_t)attrib << 8);
    }
}
void TextMode::print(int num, uint8_t attrib, int x, int y) {
    int i = 0;
    do {
        mScreen[y*80 + x + i] = ((num % 10) + '0') | ((uint16_t)attrib << 8);
        num /= 10;
        i--;
    } while(num);
}
void TextMode::printHex(int num, uint8_t attrib, int x, int y) {
    int i = 0;
    do {
        char c = '0';
        if((num & 0xF) < 0xA) {
            c = (num & 0xF) + '0';
        } else {
            c = (num & 0xF) - 10 + 'A';
        }
        mScreen[y*80 + x + i] = c | ((uint16_t)attrib << 8);
        num >>= 4;
        i--;
    } while(num);
}

static const uint8_t BOX_CHARS[3][3] = {
    {0xC9,0xCD,0xBB},
    {0xBA,0x20,0xBA},
    {0xC8,0xCD,0xBC}
};

void TextMode::box(uint8_t attrib, int x, int y, int width, int height) {
    int lx = 1;
    int ly = 1;
    for(int dx = x; dx < x+width; dx++) {
        for(int dy = y; dy < y+height; dy++) {
            if(dx == x) {
                lx = 0;
            } else if(dx == x+width-1) {
                lx = 2;
            } else {
                lx = 1;
            }
            if(dy == y) {
                ly = 0;
            } else if(dy == y+height-1) {
                ly = 2;
            } else {
                ly = 1;
            }
            if(lx != 1 || ly != 1) {
                mScreen[dy*80 + dx] = BOX_CHARS[ly][lx] | ((uint16_t)attrib << 8);
            }
        }
    }
}
void TextMode::setAttrib(uint8_t attrib, int x, int y, int width, int height) {
    for(int dx = 0; dx < width; dx++) {
        for(int dy = 0; dy < height; dy++) {
            mScreen[(y+dy)*80 + x + dx] |= ((uint16_t)attrib << 8);
        }
    }
}

void TextMode::hbar(uint8_t attrib, int x, int y, int width) {
    int lx = 1;
    int ly = 1;
    for(int dx = x; dx < x+width; dx++) {
        uint8_t symbol = 0xCD;
        if((mScreen[y*80 + dx] & 0x00FF) == 0xBA) {
            if(dx == x) {
                symbol = 0xCC;
            } else if(dx == x+width-1) {
                symbol = 0xB9;
            } else {
                symbol = 0xCE;
            }
        }
        mScreen[y*80 + dx] = symbol | ((uint16_t)attrib << 8);
        
    }
}

void TextMode::fill(char c, uint8_t attrib, int x, int y, int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            mScreen[(y+i)*80 + x + j] = c | ((uint16_t)attrib << 8);
        }
    }
}

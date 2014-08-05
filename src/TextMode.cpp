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
#include <cassert>

using std::strlen;

bool TextMode::_exists = false;

TextMode::TextMode() {
    assert(!_exists);
    _exists = true;
    //turn off blinking
    REGS inputRegisters, resultRegisters;
    inputRegisters.x.ax = 0x1003;
    inputRegisters.h.bl = 0;
    int86(0x10, &inputRegisters, &resultRegisters);

    mScreen = (uint16_t far*)MK_FP(0xB800,0);
}
TextMode::TextMode(TextMode&) {
    assert(true);
}
TextMode::~TextMode() {
    //reset video mode
    REGS inputRegisters, resultRegisters;
    inputRegisters.x.ax = 0x0003;
    int86(0x10, &inputRegisters, &resultRegisters);
}
void TextMode::print(char c, uint8_t attrib, int x, int y) {
    mScreen[y*80 + x] = c | ((uint16_t)attrib << 8);
}
uint16_t TextMode::get(int x, int y) {
    return mScreen[y*80 + x];
}

void TextMode::print(std::string str, uint8_t attrib, int x, int y) {
    for (std::string::iterator it=str.begin(); it!=str.end(); ++it) {
        print((*it), attrib, x, y);
        x++;
    }
}
void TextMode::print(int num, uint8_t attrib, int x, int y) {
    do {
        print((char)((num % 10) + '0'), attrib, x, y);
        num /= 10;
        x--;
    } while(num);
}
void TextMode::printHex(int num, uint8_t attrib, int x, int y) {
    do {
        char c = '0';
        if((num & 0xF) < 0xA) {
            c = (num & 0xF) + '0';
        } else {
            c = (num & 0xF) - 10 + 'A';
        }
        print(c, attrib, x, y);
        num >>= 4;
        x--;
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
                print(BOX_CHARS[ly][lx], attrib, dx, dy);
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
        if((get(dx, y) & 0x00FF) == 0xBA) {
            if(dx == x) {
                symbol = 0xCC;
            } else if(dx == x+width-1) {
                symbol = 0xB9;
            } else {
                symbol = 0xCE;
            }
        }
        print((char)symbol, attrib, dx, y);
    }
}

void TextMode::fill(char c, uint8_t attrib, int x, int y, int width, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            print(c, attrib, x+j, y+i);
        }
    }
}

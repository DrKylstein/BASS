#include "TextScreen.hpp"
#include <dos.h>
#include <cstring>

using std::strlen;

TextScreen::TextScreen() {
    _asm {
        mov bl, 0
        mov ax, 1003h
        int 10h
    }
    mScreen = (uint16_t far*)MK_FP(0xB800,0);
    _fmemset(mScreen, 0, 4000);
}
TextScreen::TextScreen(uint16_t far* screen) {
    mScreen = screen;
}

TextScreen TextScreen::subScreen(int x, int y) {
    return TextScreen(mScreen+x+y*80);
}

void TextScreen::print(std::string str, uint8_t attrib, int x, int y) {
    int i = 0;
    for (std::string::iterator it=str.begin(); it!=str.end(); ++it) {
        mScreen[y*80 + x + i++] = (*it) | ((uint16_t)attrib << 8);
    }
}
void TextScreen::print(int num, uint8_t attrib, int x, int y) {
    int i = 0;
    do {
        mScreen[y*80 + x + i] = ((num % 10) + '0') | ((uint16_t)attrib << 8);
        num /= 10;
        i--;
    } while(num);
}

static const uint8_t BOX_CHARS[3][3] = {
    {0xC9,0xCD,0xBB},
    {0xBA,0x20,0xBA},
    {0xC8,0xCD,0xBC}
};

void TextScreen::box(uint8_t attrib, int x, int y, int width, int height) {
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
void TextScreen::hbar(uint8_t attrib, int x, int y, int width) {
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

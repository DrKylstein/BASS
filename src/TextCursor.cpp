#include "TextCursor.hpp"
using std::uint8_t;
TextCursor::TextCursor() {
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
void TextCursor::moveTo(uint8_t x, uint8_t y) {
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
void TextCursor::moveBy(uint8_t x, uint8_t y) {
    moveTo(_x+x,_y+y);
}
void TextCursor::hide() {
    _asm {
        mov ah, 1h
        mov ch, 00100000b
        mov cl, 0
        int 10h
    }
}
void TextCursor::show() {
    uint8_t top = _top;
    uint8_t bottom = _bottom;
    _asm {
        mov ah, 1h
        mov ch, top
        mov cl, bottom
        int 10h
    }
}

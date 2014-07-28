#include <dos.h>
#include <conio.h>
#include "PCKeyboard.hpp"

#define KB_STATUS 0x64
#define KB_COMMAND 0x64
#define KB_DATA 0x60

#define KBCOMMAND_READ_REGISTER 0x20
#define KBCOMMAND_WRITE_REGISTER 0x60
#define KBCOMMAND_READ_SCANCODE 0xC0

#define KBSTATUS_INPUT_FULL 0x01

#define SCANCODE_PRESSED_FLAG 0x80
#define SCANCODE_MASK 0x7F
#define ESCAPE_CODE   0xE0

static volatile bool PCKeyboard::_state[NUM_STATES];
static volatile bool PCKeyboard::_pressed[NUM_STATES];
static volatile bool PCKeyboard::_anyKey = false;
static volatile bool PCKeyboard::_codeEscaped = false;
static interrupt_ptr PCKeyboard::prev_int_9 = 0;

PCKeyboard::PCKeyboard() {
    prev_int_9 = _dos_getvect(9);
    _dos_setvect(9, keyboard_int);
}
PCKeyboard::~PCKeyboard() {
    _dos_setvect(9, prev_int_9);
}

bool PCKeyboard::isHeld(KeySym::type k) {
    return _state[k];
}
bool PCKeyboard::wasPressed(KeySym::type k) {
    bool val = _pressed[k];
    _pressed[k] = false;
    return val;
}
bool PCKeyboard::anyKey() {
    bool val = _anyKey;
    _anyKey = false;
    return val;
}

static void __interrupt __far PCKeyboard::keyboard_int() {
    while(inp(KB_STATUS) & KBSTATUS_INPUT_FULL) {
        outp(KB_COMMAND, KBCOMMAND_READ_SCANCODE);
        int data = inp(KB_DATA);
        if(data == ESCAPE_CODE) {
            _codeEscaped = true;
            continue;
        }
        _anyKey = true;
        bool pressed = !bool(data & SCANCODE_PRESSED_FLAG);
        int scanCode = data & SCANCODE_MASK;
        if(_codeEscaped) {
            switch(scanCode) {
                case KeySym::enter:
                    scanCode = KeySym::kp_enter;
                    break;
                case KeySym::left_control:
                    scanCode = KeySym::right_control;
                    break;
                case KeySym::slash:
                    scanCode = KeySym::kp_slash;
                    break;
                case KeySym::left_alt:
                    scanCode = KeySym::right_alt;
                    break;
                case KeySym::kp_home:
                    scanCode = KeySym::home;
                    break;
                case KeySym::kp_up:
                    scanCode = KeySym::up;
                    break;
                case KeySym::kp_page_up:
                    scanCode = KeySym::page_up;
                    break;
                case KeySym::kp_left:
                    scanCode = KeySym::left;
                    break;
                case KeySym::kp_right:
                    scanCode = KeySym::right;
                    break;
                case KeySym::kp_end:
                    scanCode = KeySym::end;
                    break;
                case KeySym::kp_down:
                    scanCode = KeySym::down;
                    break;
                case KeySym::kp_page_down:
                    scanCode = KeySym::page_down;
                    break;
                case KeySym::kp_insert:
                    scanCode = KeySym::insert;
                    break;
                case KeySym::kp_delete:
                    scanCode = KeySym::delete_;
                    break;
            }
        }
        if(_state[scanCode] != pressed) {
            _state[scanCode] = pressed;
            if(pressed) {
                _pressed[scanCode] = true;
            }
        }

        _codeEscaped = false;
    }
    
    //_chain_intr(prev_int_9);
    //reset IRQ by temporarily setting bit 7
    int x = inp(0x61);
    outp(0x61, (x | 0x80));
    outp(0x61, x);
    
    //notify Programmable Interrupt Controller that we've finished
    outp(0x20, 0x20);
}

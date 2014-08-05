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
#include <dos.h>
#include <conio.h>
#include "PCKeys.hpp"

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

static volatile bool PCKeys::_state[NUM_STATES];
static volatile bool PCKeys::_pressed[NUM_STATES];
static volatile bool PCKeys::_anyKey = false;
static volatile bool PCKeys::_codeEscaped = false;
static interrupt_ptr PCKeys::prev_int_9 = 0;

PCKeys::PCKeys() {
    prev_int_9 = _dos_getvect(9);
    _dos_setvect(9, keyboard_int);
}
PCKeys::~PCKeys() {
    _dos_setvect(9, prev_int_9);
}

bool PCKeys::isHeld(KeySym::type k) {
    return _state[k];
}
bool PCKeys::wasPressed(KeySym::type k) {
    bool val = _pressed[k];
    _pressed[k] = false;
    return val;
}
bool PCKeys::anyKey() {
    bool val = _anyKey;
    _anyKey = false;
    return val;
}

static void __interrupt __far PCKeys::keyboard_int() {
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
    
    _chain_intr(prev_int_9);
    //reset IRQ by temporarily setting bit 7
    //int x = inp(0x61);
    //outp(0x61, (x | 0x80));
    //outp(0x61, x);
    
    //notify Programmable Interrupt Controller that we've finished
    //outp(0x20, 0x20);
}
int PCKeys::getDigit() {
    if(wasPressed(KeySym::zero)) {
        return 0;           
    } else if(wasPressed(KeySym::one)) {
        return 1;           
    } else if(wasPressed(KeySym::two)) {
        return 2;           
    } else if(wasPressed(KeySym::three)) {
        return 3;           
    } else if(wasPressed(KeySym::four)) {
        return 4;            
    } else if(wasPressed(KeySym::five)) {
        return 5;            
    } else if(wasPressed(KeySym::six)) {
        return 6;            
    } else if(wasPressed(KeySym::seven)) {
        return 7;            
    } else if(wasPressed(KeySym::eight)) {
        return 8;            
    } else if(wasPressed(KeySym::nine)) {
        return 9;           
    }
    return -1;
}

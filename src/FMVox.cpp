/*
 *  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 *  Soundblaster with MPU-401 UART compatible interfaces.
 *  Copyright (C) 2014  Kyle Delaney
 *
 *  This file is a part of BASS.
 *  Parts of this file are from the Chocolate Doom project, Copyright (C):
 *  1993-1996 Id Software, Inc.
 *  2005 Simon Howard
 *  Their contributions are inculded under the terms of the GPL.
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
#include "FMVox.hpp"
#include <conio.h>
#include <iostream>
#include <fstream>
#define NULL_NOTE 255

// Frequency values to use for each note.

static const unsigned short frequency_curve[] = {

	0x133, 0x133, 0x134, 0x134, 0x135, 0x136, 0x136, 0x137,   // -1
	0x137, 0x138, 0x138, 0x139, 0x139, 0x13a, 0x13b, 0x13b,
	0x13c, 0x13c, 0x13d, 0x13d, 0x13e, 0x13f, 0x13f, 0x140,
	0x140, 0x141, 0x142, 0x142, 0x143, 0x143, 0x144, 0x144,

	0x145, 0x146, 0x146, 0x147, 0x147, 0x148, 0x149, 0x149,   // -2
	0x14a, 0x14a, 0x14b, 0x14c, 0x14c, 0x14d, 0x14d, 0x14e,
	0x14f, 0x14f, 0x150, 0x150, 0x151, 0x152, 0x152, 0x153,
	0x153, 0x154, 0x155, 0x155, 0x156, 0x157, 0x157, 0x158,

	// These are used for the first seven MIDI note values:

	0x158, 0x159, 0x15a, 0x15a, 0x15b, 0x15b, 0x15c, 0x15d,   // 0
	0x15d, 0x15e, 0x15f, 0x15f, 0x160, 0x161, 0x161, 0x162,
	0x162, 0x163, 0x164, 0x164, 0x165, 0x166, 0x166, 0x167,
	0x168, 0x168, 0x169, 0x16a, 0x16a, 0x16b, 0x16c, 0x16c,

	0x16d, 0x16e, 0x16e, 0x16f, 0x170, 0x170, 0x171, 0x172,   // 1
	0x172, 0x173, 0x174, 0x174, 0x175, 0x176, 0x176, 0x177,
	0x178, 0x178, 0x179, 0x17a, 0x17a, 0x17b, 0x17c, 0x17c,
	0x17d, 0x17e, 0x17e, 0x17f, 0x180, 0x181, 0x181, 0x182,

	0x183, 0x183, 0x184, 0x185, 0x185, 0x186, 0x187, 0x188,   // 2
	0x188, 0x189, 0x18a, 0x18a, 0x18b, 0x18c, 0x18d, 0x18d,
	0x18e, 0x18f, 0x18f, 0x190, 0x191, 0x192, 0x192, 0x193,
	0x194, 0x194, 0x195, 0x196, 0x197, 0x197, 0x198, 0x199,

	0x19a, 0x19a, 0x19b, 0x19c, 0x19d, 0x19d, 0x19e, 0x19f,   // 3
	0x1a0, 0x1a0, 0x1a1, 0x1a2, 0x1a3, 0x1a3, 0x1a4, 0x1a5,
	0x1a6, 0x1a6, 0x1a7, 0x1a8, 0x1a9, 0x1a9, 0x1aa, 0x1ab,
	0x1ac, 0x1ad, 0x1ad, 0x1ae, 0x1af, 0x1b0, 0x1b0, 0x1b1,

	0x1b2, 0x1b3, 0x1b4, 0x1b4, 0x1b5, 0x1b6, 0x1b7, 0x1b8,   // 4
	0x1b8, 0x1b9, 0x1ba, 0x1bb, 0x1bc, 0x1bc, 0x1bd, 0x1be,
	0x1bf, 0x1c0, 0x1c0, 0x1c1, 0x1c2, 0x1c3, 0x1c4, 0x1c4,
	0x1c5, 0x1c6, 0x1c7, 0x1c8, 0x1c9, 0x1c9, 0x1ca, 0x1cb,

	0x1cc, 0x1cd, 0x1ce, 0x1ce, 0x1cf, 0x1d0, 0x1d1, 0x1d2,   // 5
	0x1d3, 0x1d3, 0x1d4, 0x1d5, 0x1d6, 0x1d7, 0x1d8, 0x1d8,
	0x1d9, 0x1da, 0x1db, 0x1dc, 0x1dd, 0x1de, 0x1de, 0x1df,
	0x1e0, 0x1e1, 0x1e2, 0x1e3, 0x1e4, 0x1e5, 0x1e5, 0x1e6,

	0x1e7, 0x1e8, 0x1e9, 0x1ea, 0x1eb, 0x1ec, 0x1ed, 0x1ed,   // 6
	0x1ee, 0x1ef, 0x1f0, 0x1f1, 0x1f2, 0x1f3, 0x1f4, 0x1f5,
	0x1f6, 0x1f6, 0x1f7, 0x1f8, 0x1f9, 0x1fa, 0x1fb, 0x1fc,
	0x1fd, 0x1fe, 0x1ff, 0x200, 0x201, 0x201, 0x202, 0x203,

	// First note of looped range used for all octaves:

	0x204, 0x205, 0x206, 0x207, 0x208, 0x209, 0x20a, 0x20b,   // 7
	0x20c, 0x20d, 0x20e, 0x20f, 0x210, 0x210, 0x211, 0x212,
	0x213, 0x214, 0x215, 0x216, 0x217, 0x218, 0x219, 0x21a,
	0x21b, 0x21c, 0x21d, 0x21e, 0x21f, 0x220, 0x221, 0x222,

	0x223, 0x224, 0x225, 0x226, 0x227, 0x228, 0x229, 0x22a,   // 8
	0x22b, 0x22c, 0x22d, 0x22e, 0x22f, 0x230, 0x231, 0x232,
	0x233, 0x234, 0x235, 0x236, 0x237, 0x238, 0x239, 0x23a,
	0x23b, 0x23c, 0x23d, 0x23e, 0x23f, 0x240, 0x241, 0x242,

	0x244, 0x245, 0x246, 0x247, 0x248, 0x249, 0x24a, 0x24b,   // 9
	0x24c, 0x24d, 0x24e, 0x24f, 0x250, 0x251, 0x252, 0x253,
	0x254, 0x256, 0x257, 0x258, 0x259, 0x25a, 0x25b, 0x25c,
	0x25d, 0x25e, 0x25f, 0x260, 0x262, 0x263, 0x264, 0x265,

	0x266, 0x267, 0x268, 0x269, 0x26a, 0x26c, 0x26d, 0x26e,   // 10
	0x26f, 0x270, 0x271, 0x272, 0x273, 0x275, 0x276, 0x277,
	0x278, 0x279, 0x27a, 0x27b, 0x27d, 0x27e, 0x27f, 0x280,
	0x281, 0x282, 0x284, 0x285, 0x286, 0x287, 0x288, 0x289,

	0x28b, 0x28c, 0x28d, 0x28e, 0x28f, 0x290, 0x292, 0x293,   // 11
	0x294, 0x295, 0x296, 0x298, 0x299, 0x29a, 0x29b, 0x29c,
	0x29e, 0x29f, 0x2a0, 0x2a1, 0x2a2, 0x2a4, 0x2a5, 0x2a6,
	0x2a7, 0x2a9, 0x2aa, 0x2ab, 0x2ac, 0x2ae, 0x2af, 0x2b0,

	0x2b1, 0x2b2, 0x2b4, 0x2b5, 0x2b6, 0x2b7, 0x2b9, 0x2ba,   // 12
	0x2bb, 0x2bd, 0x2be, 0x2bf, 0x2c0, 0x2c2, 0x2c3, 0x2c4,
	0x2c5, 0x2c7, 0x2c8, 0x2c9, 0x2cb, 0x2cc, 0x2cd, 0x2ce,
	0x2d0, 0x2d1, 0x2d2, 0x2d4, 0x2d5, 0x2d6, 0x2d8, 0x2d9,

	0x2da, 0x2dc, 0x2dd, 0x2de, 0x2e0, 0x2e1, 0x2e2, 0x2e4,   // 13
	0x2e5, 0x2e6, 0x2e8, 0x2e9, 0x2ea, 0x2ec, 0x2ed, 0x2ee,
	0x2f0, 0x2f1, 0x2f2, 0x2f4, 0x2f5, 0x2f6, 0x2f8, 0x2f9,
	0x2fb, 0x2fc, 0x2fd, 0x2ff, 0x300, 0x302, 0x303, 0x304,

	0x306, 0x307, 0x309, 0x30a, 0x30b, 0x30d, 0x30e, 0x310,   // 14
	0x311, 0x312, 0x314, 0x315, 0x317, 0x318, 0x31a, 0x31b,
	0x31c, 0x31e, 0x31f, 0x321, 0x322, 0x324, 0x325, 0x327,
	0x328, 0x329, 0x32b, 0x32c, 0x32e, 0x32f, 0x331, 0x332,

	0x334, 0x335, 0x337, 0x338, 0x33a, 0x33b, 0x33d, 0x33e,   // 15
	0x340, 0x341, 0x343, 0x344, 0x346, 0x347, 0x349, 0x34a,
	0x34c, 0x34d, 0x34f, 0x350, 0x352, 0x353, 0x355, 0x357,
	0x358, 0x35a, 0x35b, 0x35d, 0x35e, 0x360, 0x361, 0x363,

	0x365, 0x366, 0x368, 0x369, 0x36b, 0x36c, 0x36e, 0x370,   // 16
	0x371, 0x373, 0x374, 0x376, 0x378, 0x379, 0x37b, 0x37c,
	0x37e, 0x380, 0x381, 0x383, 0x384, 0x386, 0x388, 0x389,
	0x38b, 0x38d, 0x38e, 0x390, 0x392, 0x393, 0x395, 0x397,

	0x398, 0x39a, 0x39c, 0x39d, 0x39f, 0x3a1, 0x3a2, 0x3a4,   // 17
	0x3a6, 0x3a7, 0x3a9, 0x3ab, 0x3ac, 0x3ae, 0x3b0, 0x3b1,
	0x3b3, 0x3b5, 0x3b7, 0x3b8, 0x3ba, 0x3bc, 0x3bd, 0x3bf,
	0x3c1, 0x3c3, 0x3c4, 0x3c6, 0x3c8, 0x3ca, 0x3cb, 0x3cd,

	// The last note has an incomplete range, and loops round back to
	// the start.  Note that the last value is actually a buffer overrun
	// and does not fit with the other values.

	0x3cf, 0x3d1, 0x3d2, 0x3d4, 0x3d6, 0x3d8, 0x3da, 0x3db,   // 18
	0x3dd, 0x3df, 0x3e1, 0x3e3, 0x3e4, 0x3e6, 0x3e8, 0x3ea,
	0x3ec, 0x3ed, 0x3ef, 0x3f1, 0x3f3, 0x3f5, 0x3f6, 0x3f8,
	0x3fa, 0x3fc, 0x3fe, 0x36c,
};

// Mapping from MIDI volume level to OPL level value.

static const unsigned int volume_mapping_table[] = {
	0, 1, 3, 5, 6, 8, 10, 11,
	13, 14, 16, 17, 19, 20, 22, 23,
	25, 26, 27, 29, 30, 32, 33, 34,
	36, 37, 39, 41, 43, 45, 47, 49,
	50, 52, 54, 55, 57, 59, 60, 61,
	63, 64, 66, 67, 68, 69, 71, 72,
	73, 74, 75, 76, 77, 79, 80, 81,
	82, 83, 84, 84, 85, 86, 87, 88,
	89, 90, 91, 92, 92, 93, 94, 95,
	96, 96, 97, 98, 99, 99, 100, 101,
	101, 102, 103, 103, 104, 105, 105, 106,
	107, 107, 108, 109, 109, 110, 110, 111,
	112, 112, 113, 113, 114, 114, 115, 115,
	116, 117, 117, 118, 118, 119, 119, 120,
	120, 121, 121, 122, 122, 123, 123, 123,
	124, 124, 125, 125, 126, 126, 127, 127
};


static unsigned int NoteLookup(unsigned int note, int bend)
{
	unsigned int freq_index;
	unsigned int octave;
	unsigned int sub_index;

	freq_index = 64 + 32 * note + bend;

	// The first 7 notes use the start of the table, while
	// consecutive notes loop around the latter part.

	if (freq_index < 284)
	{
		return frequency_curve[freq_index];
	}

	sub_index = (freq_index - 284) % (12 * 32);
	octave = (freq_index - 284) / (12 * 32);

	// Once the seventh octave is reached, things break down.
	// We can only go up to octave 7 as a maximum anyway (the OPL
	// register only has three bits for octave number), but for the
	// notes in octave 7, the first five bits have octave=7, the
	// following notes have octave=6.  This 7/6 pattern repeats in
	// following octaves (which are technically impossible to
	// represent anyway).

	if (octave >= 7)
	{
		if (sub_index < 5)
		{
			octave = 7;
		}
		else
		{
			octave = 6;
		}
	}

	// Calculate the resulting register value to use for the frequency.

	return frequency_curve[sub_index + 284] | (octave << 10);
}

void FMVox::playNote(unsigned char note, unsigned char velocity) {
	for(int i = 0; i < _channelCount; ++i) {
		if(_notes[i] == NULL_NOTE) { //an empty channel! lets use that.
			_notes[i] = note;
			_ages[i] = _notesHeld;
			++_notesHeld;
			_driver->keyOn(_firstChannel+i, NoteLookup(note, 0));
			return;
		}
	}
	//no empty channels, kick out the oldest note
	for(int i = 0; i < _channelCount; ++i) {
		if(_ages[i] == 0) { //the oldest note, lets overwrite it.
			_notes[i] = note;
			_ages[i] = _notesHeld; //still the same number of notes held
			_driver->keyOn(_firstChannel+i, NoteLookup(note, _bend));
		} else { //age all the other notes by one. (next oldest (1) becomes oldest (0), etc.)
			--_ages[0];
		}
	}
}
void FMVox::stopNote(unsigned char note) {
	unsigned char removedAge = NULL_NOTE;
	for(int i = 0; i < _channelCount; ++i) {
		if(_notes[i] == note) {
            _driver->keyOff(_firstChannel+i);
			_notes[i] = NULL_NOTE;
			removedAge = _ages[i];
			_ages[i] = NULL_NOTE;
			--_notesHeld;
			break;
		}
	}
	if(removedAge != NULL_NOTE) { //shift all the younger notes back to fill the gap in ages
		for(int i=0; i < _channelCount; ++i) {
			if(_ages[i] != NULL_NOTE && _ages[i] > removedAge) {
				--_ages[i];
			}
		}
	}
}
void FMVox::pitchBend(signed int offset) {
    _bend = offset / 512;
    for(int i = 0; i < _channelCount; ++i) {
        if(_notes[i] != NULL_NOTE) {
            _driver->setFrequency(_firstChannel+i, NoteLookup(_notes[i], _bend));
        }
    }
}
void FMVox::pressureChangeNote(unsigned char note, unsigned char pressure) {
}
void FMVox::silence() {
	_notesHeld = 0;
	for(int i = 0; i < _channelCount; ++i) {
		if(_notes[i] != NULL_NOTE) {
			_driver->keyOff(_firstChannel+i);
		}
		_notes[i] = NULL_NOTE;
		_ages[i] = NULL_NOTE;
	}
}

void FMVox::resetParameters() {
	silence(); //to initialize the held note table
    for(int i = 0; i < PARAMETER_COUNT; i++) {
        setParameter(i, 0);
    }
}
static const int _divisors[FMVox::PARAMETER_COUNT] = {
    0,0,6,4,6,6,
    3,3,3,3,1,3,6,6,6,4,
    3,3,3,3,1,3,6,6,6,4
    
};

void FMVox::setParameter(int id, unsigned char value) {
    if(id >= PARAMETER_COUNT) return;
    _panel->updateParameter(id, value);
    switch(id) {
        case P_CC_CHANNEL:
            ccChannel = value;
            return;
        case P_NOTE_CHANNEL:
            channel = value;
            return;
        case P_TREMOLO_DEPTH:
            _driver->setTremoloDepth(value);
            return;
        case P_VIBRATO_DEPTH:
            _driver->setVibratoDepth(value);
            return;
    }
    for(int c = 0; c < _channelCount; c++) {
        switch(id) {
            case P_MOD_ATTACK:
                _driver->setAttack(_firstChannel+c, 0, value);
                break;
            case P_MOD_DECAY:
                _driver->setDecay(_firstChannel+c, 0, value);
                break;
            case P_MOD_SUSTAIN:
                _driver->setSustain(_firstChannel+c, 0, value);
                break;
            case P_MOD_RELEASE:
                _driver->setRelease(_firstChannel+c, 0, value);
                break;
            case P_MOD_VOLUME:
                _driver->setVolume(_firstChannel+c, 0, value);
                break;
            case P_MOD_FREQMULT:
                _driver->setFreqMult(_firstChannel+c, 0, value);
                break;
            case P_MOD_TREMOLO:
                _driver->setTremolo(_firstChannel+c, 0, value);
                break;
            case P_MOD_VIBRATO:
                _driver->setVibrato(_firstChannel+c, 0, value);
                break;
            case P_MOD_HOLD:
                _driver->setHold(_firstChannel+c, 0, value);
                break;
            
            case P_CARRIER_ATTACK:
                _driver->setAttack(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_DECAY:
                _driver->setDecay(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_SUSTAIN:
                _driver->setSustain(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_RELEASE:
                _driver->setRelease(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_VOLUME:
                _driver->setVolume(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_FREQMULT:
                _driver->setFreqMult(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_TREMOLO:
                _driver->setTremolo(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_VIBRATO:
                _driver->setVibrato(_firstChannel+c, 1, value);
                break;
            case P_CARRIER_HOLD:
                _driver->setHold(_firstChannel+c, 1, value);
                break;
            
            case P_AM:
                _driver->setAM(_firstChannel+c, value);
                break;
            case P_FEEDBACK:
                _driver->setFeedback(_firstChannel+c, value);
                break;
            
            case P_MOD_WAVE:
                _driver->setWaveform(_firstChannel+c, 0, value);
                break;
            case P_CARRIER_WAVE:
                _driver->setWaveform(_firstChannel+c, 1, value);
                break;
        }
    }
}

void FMVox::cc(unsigned char id, unsigned char value) {
    switch(id) {
        case 20:
            setParameter(P_MOD_ATTACK, value >> _divisors[P_MOD_ATTACK]);
            break;
        case 21:
            setParameter(P_MOD_DECAY, value >> _divisors[P_MOD_DECAY]);
            break;
        case 22:
            setParameter(P_MOD_SUSTAIN, value >> _divisors[P_MOD_SUSTAIN]);
            break;
        case 23:
            setParameter(P_MOD_RELEASE, value >> _divisors[P_MOD_RELEASE]);
            break;
        case 3:
            setParameter(P_MOD_VOLUME, value >> _divisors[P_MOD_VOLUME]);
            break;
        case 9:
            setParameter(P_MOD_FREQMULT, value >> _divisors[P_MOD_FREQMULT]);
            break;
        case 28:
            setParameter(P_MOD_TREMOLO, value >> _divisors[P_MOD_TREMOLO]);
            break;
        case 29:
            setParameter(P_MOD_VIBRATO, value >> _divisors[P_MOD_VIBRATO]);
            break;
        case 30:
            setParameter(P_MOD_HOLD, value >> _divisors[P_MOD_HOLD]);
            break;

        
        case 24:
            setParameter(P_CARRIER_ATTACK, value >> _divisors[P_CARRIER_ATTACK]);
            break;
        case 25:
            setParameter(P_CARRIER_DECAY, value >> _divisors[P_CARRIER_DECAY]);
            break;
        case 26:
            setParameter(P_CARRIER_SUSTAIN, value >> _divisors[P_CARRIER_SUSTAIN]);
            break;
        case 27:
            setParameter(P_CARRIER_RELEASE, value >> _divisors[P_CARRIER_RELEASE]);
            break;
        case 16:
            setParameter(P_CARRIER_VOLUME, value >> _divisors[P_CARRIER_VOLUME]);
            break;
        case 17:
            setParameter(P_CARRIER_FREQMULT, value >> _divisors[P_CARRIER_FREQMULT]);
            break;
        case 35:
            setParameter(P_CARRIER_TREMOLO, value >> _divisors[P_CARRIER_TREMOLO]);
            break;
        case 41:
            setParameter(P_CARRIER_VIBRATO, value >> _divisors[P_CARRIER_VIBRATO]);
            break;
        case 46:
            setParameter(P_CARRIER_HOLD, value >> _divisors[P_CARRIER_HOLD]);
            break;

        
        case 47:
            setParameter(P_AM, value >> _divisors[P_AM]);
            break;
        case 19:
            setParameter(P_FEEDBACK, value >> _divisors[P_FEEDBACK]);
            break;
        case 75:
            setParameter(P_TREMOLO_DEPTH, value >> _divisors[P_TREMOLO_DEPTH]);
            break;
        case 76:
            setParameter(P_VIBRATO_DEPTH, value >> _divisors[P_VIBRATO_DEPTH]);
            break;
        
        case 14:
            setParameter(P_MOD_WAVE, value >> _divisors[P_MOD_WAVE]);
            break;
        case 18:
            setParameter(P_CARRIER_WAVE, value >> _divisors[P_CARRIER_WAVE]);
            break;
        default:
            break;
    }
}
FMVox::FMVox(FMDriver* driver, int firstChannel, int channelCount, Pane* panel)
: _driver(driver), _firstChannel(firstChannel), _channelCount(channelCount), 
_panel(panel), _bend(0) {
}
FMVox::~FMVox() {
    silence();
}
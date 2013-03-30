/*
 *  BASS, a MIDI controled synthesizer for MSDOS systems using Adlib or 
 *  Soundblaster with MPU-401 UART compatible interfaces.
 *  Copyright (C) 2011  Kyle Delaney
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
#include <iostream>
#include "DebugIns.hpp"
void DebugInstrument::playNote(unsigned char note, unsigned char velocity)
{
	std::cout << "Note on: " << int(note) << " Velocity: " << int(velocity) << std::endl;
}
void DebugInstrument::stopNote(unsigned char note)
{
	std::cout << "Note off: " << int(note) << std::endl;
}
void DebugInstrument::pitchBend(signed int offset)
{
	std::cout << "Pitch Bend: " << offset << std::endl;
}
void DebugInstrument::pressureChangeNote(unsigned char note, unsigned char pressure)
{
	std::cout << "Aftertouch note: " << int(note) << " Pressure: " << int(pressure) << std::endl;
}
void DebugInstrument::silence()
{
	std::cout << "Silenced." << std::endl;
}
void DebugInstrument::cc(unsigned char id, unsigned char value) {
    std::cout << "CC ID:" << (int)id << " Value: " << (int)value << std::endl;
}

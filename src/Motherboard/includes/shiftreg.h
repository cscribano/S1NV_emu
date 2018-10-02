/*S1NV - a Space Invaders arcade emulator written in C++
    Copyright (C) 2018  Carmelo Scribano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see [http://www.gnu.org/licenses/].
.*/

#ifndef SHIFT_REG_H
#define SHIFT_REG_H

#include<iostream>
namespace shiftreg {

	uint16_t sd_data = 0x0000;
	uint8_t ofs = 0;

	void shift(uint8_t acc) {
		sd_data = (sd_data >> 8) | (acc << 8);

	}

	void setofs(uint8_t acc) {
		ofs = (acc & 0x7);
	}

	uint8_t read_reg() {
		return (sd_data >> (8-ofs))&0xFF;
	}

}
#endif // !SHIFT_REG_H

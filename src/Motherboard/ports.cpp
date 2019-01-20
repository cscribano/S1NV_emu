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

#include "includes/ports.h"
#include "includes/shiftreg.h"
#include "includes/keyboard.h"
#include"includes/sound.h"

//uint8_t IN_2() { return 0x00; }

/*

uint8_t(*in_port(uint8_t adr))() {
	switch (adr) {
	case 0:
		break;
	case 1:
		return keyboard::HandleInput;
	case 2:
		return keyboard::HandleInput2;
	case 3:
		return shiftreg::read_reg;
	default:
		break;
	}
	return NULL;
}*/

uint8_t in_port(uint8_t adr){
	switch(adr){
		case 0:
			break;
		case 1:
			return keyboard::HandleInput();
		case 2:
			return keyboard::HandleInput2();
		case 3:
			return shiftreg::read_reg();
		default:
			break;
	}
	return NULL;
}

void(*out_port(uint8_t adr))(uint8_t acc) {
	switch (adr) {
	case 2:
		return shiftreg::setofs;
	case 3:
		return snd::port_3;
		break;
	case 4:
		return shiftreg::shift;
	case 5:
		return snd::port_5;
		break;
	case 6:
		break;
	default:
		break;
	}
	return NULL;
}
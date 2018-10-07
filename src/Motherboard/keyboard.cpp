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

#include"includes/keyboard.h"
#include<iostream>

uint8_t keyboard::HandleInput(){
	const Uint8 *ks = SDL_GetKeyboardState(NULL);
	uint8_t ret = ks[SDL_SCANCODE_3] | ks[SDL_SCANCODE_2] << 1 | ks[SDL_SCANCODE_1] << 2 | 0x8 | ks[SDL_SCANCODE_SPACE] <<4 | ks[SDL_SCANCODE_LEFT] << 5 | ks[SDL_SCANCODE_RIGHT]<<6;
	return ret;
}

uint8_t keyboard::HandleInput2() {
	const Uint8 *ks = SDL_GetKeyboardState(NULL);
	uint8_t ret = (ks[SDL_SCANCODE_SPACE] << 4 | ks[SDL_SCANCODE_LEFT] << 5 | ks[SDL_SCANCODE_RIGHT] << 6)&0xFF;
	return ret;
}

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

uint8_t keyboard::HandleInput() {
	uint8_t ret = 0x8;

#ifdef __ANDROID__
    //SDL_TouchID device = SDL_GetTouchDevice(0);

    SDL_Finger *finger = SDL_GetTouchFinger(8, 0);

    if(finger == NULL)
    	ret = 0x8;
    else {
        if(finger->y < 0.7){ //top half of display
            if(finger->x > 0.5) //top right = insert coin
                ret = 0x9;
            else //top left = 1 player
             ret = 0xC;
        }
        else{//bottom half
            if(finger->x > 0.6) //bottom right = right
                ret = 0x48;
            else if(finger->x < 0.4) //bottom left = left
                ret = 0x28;
            else //bottom center = shoot
                ret = 0x18;
        }
    }
#else
	const Uint8 *ks = SDL_GetKeyboardState(NULL);
	ret = ks[SDL_SCANCODE_3] | ks[SDL_SCANCODE_2] << 1 | ks[SDL_SCANCODE_1] << 2 | 0x8 |
				  ks[SDL_SCANCODE_SPACE] << 4 | ks[SDL_SCANCODE_LEFT] << 5 |
				  ks[SDL_SCANCODE_RIGHT] << 6;
#endif

	return ret;

}

uint8_t keyboard::HandleInput2() {
	const Uint8 *ks = SDL_GetKeyboardState(NULL);
	uint8_t ret = (ks[SDL_SCANCODE_SPACE] << 4 | ks[SDL_SCANCODE_LEFT] << 5 | ks[SDL_SCANCODE_RIGHT] << 6)&0xFF;
	return ret;
}
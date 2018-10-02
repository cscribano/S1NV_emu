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

#ifndef SOUND_H
#define SOUND_H

#include<fstream>
#include<vector>
#include<string>
#include<SDL.h>
#include<SDL_mixer.h>

namespace snd {
	bool setup_sound(const char* folder = "SOUND");
	void port_3(uint8_t acc);
	void port_5(uint8_t acc);
};

#endif // !SOUND_H

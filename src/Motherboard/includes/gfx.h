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

#ifndef GFX_H
#define GFX_H

#include <SDL.h>

static int pxScale = 2;
static int width = 224;
static int height = 256;

class I8080;

class display {
private:
	SDL_Window *_window = NULL;
	SDL_Renderer *_renderer = NULL;
	SDL_Texture *_texture = NULL;

	I8080& cpu;
	uint8_t* _vram;
	uint8_t gfx_buffer[224 * 256]; //57344
	bool Vblank = true;
public:
	display(I8080& i);
	void draw_gfx();
	~display();
};


#endif // !GFX_H

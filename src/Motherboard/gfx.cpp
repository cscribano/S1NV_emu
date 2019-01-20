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

#include "includes/gfx.h"
#include"../CPU/includes/cpu.h"

#include<iostream>
#include<algorithm>

display::display(I8080& i) : cpu{ i } {

    _vram = &cpu.memory[0x2400];

#ifdef __ANDROID__

    SDL_DisplayMode displayMode;

	if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0){
		gScreenRect.w = displayMode.w;
		gScreenRect.h = displayMode.h;
	}
    _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );

#else
	_window = SDL_CreateWindow
	(
		"Still Testing : S1NV",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		//gScreenRect.h,
		//gScreenRect.w,
		width*pxScale,
		height*pxScale,
		SDL_WINDOW_OPENGL
	);
#endif

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(_renderer, width, height);

    _texture = SDL_CreateTexture(
		_renderer,
		SDL_PIXELFORMAT_RGB332,
		SDL_TEXTUREACCESS_STATIC,
		width,
		height
	);

}

void display::draw_gfx() {

	//7168 bytes -> 1bit pp
	int w = 256;
	int h = 224;
	size_t n = 0;
	size_t i = Vblank ? 0 : 3584;

	//0xE0
	for (int r = !Vblank ? 112 : 0; r < h; ++r) { //r
		for (int c = 0; c < w; ++c) { //c
			gfx_buffer[(w - c - 1)*h + r] = ((_vram[i] >> n) & 1) * 0xFF; //add color overlay
			++n;
			if (n == 8) {
				n = 0;
				++i;
			}
			if (i == 3584 && Vblank) { //draw first half
				Vblank = false;
				cpu.Interrupt(0xcf);
				return;
			}
		}
	}
	Vblank = true;
	cpu.Interrupt(0xd7);
	SDL_UpdateTexture(_texture, NULL, gfx_buffer, width * sizeof(uint8_t));
	SDL_RenderClear(_renderer);
	SDL_RenderCopy(_renderer, _texture, NULL, NULL);
	SDL_RenderPresent(_renderer);

}

display::~display() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyTexture(_texture);
}

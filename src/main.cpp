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

#include<SDL.h>
#include<SDL_timer.h>
#include<SDL_mixer.h>
#include<iostream>
#include<vector>

#include"CPU/includes/cpu.h"
#include"Motherboard/includes/gfx.h"
#include "Motherboard/includes/sound.h"

using namespace std;

int error(const char* message) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		"Error",
		message,
		NULL);

	return EXIT_FAILURE;
}

Uint32 UpdateTimersCB(Uint32 interval, void* param) {
	display *d = reinterpret_cast<display*>(param);
	d->draw_gfx();
	return 1000 / 120;
}


int main(int argc, char** argv) {
	bool di = false;
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		string err = "SDL could not initialize! SDL Error: " + string(SDL_GetError());
		return error(err.c_str());
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		string err = "SDL_mixer could not initialize! SDL_mixer Error: " + string(Mix_GetError());
		return error(err.c_str());
	}
	
	I8080 i(0x10000, 0x00);
	display d{ i }; //TO-DO: color overlay
	if (!snd::setup_sound()) {
		error("Can not initialize sound effects, game will be muted");
	}

	int bl = i.LoadRom("ROM/invaders.h", 0);
	bl += i.LoadRom("ROM/invaders.g", 0x0800);
	bl += i.LoadRom("ROM/invaders.f", 0x1000);
	bl += i.LoadRom("ROM/invaders.e", 0x1800);

	if (bl != 2048 * 4) {
		return error("Can not properly load ROMS/invaders.<h/g/f/e>\nPlease provide the proper ROM files\n");
	}
	
	bool loop = true;
	SDL_TimerID timerID = SDL_AddTimer(1000 / 120, UpdateTimersCB, reinterpret_cast<void*>(&d));

	while (loop) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				loop = false;
		}
		i.EmulateCycle(); //TO-DO: cycle counting @2MHz
	}

	//TO-DO: fix memory leaks (sound...)
	SDL_Quit();

	return EXIT_SUCCESS;
}
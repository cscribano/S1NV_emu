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

#include"includes/sound.h" 
#include<iostream>

using namespace std;

bool mute;
std::vector<Mix_Chunk*> effects;
uint8_t lastacc = 0x00;

bool snd::setup_sound(const char * folder) {
	mute = false;
	for (size_t i = 0; i < 9; ++i) {
		std::string filename = folder + std::string("/") + to_string(i) + std::string(".wav");
		auto effect = new Mix_Chunk;
		effect = Mix_LoadWAV(filename.c_str());
		if (!effect){
			mute = true;
			std::cout<<Mix_GetError()<<"-"<<filename.c_str()<<"\n";
		}
		effects.push_back(effect);
	}
	return !mute;
}

void snd::port_3(uint8_t acc) {
	for (size_t i = 0; i < 4; ++i) {

		uint8_t b = (acc >> i) & 1;
		if (b && !mute) {
			if (i == 0) {
				Mix_PlayChannel(-1, effects[i], 0);
			}
			else {
				if (b > ((lastacc >> i) & 1))
					Mix_PlayChannel(-1, effects[i], 0);
			}
		}
	}
	lastacc = acc;
}

void snd::port_5(uint8_t acc) {
	for (size_t i = 0; i < 5; ++i) {
		if ((acc >> i) & 1 && !mute)
			Mix_PlayChannel(-1, effects[i + 4], 0);
	}
}

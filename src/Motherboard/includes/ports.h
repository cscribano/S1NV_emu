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

#ifndef PORTS_H
#define PORTS_H

#include<iostream>

//uint8_t(*in_port(uint8_t adr))();

uint8_t in_port(uint8_t adr);
void(*out_port(uint8_t adr))(uint8_t acc);

#endif // !PORTS_H

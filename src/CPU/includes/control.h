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

#ifndef CONTROL_H
#define CONTROL_H

#include "cpu.h"
#include "../../Motherboard/includes/ports.h"

#include <utility>
//PUSH rp
#define PUSH(RH,RL) void PUSH##RH(I8080& i){\
	i.memory[i.SP - 1] = i.RH;\
	i.memory[i.SP - 2] = i.RL;\
	i.SP -= 2;\
}

PUSH(B,C) PUSH(D,E) PUSH(H,L) PUSH(S,P)

//PUSH PSW
void PUSH_PSW(I8080& i) {
	i.memory[i.SP - 1] = i.A;
	uint8_t p = PSW(i.CY_, 1, i.P_, 0, i.AC_, 0, i.Z_, i.S_);
	i.memory[i.SP - 2] = p;
	i.SP -= 2;
}

//POP rp
#define POP(RH,RL) void POP_##RH(I8080& i){\
	i.RL = i.memory[i.SP];\
	i.RH = i.memory[i.SP + 1];\
	i.SP += 2;\
}

POP(B,C) POP(D,E) POP(H,L) POP(S,P)

//POP psw
void POP_PSW(I8080& i) {
	uint8_t t = i.memory[i.SP];
	i.CY_ = t & 1;
	i.P_ = (t >> 2) & 1;
	i.AC_ = (t >> 4) & 1;
	i.Z_ = (t >> 6) & 1;
	i.S_ = (t >> 7) & 1;

	i.A = i.memory[i.SP + 1];
	i.SP += 2;
}

//XTHL
void XTHL(I8080& i) {
	std::swap(i.L, i.memory[i.SP]);
	std::swap(i.H, i.memory[i.SP + 1]);
}

//SPHL
void SPHL(I8080& i) {
	i.SP = i.HL;
}

//IN port
void IN(I8080& i) {

	if (in_port(i.I2) != NULL) {
		i.A = in_port(i.I2);
	}
}

//OUT port
void OUT(I8080 &i) {

	if (out_port(i.I2) != NULL) {
		out_port(i.I2)(i.A);
	}
}

//EI (Enable interrupt)
void EI(I8080& i) {
	i.EnableInterrput();
}

//DI (Disable Interrupt)
void DI(I8080& i) {
	i.IEnabled = false;
}

//HTL (Halt)
void HALT(I8080& i) {
	i.incrPC = false;
}

//NOP
void NOP(I8080& i) {
	//No operation
}

#endif // !CONTROL_H

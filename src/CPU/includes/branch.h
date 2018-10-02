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

#ifndef BRANCH_H
#define BRANCH_H

#include "cpu.h"

//JMP addr
void JMP(I8080& i) {
	i.PC = i.I;
	i.incrPC = false;
}

//Jcondition addr (+= 3??)
#define J(COND) void J##COND(I8080& i){\
	if (i.COND())\
		JMP(i);\
	else\
		i.PC += 3;\
	i.incrPC = false;\
}

J(_NZ) J(_Z) J(_NC) J(_C) J(_PO) J(_PE) J(_P) J(_M)

//CALL addr
void CALL(I8080& i) {

	i.PC += 3;
	i.memory[i.SP - 1] = i.PCH;
	i.memory[i.SP - 2] = i.PCL;
	i.SP -= 2;
	i.PC = i.I;
	i.incrPC = false;
}

//Ccondition addr
#define C(COND) void C##COND(I8080& i){\
	if(i.COND()){\
		CALL(i);\
	}\
	else {\
		i.PC += 3;\
	}\
	i.incrPC = false;\
}

C(_NZ) C(_Z) C(_NC) C(_C) C(_PO) C(_PE) C(_P) C(_M)

//RET
void RET(I8080& i) {
	i.PCL = i.memory[i.SP];
	i.PCH = i.memory[i.SP + 1];
	i.SP += 2;

	i.incrPC = false;
}

//Rcondition
#define R(COND) void R##COND(I8080& i){\
	if(i.COND()){\
		RET(i);\
	}\
	else {\
		i.PC += 1;\
	}\
	i.incrPC = false;\
}

R(_NZ) R(_Z) R(_NC) R(_C) R(_PO) R(_PE) R(_P) R(_M)

//RST n
#define RST(NNN) void RST_##NNN(I8080& i){\
	i.PC++;\
	i.memory[i.SP - 1] = i.PCH;\
	i.memory[i.SP - 2] = i.PCL;\
	i.SP -= 2;\
	i.PC = 8 * NNN;\
	i.incrPC = false;\
}

RST(0) RST(1) RST(2) RST(3) RST(4) RST(5) RST(6) RST(7)

//PCHL
void PCHL(I8080& i) {
	i.PCH = i.H;
	i.PCL = i.L;
	i.incrPC = false;
}

#endif // !BRANCH_H

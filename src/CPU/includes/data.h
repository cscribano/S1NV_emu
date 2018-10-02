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

#ifndef DATA_H
#define DATA_H

#include "cpu.h"
#include<utility>

//MOV r1,r2
#define MOV(REG1,REG2) void MOV_##REG1##REG2(I8080& i){\
	i.REG1 = i.REG2;\
}

MOV(A, A) MOV(A, B) MOV(A, C) MOV(A, D) MOV(A, E) MOV(A, H) MOV(A, L)
MOV(B, A) MOV(B, B) MOV(B, C) MOV(B, D) MOV(B, E) MOV(B, H) MOV(B, L)
MOV(C, A) MOV(C, B) MOV(C, C) MOV(C, D) MOV(C, E) MOV(C, H) MOV(C, L)
MOV(D, A) MOV(D, B) MOV(D, C) MOV(D, D) MOV(D, E) MOV(D, H) MOV(D, L)
MOV(E, A) MOV(E, B) MOV(E, C) MOV(E, D) MOV(E, E) MOV(E, H) MOV(E, L)
MOV(H, A) MOV(H, B) MOV(H, C) MOV(H, D) MOV(H, E) MOV(H, H) MOV(H, L)
MOV(L, A) MOV(L, B) MOV(L, C) MOV(L, D) MOV(L, E) MOV(L, H) MOV(L, L)

//MOV r,M
#define MOV_RM(REG) void MOV_##REG##M(I8080& i){\
	i.REG = i.memory[i.HL];\
}

//MOV M,r
MOV_RM(A) MOV_RM(B) MOV_RM(C) MOV_RM(D) MOV_RM(E) MOV_RM(H) MOV_RM(L)

#define MOV_MR(REG) void MOV_M##REG(I8080& i){\
	i.memory[i.HL] = i.REG;\
}

MOV_MR(A) MOV_MR(B) MOV_MR(C) MOV_MR(D) MOV_MR(E) MOV_MR(H) MOV_MR(L)

//MVI r, data
#define MVI_R_D(REG) void MVI_##REG##D8(I8080& i){\
	i.REG = i.I2;\
}

MVI_R_D(A) MVI_R_D(B) MVI_R_D(C) MVI_R_D(D) MVI_R_D(E) MVI_R_D(H) MVI_R_D(L)

//MVI M, data (0x36)
void MVI_M_D8(I8080& i) {
	i.memory[i.HL] = i.I2;
}

//LXI rp, d16 RP = I ?
#define LXI(RH, RL) void LXI_##RH##D16(I8080& i){\
	i.RH = i.I3;\
	i.RL = i.I2;\
}

LXI(B,C) LXI(D,E) LXI(H,L) LXI(S,P)

//LDA addr
void LDA(I8080& i) {
	i.A = i.memory[i.I];
}

//STA addr
void STA(I8080& i) {
	i.memory[i.I] = i.A;
}

//LHLD addr
void LHLD(I8080& i) {
	i.L = i.memory[i.I];
	i.H = i.memory[i.I + 1];
}

//SHLD addr
void SHLD(I8080& i) {
	i.memory[i.I] = i.L;
	i.memory[i.I + 1] = i.H;
}

//LDAX rp
#define LDAX(RP) void LDAX_##RP(I8080& i){\
	i.A = i.memory[i.RP];\
}

LDAX(BC) LDAX(DE)

//STAX rp
#define STAX(RP) void STAX_##RP(I8080& i){\
	i.memory[i.RP] = i.A;\
}

STAX(BC) STAX(DE)

//XCHG
void XCHG(I8080& i) {
	std::swap(i.H, i.D);
	std::swap(i.L, i.E);
}

#endif // !DATA_H

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

#ifndef LOGICAL_H
#define LOGICAL_H

#include"cpu.h"
//ANA r
#define ANA(REG) void ANA_##REG(I8080& i){\
	i.A &= i.REG;\
	i.SetFlags_NC(i.A);\
	i.CY_ = 0;\
}

ANA(A) ANA(B) ANA(C) ANA(D) ANA(E) ANA(H) ANA(L)

//ANA M
void ANA_M(I8080& i) {
	i.A &= i.memory[i.HL];
	i.SetFlags_NC(i.A);
	i.CY_ = 0;
}

//ANI data
void ANI(I8080& i) {
	i.A &= i.I2;
	i.SetFlags_NC(i.A);
	i.CY_ = 0;
	i.AC_ = 0;
}

//XRA r
#define XRA(REG) void XRA_##REG(I8080& i){\
	i.A ^= i.REG;\
	i.SetFlags_NC(i.A);\
	i.CY_ = 0;\
	i.AC_ = 0;\
}

XRA(A) XRA(B) XRA(C) XRA(D) XRA(E) XRA(H) XRA(L)

//XRA M
void XRA_M(I8080& i) {
	i.A ^= i.memory[i.HL]; 
	i.SetFlags_NC(i.A); 
	i.CY_ = 0; 
	i.AC_ = 0; 
}

//XRI data
void XRI(I8080& i) {
	i.A ^= i.I2;
	i.SetFlags_NC(i.A);
	i.CY_ = 0;
	i.AC_ = 0;
}

//ORA r
#define ORA(REG) void ORA_##REG(I8080& i){\
	i.A |= i.REG;\
	i.SetFlags_NC(i.A);\
	i.CY_ = 0;\
	i.AC_ = 0;\
}

ORA(A) ORA(B) ORA(C) ORA(D) ORA(E) ORA(H) ORA(L)

//ORA M
void ORA_M(I8080& i) {
	i.A |= i.memory[i.HL];
	i.SetFlags_NC(i.A);
	i.CY_ = 0;
	i.AC_ = 0;
}

//ORI data
void ORI(I8080& i) {
	i.A |= i.I2;
	i.SetFlags_NC(i.A);
	i.CY_ = 0;
	i.AC_ = 0;
}

//CMP r
#define CMP(REG) void CMP_##REG(I8080& i){\
	i.SetFlags_NC(i.A - i.REG);\
	i.Z_ = (i.A == i.REG);\
	i.CY_ = (i.A < i.REG);\
}
CMP(A) CMP(B) CMP(C) CMP(D) CMP(E) CMP(H) CMP(L)

//CMP M
void CMP_M(I8080& i) {
	i.SetFlags_NC(i.A - i.memory[i.HL]); 
	i.Z_ = (i.A == i.memory[i.HL]);
	i.CY_ = (i.A < i.memory[i.HL]);
}

//CPI data
void CPI(I8080& i) {
	i.SetFlags_NC(i.A - i.I2);
	i.Z_ = (i.A == i.I2);
	i.CY_ = (i.A < i.I2);
}

//RLC
void RLC(I8080& i) {
	uint16_t r = i.A << 1;
	i.CY_ = (r >> 8) & 1;
	r |= i.CY_;
	i.A = r & 0xFF;
}

//RRC
void RRC(I8080& i) {
	i.CY_ = i.A & 1;
	uint16_t r = i.A >> 1;
	r |= (i.CY_<<7);
	i.A = r & 0xFF;
}

//RAL
void RAL(I8080& i) {
	uint8_t t = (i.A >> 7) & 1;
	i.A = (i.A << 1) | i.CY_;
	i.CY_ = t;
}

//RAR
void RAR(I8080& i) {
	uint8_t t = i.A & 1;
	i.A = (i.A >> 1) | (i.CY_ << 7);
	i.CY_ = t;
}

//CMA
void CMA(I8080& i) {
	i.A = ~(i.A);
}

//CMC
void CMC(I8080& i) {
	i.CY_ = (~i.CY_)&1;
}

//STC
void STC(I8080& i) {
	i.CY_ = 1;
}
#endif // !LOGICAL_H

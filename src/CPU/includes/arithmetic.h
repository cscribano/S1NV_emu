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

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "cpu.h"

//ADD r
#define ADD(REG) void ADD_##REG(I8080& i){\
	uint16_t r = i.REG + i.A;\
	i.SetFlags(r, i.REG);\
	i.A = r & 0xFF; \
}

ADD(A) ADD(B) ADD(C) ADD(D) ADD(E) ADD(H) ADD(L)

//ADD M
void ADD_M (I8080& i) {
	uint16_t r = i.A + i.memory[i.HL];
	i.SetFlags(r, i.memory[i.HL]);
	i.A = r & 0xFF;
}

//ADI data
void ADI(I8080& i) {
	uint16_t r = i.A + i.I2;
	i.SetFlags(r, i.I2);
	i.A = r & 0xFF;
}

//ADC r (???)
#define ADC(REG) void ADC_##REG(I8080& i){\
	uint16_t r = i.A + (i.REG + i.CY_);\
	i.SetFlags(r,(i.REG + i.CY_)); \
	i.A = r&0xFF;\
}

ADC(A) ADC(B) ADC(C) ADC(D) ADC(E) ADC(H) ADC(L)

//ADC M (???)
void ADC_M(I8080 & i) {
	uint16_t r = i.A + i.memory[i.HL] + i.CY_;
	i.SetFlags(r, i.memory[i.HL] + i.CY_);
	i.A = r & 0xFF;
}

//ACI data
void ACI(I8080& i) {
	uint16_t r = i.A + i.I2 + i.CY_;
	i.SetFlags(r, i.I2 + i.CY_);
	i.A = r & 0xFF;
}

//SUB r
#define SUB(REG) void SUB_##REG(I8080& i){\
	uint16_t r = i.A - i.REG;\
	i.SetFlags(r, -i.REG);\
	i.A = r&0xFF;\
}

SUB(A) SUB(B) SUB(C) SUB(D) SUB(E) SUB(H) SUB(L)

//SUB M
void SUB_M(I8080& i) {
	uint16_t r = i.A - i.memory[i.HL];
	i.SetFlags(r, -i.memory[i.HL]);
	i.A = r & 0xFF;
}

//SUI data
void SUI(I8080& i) {
	uint16_t r = i.A - i.I2;
	i.SetFlags(r, -i.I2);
	i.A = r & 0xFF;
}

//SBB r
#define SBB(REG) void SBB_##REG(I8080& i){\
	uint16_t r = i.A - (i.REG + i.CY_);\
	i.SetFlags(r, -(i.REG + i.CY_));\
	i.A = r & 0xFF;\
}

SBB(A) SBB(B) SBB(C) SBB(D) SBB(E) SBB(H) SBB(L)

//SBB M
void SBB_M(I8080& i) {
	uint16_t r = i.A - (i.memory[i.HL] + i.CY_);
	i.SetFlags(r, -(i.memory[i.HL] + i.CY_));
	i.A = r & 0xFF;
}

//SBI data
void SBI(I8080& i) {
	uint16_t r = i.A - i.I2 - i.CY_;
	i.SetFlags(r, -(i.I2 - i.CY_));
	i.A = r & 0xFF;
}

//<<<--------- AC problem
//INR r
#define INR(REG) void INR_##REG(I8080& i){\
	uint16_t r = i.REG + 1;\
	i.SetFlags_NC(r);\
	i.REG = r&0xFF;\
	i.AC_ = (((i.REG & 0xF + 1)) > 0xF);\
}

INR(A) INR(B) INR(C) INR(D) INR(E) INR(H) INR(L)

//INR M
void INR_M(I8080& i) {
	uint16_t r = i.memory[i.HL] + 1;
	i.AC_ = (((i.memory[i.HL] & 0xF + 1)) > 0xF);
	i.SetFlags_NC(r);
	i.memory[i.HL] = r & 0xFF;
}

//DCR r
#define DC(REG) void DCR_##REG(I8080& i){\
	uint16_t r = i.REG - 1;\
	i.REG = r & 0xFF;\
	i.SetFlags_NC(r);\
}

DC(A) DC(B) DC(C) DC(D) DC(E) DC(H) DC(L)

//DCR M
void DCR_M(I8080& i) {
	uint16_t r = i.memory[i.HL] - 1;
	i.memory[i.HL] = r & 0xFF;
	i.SetFlags_NC(r);
}

//INX rp ??
#define INX(RP) void INX_##RP(I8080& i){\
	i.RP += 1;\
}

INX(BC) INX(DE) INX(HL) INX(SP)

//DCX rp ??
#define DCX(RP) void DCX_##RP(I8080& i){\
	i.RP -= 1;\
}

DCX(BC) DCX(DE) DCX(HL) DCX(SP)

//DAD rp ??
#define DAD(RP) void DAD_##RP(I8080& i){\
	uint32_t r = i.HL + i.RP;\
	i.CY_ = ((r>>16)>0);\
	i.HL = r&0xFFFF;\
}

DAD(BC) DAD(DE) DAD(HL) DAD(SP)

//DAA (to be further tested)
void DAA(I8080& i) {
	uint8_t sum = 0;
	uint8_t c = i.CY_;

	if (i.AC_ || (i.A & 0x0F)>9) {
		sum += 0x06;
	}
	if (i.CY_ || (i.A >> 4) > 9 || ((i.A >> 4) >= 9 && (i.A & 0xF0) > 9)) {
		sum += 0x60;
		c = 1;
	}
	uint16_t t = i.A + sum;
	i.SetFlags_NC(t);
	i.A = t & 0xFF;
	i.CY_ = c;
}

#endif // !ARITHMETIC_H

/*	uint16_t ta = i.A;

	if ((ta & 0xF) > 9 || i.AC_) {
		ta += 6;
		if (((ta >> 4) > 9) || i.CY_){
			ta += 0x60;
		}
	}
	if (ta != i.A) {
		i.A = ta & 0xFF;
		i.SetFlags(ta, ta - i.A);
	}*/

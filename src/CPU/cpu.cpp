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
#define _CRT_SECURE_NO_WARNINGS

#include "includes/cpu.h"
#include "includes/table.h"
#include "invaders_e.h"
#include "invaders_f.h"
#include "invaders_g.h"
#include "invaders_h.h"

#include <fstream>
#include<cstdarg>
#include<cstdio>
#include<iomanip>
#include<cstring>

using namespace std;

bool parity(uint8_t b){
	uint8_t n = 8;
	uint8_t p = 0;
	while (n-- > 0) {
		p += ((b >> n) & 1);
	}
	return ((p % 2) == 0);
}

I8080::I8080(size_t memsize, uint16_t startpoint){
	this->memsize = memsize;
	memory = new uint8_t[memsize];
	PC = startpoint;
}

int I8080::LoadRom(const char * fileName, size_t offset){

	size_t i = 0;
	ifstream rom(fileName, ios::binary);
	if (!rom)
		return i;

	while (true) {
		if ((offset + i) >= memsize)
			break;

		auto a = rom.get();
		if (a == EOF)
			break;
		memory[offset + i] = a;
		++i;
	}
	return i;
}

int I8080::LoadRomHeader() { //h-g-f-e
	memcpy(memory, invaders_h, 2048);
	memcpy(memory + 2048, invaders_g, 2048);
	memcpy(memory + 4096, invaders_f, 2048);
	memcpy(memory + 6144, invaders_e, 2048);
	return 2048 * 4;
}

uint8_t I8080::EmulateCycle(){
	
	uint8_t opcode;

	if (!ISR) {
		opcode = memory[PC];
	}
	else {
		PC--;
		IEnabled = false;
		opcode = ISR;
		ISR = 0;
	}

	char dbg_str[50];
	incrPC = true;
	
	switch (instructions[opcode].nOperands) {
	case 2:
		I2 = memory[PC + 1];
		if (dbg)
			std::sprintf(dbg_str, instructions[opcode].disassembly, I2);
		break;
	case 3:
		I = memory[PC + 1] | (memory[PC + 2] << 8);
		//if (dbg)
			//std::sprintf(dbg_str, instructions[opcode].disassembly, I);
		break;
	default:
		//if (dbg)
			//std::sprintf(dbg_str, instructions[opcode].disassembly);
		break;
	}

	if (dbg)
		std::cout << std::setbase(16)<<std::setw(4)<<std::setfill('0')<<PC<<" - ";

	if (instructions[opcode].instr != NULL) {
		instructions[opcode].instr(*this);
	}
	else {
		if (dbg)
			std::cout << "[UNIMPLEMENTED]";
	}

	if (dbg)
		std::cout << dbg_str << "\n";

	//Interrupts enabled following the execution of the next instruction wrt IE call
	if (_IE && (PC != _PC_IET)) {
		_IE = false;
		IEnabled = true;
	}

	if(incrPC)
		PC += instructions[opcode].nOperands;

	return 	instructions[opcode].states;

}

void I8080::SetFlags(uint16_t result, uint8_t o){
	Z_ = ((result & 0xFF) == 0);
	S_ = (result >> 7)&1;
	P_ = parity(result & 0xFF);
	CY_ = ((result >> 8) > 0);
	AC_ = (((A & 0xf) + (o & 0xf) & 0x10) == 0x10);
}

void I8080::SetFlags_NC(uint16_t result) {
	Z_ = ((result & 0xFF) == 0);
	S_ = (result >> 7) & 1;
	P_ = parity(result & 0xFF);
}

 void I8080::Interrupt(uint8_t ISR){
	if (IEnabled == true) {
		if (dbg)
			std::cout << "[I] - " << std::setbase(16) << +ISR<<"\n";
		this->ISR = ISR;
	}
}

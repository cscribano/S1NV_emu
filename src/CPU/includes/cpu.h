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

#ifndef  CPU_H
#define CPU_H

#include<iostream>
#include<vector>
#include<unordered_map>

typedef uint8_t(*i_callback)();
typedef uint8_t(*o_callback)(uint8_t arg);

bool parity(uint8_t b);

template<typename ... Flags>
uint8_t PSW(Flags ... args) {
	uint8_t ret = 0;
	std::vector<int> argsVector{ args... };
	size_t n = 0;

	for (auto& x : argsVector) {
		ret |= x << n;
		++n;
	}
	return ret;
}

class I8080{
private:
	size_t memsize;
	uint16_t _PC_IET; //PC at IE call issue time
	bool _IE = false; //request for enable Interrupts

public:
	uint8_t *memory;
	
	bool IEnabled = false; //are interrupts enabled?
	uint8_t ISR = 0;

	bool dbg = false;
	bool incrPC;

	//instructions
	union {
		struct {
			uint8_t I2; //instr byte 2 (lsb)
			uint8_t I3; //instr byte 3
		};
		uint16_t I; //I3-I2
	};

	//resgisters
	union {
		struct {
			uint8_t C; //lsb 
			uint8_t B; //msb
		};
		uint16_t BC; //msb-lsb
	};

	union {
		struct {
			uint8_t E;
			uint8_t D;
		};
		uint16_t DE;
	};

	union {
		struct {
			uint8_t L;
			uint8_t H;
		};
		uint16_t HL;
	};

	union {
		struct {
			uint8_t Z;
			uint8_t W;
		};
		uint16_t WZ;
		};


	//stack pointer
	union {
		struct {
			uint8_t P;//l
			uint8_t S;//m
			};
		uint16_t SP;
	};

	//programm counter
	union {
		struct {
			uint8_t PCL;
			uint8_t PCH;
		};
		uint16_t PC;
	};

	//ALU
	uint8_t A;

	struct {
		uint8_t Z_, CY_, S_, P_, AC_;
	};

	//END ALU

	I8080(size_t memsize = 0x10000, uint16_t startpoint = 0);
	~I8080() { delete[] memory; }

	int LoadRom(const char* fileName, size_t offset = 0x00);
	uint8_t EmulateCycle();

	void EnableInterrput() { _PC_IET = PC, _IE = true; }
	void Interrupt(uint8_t ISR);

	void SetFlags(uint16_t result, uint8_t op);
	void SetFlags_NC(uint16_t result);

	//conditions
	bool _NZ() { return !Z_; }
	bool _Z() { return Z_; }
	bool _NC() { return !CY_; }
	bool _C() { return CY_; }
	bool _PO() { return !P_; }
	bool _PE() {return P_; }
	bool _P() { return !S_; }
	bool _M() { return S_; }
};

#endif // ! CPU_H

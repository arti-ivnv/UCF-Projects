// CDA 3103C, Fall 2019
// MySPIM Project

// Stephen Speer
// Artem Ivanov
// Kyle Villarante

#include "spimcore.h"

void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{
	// ALU performs logical operations on the two parameters A and B
	// the ALU control dictates the operation to be performed

	// Add
	if (ALUControl == 0b00)
	{
		*ALUresult = A + B;
	}
	// Subtract
	else if (ALUControl == 0b001)
	{
		*ALUresult = A - B;
	}
	// Set less than (signed)
	else if (ALUControl == 0b010)
	{
		if ((signed) A < (signed) B)
		{
			*ALUresult = 1;
		}
		else
		{
			*ALUresult = 0;
		}
	}
	// set less than (unsigned)
	else if (ALUControl == 0b011)
	{
		if (A < B)
		{
			*ALUresult = 1;
		}
		else
		{
			*ALUresult = 0;
		}
	}
	// AND
	else if (ALUControl == 0b100)
	{
		*ALUresult = A & B;
	}
	// OR
	else if (ALUControl == 0b101)
	{
		*ALUresult = A | B;
	}
	else if (ALUControl == 0b110)
	{
		*ALUresult = B << 16;
	}
	// NOT
	else if (ALUControl == 0b111)
	{
		*ALUresult = ~A;
	}

	// The ALU keeps track if the result of the operation is zero.
	// This is useful for instructions that use comparison, such as beq
	if (*ALUresult == 0)
	{
		*Zero = 1;
	}
	else
	{
		*Zero = 0;
	}
}

int instruction_fetch(unsigned PC, unsigned *Mem, unsigned *instruction)
{
	// Checks if PC is a multiple of 4.
	if ((PC % 4) != 0)
	{
		// Halt
		return 1;
	}

	// Checks if our PC is in a range of 64 kB.
	if (PC <= 0xFFFF && PC >=0x0000)
	{
		*instruction = Mem[(PC >> 2)];
		return 0;
	}
	else
	{
		return 1;
	}
}

void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// Instruction partition translates the instruction code
	// into variables for R, I, and J type instructions
	// by bitmasking the bits the represent each field in the instruction

	// op: 		31 - 26
	*op = (instruction & 0b11111100000000000000000000000000) >> 26;

	// rs:		25 - 21
	*r1 = (instruction & 0b00000011111000000000000000000000) >> 21;

	// rt:		20 - 16
	*r2 = (instruction & 0b00000000000111110000000000000000) >> 16;

	// rd:		15 - 11
	*r3 = (instruction & 0b00000000000000001111100000000000) >> 11;

	// funct:	5 - 0
	*funct = instruction & 0b00000000000000000000000000111111;

	// shamt:	15 - 0
	*offset = instruction & 0b00000000000000001111111111111111;

	// jsec:	25 - 0
	*jsec = instruction & 0b00000011111111111111111111111111;

}

int instruction_decode(unsigned op, struct_controls *controls)
{
	// This function acts as the control unit in our datapath.
	// Depending on the op code parameter, certain values need to be toggled
	// By selecting these values, we can control the MUXs in our datapath

	// R-type
	if (op == 0)
	{
		controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 7; // ALUOp = 111
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 1;
	}
	// Load word
	else if (op == 35)
	{
		// load word instruction reads from memory and write to a register
		controls->RegDst = 1;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 1;
		controls->MemtoReg = 1;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
	}
	// Store word
	else if (op == 43)
	{
		// copies data from a register to memory
		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 0;
	}
	// beq
	else if (op == 4)
	{

		controls->RegDst = 2;
		controls->Jump = 0;
		controls->Branch = 1;
		controls->MemRead = 0;
		controls->MemtoReg = 2;

		// use subtraction to determine if addresses match
		controls->ALUOp = 1;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
	}
	// addi
	else if (op == 8)
	{
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
	}
	// slti
	else if (op == 10)
	{
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 2;
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
	}
	// sltiu
	else if (op == 11)
	{
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 3;
		controls->MemWrite = 1;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
	}
	// lui
	else if (op == 15)
	{
		controls->RegDst = 0;
		controls->Jump = 0;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 6;
		controls->MemWrite = 0;
		controls->ALUSrc = 1;
		controls->RegWrite = 1;
	}
	// jump
	else if (op == 2)
	{
		controls->RegDst = 2;
		controls->Jump = 1;
		controls->Branch = 0;
		controls->MemRead = 0;
		controls->MemtoReg = 0;
		controls->ALUOp = 0;
		controls->MemWrite = 0;
		controls->ALUSrc = 0;
		controls->RegWrite = 0;
	}
	else
	{
		// Halt. Invalid instructions
		return 1;
	}

	return 0;
}

void read_register(unsigned r1, unsigned r2, unsigned *Reg, unsigned *data1, unsigned *data2)
{
	// load data from registers into our data variables
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}

void sign_extend(unsigned offset, unsigned *extended_value)
{
	// Assign the sign-extended value of offset to extended_value
	// check sign of value, if the 16th bit is 1, then it is negative

	// If the 16th bit on a 16 bit value is 1, then it represents a negative number
	// to keep the sign, pad the leftmost 16 bits in the new 32 bit value with 1
	if (offset >> 15 == 1)
	{
		*extended_value = offset | 0b11111111111111110000000000000000;
	}
	// keep number positive
	else
	{
		*extended_value = offset & 0b00000000000000001111111111111111;
	}
}

int ALU_operations(unsigned data1, unsigned data2, unsigned extended_value, unsigned funct, char ALUOp, char ALUSrc, unsigned *ALUresult, char *Zero)
{
	// ALU operations first determines the type of instruction depending on the ALUSrc paramter
	// If the instruction is R type, we look to the funct code to determine the logical operation in the ALU
	// Variable to store translated ALU operation code
	unsigned ALUCode;

	if(ALUSrc == 1)
	{
		// I type instructions
		// pass the extended value as the second data parameter to be used for addressing
		ALU(data1, extended_value, ALUOp, ALUresult, Zero);
	}
	else if (ALUSrc == 0)
	{
		// Case for beq
		// ALU operation is 1 for subtraction operation, which is used to compare
		if (ALUOp == 1)
		{
			ALU(data1, data2, 1, ALUresult, Zero);
		}

		if (ALUOp == 7)
		{
			if (funct == 32)
			{
				// add
				ALUCode = 0;
			}
			else if (funct == 34)
			{
				// subtract
				ALUCode = 1;
			}
			else if (funct == 42)
			{
				// set less than signed
				ALUCode = 2;
			}
			else if (funct == 43)
			{
				// set less than unsigned
				ALUCode = 3;
			}
			else if (funct == 36)
			{
				// AND
				ALUCode = 4;
			}
			else if (funct == 37)
			{
				// OR
				ALUCode = 5;
			}
			else if (funct == 39)
			{
				// shift left by 16 bits
				ALUCode = 6;
			}
			else
			{
				// Halt. Invalid instruction
				return 1;
			}
		}

		// call the ALU function with the translated ALUCode
		ALU(data1, data2, ALUCode, ALUresult, Zero);
	}
	else
	{
		// Halt. Invalid instruction
		return 1;
	}

	return 0;
}

int rw_memory(unsigned ALUresult, unsigned data2, char MemWrite, char MemRead, unsigned *memdata, unsigned *Mem)
{

	if (MemWrite == 1 || MemRead == 1)
	{
		// check for word alignment
		if ( (ALUresult % 4) != 0)
		{
			// printf("Error in rw memory. Word not aligned\n");
			return 1;
		}
		// check that the address is within 64kb
		else if (ALUresult > 65536)
		{
			// printf( "Error in rw memory. Address out of bounds\n");
			return 1;
		}
	}

	ALUresult = ALUresult >> 2;

	if (MemRead == 1)
	{
		// Get value from memory and store in memdate
		*memdata = Mem[ALUresult];
	}

	if (MemWrite == 1)
	{
		// Copy value from register into memory
		Mem[ALUresult] = data2;
	}

	return 0;
}

void write_register(unsigned r2, unsigned r3, unsigned memdata, unsigned ALUresult, char RegWrite, char RegDst, char MemtoReg, unsigned *Reg)
{
	// To write anything to a register we need to determine first if we are allowed
	// to do so. (Depending on our RegWrite control signal) Then we are checking if
	// we are writing from from memory or ALU result. (Depending on our MemtoReg control signal)
	// Finaly, we need to need to determine wich register we are writing to. r2 or r3
	// (Depending on our RegDst)

	// Checks if we are allowed to write to a register.
	if(RegWrite == 1)
	{
		// For lw instruction
		if (MemtoReg == 1)
		{
			// for load word instruction, put the value of memory into the specified register
			Reg[r2] = memdata;
		}
		else if (MemtoReg == 0)
		{
			// If RegDst is 0 => we are writing to r2 else to r3.
			if (RegDst == 1)
			{
				Reg[r3] = ALUresult;
			}
			else if (RegDst == 0)
			{
				Reg[r2] = ALUresult;
			}
		}
	}
}

void PC_update(unsigned jsec, unsigned extended_value, char Branch, char Jump, char Zero, unsigned *PC)
{
	// PC update function helps us to increment our program function, jump, and branc

	// If Jump is true, use a mask to change the upper 4 bits, then add the jsec value shifted by 2;
	if (Jump == 1)
	{
		*PC = (*PC & 0b11110000000000000000000000000000) + (jsec << 2);
	}
	// Represents the beq condition
	// add the extended value of the address to the PC to get next instruction
	else if (Zero == 1 && Branch == 1)
	{
		*PC = *PC + (extended_value << 2) + 4;
	}
	else
	{
		// if not a branch or jump, increment the PC by 4 to the next instruction
		*PC += 4;
	}
}

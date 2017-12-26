#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <stack>
#include <string>
#include <memory>
#include <fstream>

class C_Chip8
{
public:
	C_Chip8(std::string file_name);
	void assemble();
	void initialize();
	void interpret();

private:
	std::size_t length;
	std::ifstream file;
	std::unique_ptr<std::uint8_t[]> buffer;
	std::uint16_t* cur_instrs;
	std::vector<std::uint8_t> registers;
	std::uint16_t ir; /* index register */
	std::uint16_t pc; /* program counter */
	std::stack<std::uint16_t> stack;
	std::unique_ptr<std::uint8_t[]> memory;
};
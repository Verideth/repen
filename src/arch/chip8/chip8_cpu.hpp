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
	std::vector<std::uint8_t> registers;
	std::unique_ptr<std::uint8_t[]> memory;
};

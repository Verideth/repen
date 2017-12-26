#include "arch/arch.hpp"
#include <iostream>
#include <cstdint>
#include <string>

std::int32_t main(std::int32_t argc, char* argv[])
{
	std::printf("Enter what architecture you'd like to disassemble\n CHIP-8 (90% complete)\n Z80 (not implemented)\n i8086 (not implemented)\n");

	std::string input_arch;
	std::cin >> input_arch;
	std::printf("Now please enter the file name: ");
	std::string input_file;
	std::cin >> input_file;
	std::printf("\n\n\n");

	if (input_arch == "CHIP-8")
	{
		C_Chip8 chip(input_file);

		std::printf("Binary being disassembled......\n\n\n");
		
		chip.initialize();

		chip.assemble();
	}

	while (true)
	{
		std::string exit_input;
		std::cin >> exit_input;
	}

	return 1;
}
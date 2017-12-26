#include "chip8_cpu.hpp"

C_Chip8::C_Chip8(std::string file_name)
{
	this->file.open(file_name, std::ios::in | std::ios::binary);
}

void C_Chip8::initialize()
{
	this->file.seekg(0, this->file.end);
	this->length = this->file.tellg();
	this->file.seekg(0, this->file.beg);

	this->buffer = std::make_unique<std::uint8_t[]>(this->length);

	this->file.read(reinterpret_cast<char*>(this->buffer.get()), this->length);
}

void C_Chip8::assemble()
{
	for (std::size_t i = 0; i < this->length; i++)
	{
		std::uint16_t opcode = (this->buffer[i] << 8) | this->buffer[i + 1];
		std::uint16_t op_lower_bit = (opcode & 0x000F);

		switch ((opcode & 0xF000) >> 12)
		{
		case 0x0:
		{
			if ((opcode & 0x0FFF) == 0xE0)
			{
				std::printf("CLS		; clear display");
				std::printf("\n");
			}
			else if ((opcode & 0x0FFF) == 0xEE)
			{
				std::printf("RETURN				; return from subroutined");
				std::printf("\n");
			}
			else
			{

			}

			break;
		}

		case 0x1:
		{
			std::printf("JMP 0x%02X			; 'jump' to address (go to)", ((opcode & 0x0FFF)));
			std::printf("\n");

			break;
		}

		case 0x2:
		{
			std::printf("CALL sub_0x%02X			; call address", (opcode & 0x0FFF));
			std::printf("\n");

			break;
		}

		case 0x3:
		{
			std::printf("SE BYTE V%i, %i			; skip if right is equal to left", ((opcode & 0x0F00) >> 8), (opcode & 0x00FF));
			std::printf("\n");

			break;
		}

		case 0x4:
		{
			std::printf("SNE BYTE V%i, %i			; skip if right is NOT equal to left", ((opcode & 0x0F00) >> 8), ((opcode & 0x00FF)));
			std::printf("\n");

			break;
		}

		case 0x5:
		{
			std::printf("SE V%i, V%i			; skip if right register is equal to left register", ((opcode & 0x0F00 >> 8)), ((opcode & 0x00F0) >> 4));
			std::printf("\n");


			break;
		}

		case 0x6:
		{
			std::printf("LD V%i, 0x%02X			; put right value into Vx", ((opcode & 0x0F00) >> 8), ((opcode & 0x0F00)));
			std::printf("\n");

			break;
		}

		case 0x7:
		{
			std::printf("ADD V%i, %i			; add register to number", ((opcode & 0x0F00) >> 8), ((opcode & 0x0F00)));
			std::printf("\n");

			break;
		}

		case 0x8:
		{
			switch (op_lower_bit)
			{
				case 0x0:
				{
					std::printf("LD V%i, V%i			; store right register into left register", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}
				case 0x1:
				{
					std::printf("OR V%i, V%i			; OR operation, right register is or'd against left register", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;

				}

				case 0x2:
				{
					std::printf("AND V%i, V%i			; ands right register against left", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}

				case 0x3:
				{
					std::printf("XOR V%i, V%i		; xors right register against left", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}

				case 0x4:
				{
					std::printf("ADD V%i, V%i		; adds the right register against left", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}

				case 0x5:
				{
					std::printf("SUB V%i, V%i		; subtracts right register against left", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}

				case 0x6:
				{
					std::printf("SHR V%i			; if the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.", ((opcode & 0x0F00) >> 8));
					std::printf("\n");

					break;
				}

				case 0x7:
				{
					std::printf("SUBN V%i, V%i		; If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
					std::printf("\n");

					break;
				}

				case 0xE:
				{
					std::printf("SHL V%i		; if the most - significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.", ((opcode & 0x0F00) >> 8));
					std::printf("\n");

					break;
				}
				}

				break;
			}

			case 0x9:
			{
				std::printf("SNE V%i, V%i			; skip next instruction if Vx != Vy", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
				std::printf("\n");

				break;
			}

			case 0xA:
			{
				std::printf("LD I, 0x%02X			; value of register I is set to right.", ((opcode & 0x0F00) >> 8), (opcode & 0x0F00));
				std::printf("\n");

				break;
			}

			case 0xB:
			{
				std::printf("JMP V%i, 0x%02X		; jump to right side + left side", ((opcode & 0x0F00) >> 8), (opcode & 0x0F00));
				std::printf("\n");
			
				break;
			}

			case 0xC:
			{
				std::printf("RND V%i, %i			; set left side to a random byte AND right side (random ranges from 0 - 255)", ((opcode & 0x0F00) >> 8), (opcode & 0x0F00));
				std::printf("\n");

				break;
			}

			case 0xD:
			{
				std::printf("DRAW V%i, V%i			; draws the registers to screen", ((opcode & 0x0F00) >> 8), ((opcode & 0x00F0) >> 4));
				std::printf("\n");

				break;
			}

			case 0xE:
			{
				switch (opcode & 0x00FF)
				{
					case 0x9E:
					{
						std::printf("SKP V%i			; skip next instruction if key with the value Vx is pressed", ((opcode & 0x0F00) >> 8));
						std::printf("\n");

						break;
					}

					case 0xA1:
					{
						std::printf("SKNP V%i			; skip next instruction if key with the value Vx is NOT pressed", ((opcode & 0x0F00) >> 8));
						std::printf("\n");

						break;
					}
				}

				break;
			}

			case 0xF:
			{
				switch (opcode & 0x00FF)
				{
					case 0xA1:
					{

					}
				}
			}

			default:
			{
				std::printf("UNK");
				std::printf("\n");

				break;
			}
		}
	}
}

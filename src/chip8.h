#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <chrono>
#include <random>

class Chip8
{
    Chip8()
        : randGen(std::chrono::system_clock::now().time_since_epoch().count()) 
    {
        
        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

    }
    public:
      uint8_t keys[16]{};
      uint32_t screen[64 * 32]{};
    private: 
      uint8_t registers[16]{};
      uint8_t memory[4096]{};
      uint16_t index{};
      uint16_t pc{};
      uint16_t stack[16]{};
      uint8_t sp{};
      uint8_t delay_timer{};
      uint8_t sound_timer{};
      uint16_t opcode;

      std::default_random_engine randGen;
      std::uniform_int_distribution<uint8_t> randByte;

};

#endif

#ifndef CHIP8_H
#define CHIP8_H

#include <SDL.h>
#include <cstdint>
#include <chrono>
#include <random>


constexpr unsigned int VIDEO_WIDTH = 64;
constexpr unsigned int VIDEO_HEIGHT = 32;


class Chip8
{
    void Table0()
	{
		((*this).*(table0[opcode & 0x000Fu]))();
	}

	void Table8()
	{
		((*this).*(table8[opcode & 0x000Fu]))();
	}

	void TableE()
	{
		((*this).*(tableE[opcode & 0x000Fu]))();
	}

	void TableF()
	{
		((*this).*(tableF[opcode & 0x00FFu]))();
	}

	void OP_NULL()
	{}


	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1];
	Chip8Func table0[0xE + 1];
	Chip8Func table8[0xE + 1];
	Chip8Func tableE[0xE + 1];
	Chip8Func tableF[0x65 + 1];

        

    public:
      Chip8();
      void LoadROM(char const* filename);
      void Cycle();
      uint8_t keypad[16]{};
      uint32_t video[64 * 32]{};
    private: 
      uint8_t registers[16]{};
      uint8_t memory[4096]{};
      uint16_t index{};
      uint16_t pc{};
      uint16_t stack[16]{};
      uint8_t sp{};
      uint8_t delayTimer{};
      uint8_t soundTimer{};
      uint16_t opcode;

      void OP_00E0();
      void OP_00EE();
      void OP_1nnn();
      void OP_2nnn();
      void OP_3xkk();
      void OP_4xkk();
      void OP_5xy0();
      void OP_6xkk();
      void OP_7xkk();
      void OP_8xy0();
      void OP_8xy1();
      void OP_8xy2();
      void OP_8xy3();
      void OP_8xy4();
      void OP_8xy5();
      void OP_8xy6();
      void OP_8xy7();
      void OP_8xyE();
      void OP_9xy0();
      void OP_Annn();
      void OP_Bnnn();
      void OP_Cxkk();
      void OP_Dxyn();
      void OP_Ex9E();
      void OP_ExA1();
      void OP_Fx07();
      void OP_Fx0A();
      void OP_Fx15();
      void OP_Fx18();
      void OP_Fx1E();
      void OP_Fx29();
      void OP_Fx33();
      void OP_Fx55();
      void OP_Fx65();

      std::default_random_engine randGen;
      std::uniform_int_distribution<uint16_t> randByte;

};


class Platform {
    public: 
        Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
            SDL_Init(SDL_INIT_VIDEO);
            window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
        }
        ~Platform() {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        void Update(void const* buffer, int pitch) {
            SDL_UpdateTexture(texture, nullptr, buffer, pitch);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, nullptr, nullptr);
            SDL_RenderPresent(renderer);
        }
        bool ProcessInput(uint8_t* keys) {
            bool quit = false;

            SDL_Event event;

            while(SDL_PollEvent(&event)){
                switch (event.type) {
                    case SDL_QUIT:
                        {
                            quit = true;
                        } break;

                    case SDL_KEYDOWN:
                        {
                            switch (event.key.keysym.sym) {
                                case SDLK_ESCAPE:
                                    {
                                        quit = true;
                                    } break;
                                case SDLK_x:
                                    {
                                        keys[0] = 1;
                                    } break;
                                case SDLK_1:
                                {
                                    keys[1] = 1;
                                } break;
                                case SDLK_2:
                                {
                                    keys[2] = 1;
                                } break;
                                case SDLK_3:
                                {
                                    keys[3] = 1;
                                } break;
                                case SDLK_q:
                                {
                                    keys[4] = 1;
                                } break;
                                case SDLK_w:
                                {
                                    keys[5] = 1;
                                } break;
                                case SDLK_e:
                                {
                                    keys[6] = 1;
                                } break;
                                case SDLK_a:
                                {
                                    keys[7] = 1;
                                } break;
                                case SDLK_s:
                                {
                                    keys[8] = 1;
                                } break;
                                case SDLK_d:
                                {
                                    keys[9] = 1;
                                } break;
                                case SDLK_z:
                                {
                                    keys[0xA] = 1;
                                } break;
                                case SDLK_c:
                                {
                                    keys[0xB] = 1;
                                } break;
                                case SDLK_4:
                                {
                                    keys[0xC] = 1;
                                } break;
                                case SDLK_r:
                                {
                                    keys[0xD] = 1;
                                } break;
                                case SDLK_f:
                                {
                                    keys[0xE] = 1;
                                } break;
                                case SDLK_v:
                               {
                                    keys[0xF] = 1;
                               } break;
                    } break;
                }
                    case SDL_KEYUP:
                        {
                            switch (event.key.keysym.sym) {
                                case SDLK_x:
                                    {
                                        keys[0] = 0;
                                    } break;
                                case SDLK_1:
                                    {
                                        keys[1] = 0;
                                    } break;
                                case SDLK_2:
                                    {
                                        keys[2] = 0;
                                    } break;
                                case SDLK_3:
                                    {
                                        keys[3] = 0;
                                    } break;
                                case SDLK_q:
                                    {
                                        keys[4] = 0;
                                    } break;
                                case SDLK_w:
                                    {
                                        keys[5] = 0;
                                    } break;
                                case SDLK_e:
                                    {
                                        keys[6] = 0;
                                    } break;
                                case SDLK_a:
                                    {
                                        keys[7] = 0;
                                    } break;
                                case SDLK_s:
                                    {
                                        keys[8] = 0;
                                    } break;
                                case SDLK_d:
                                    {
                                        keys[9] = 0;
                                    } break;
                                case SDLK_z:
                                    {
                                        keys[0xA] = 0;
                                    } break;
                                case SDLK_c:
                                    {
                                        keys[0xB] = 0;
                                    } break;
                                case SDLK_4:
                                    {
                                        keys[0xC] = 0;
                                    } break;
                                case SDLK_r:
                                    {
                                        keys[0xD] = 0;
                                    } break;
                                case SDLK_f:
                                    {
                                        keys[0xE] = 0;
                                    } break;
                                case SDLK_v:
                                    {
                                        keys[0xF] = 0;
                                    } break;
                            } 
                        }break;
            }
        }
            return quit;
    }
    private:
        SDL_Window* window{};
        SDL_Renderer* renderer{};
        SDL_Texture* texture{};
};



#endif

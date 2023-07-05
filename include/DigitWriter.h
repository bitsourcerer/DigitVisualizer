#ifndef DIGITWRITER_H_INCLUDED
#define DIGITWRITER_H_INCLUDED

#include "SDL2/SDL.h"
#include "DigitStream.hpp"

const unsigned width = 500, height = 500;
using config::dim;

class DigitWriter
{
public:
  DigitWriter() = delete;
  DigitWriter(const DigitStream&);
  DigitWriter(const char *filename);
  ~DigitWriter();

  void run();

private:
  DigitStream stream;
  Digit digit;

  void init();
  void update();
  void render();

  bool running;

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
};

DigitWriter::DigitWriter(const DigitStream &digit_stream) : stream(digit_stream)
{
  init();
}

DigitWriter::DigitWriter(const char *filename) : DigitWriter(DigitStream(filename))
{
  ;
}

void DigitWriter::init()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
  SDL_RenderSetLogicalSize(renderer, config::dim, config::dim);
}

void DigitWriter::run()
{
  digit = stream.next();
  running = true;
  while(running)
  {
    update();
    render();
  }
}

void DigitWriter::update()
{
  if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
    running = false;
  else if(event.type == SDL_MOUSEBUTTONDOWN)
  {
    if(event.button.button == SDL_BUTTON_LEFT)
      digit = stream.next();
    else if(event.button.button == SDL_BUTTON_RIGHT)
      digit = stream.prev();
    else;
    std::cout << digit << std::endl;
  }
}

void DigitWriter::render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  for (unsigned i = 0; i < dim; ++i)
  {
    for(unsigned j = 0; j < dim; ++j)
    {
      uint8_t color = digit.representation[dim*i + j];
      SDL_SetRenderDrawColor(renderer, color, color, color, color);
      SDL_RenderDrawPoint(renderer, j, i);
    }
  }
  SDL_RenderPresent(renderer);
}

DigitWriter::~DigitWriter()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

#endif // DIGITWRITER_H_INCLUDED

#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "system.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, System &system);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  ~Game();
  int GetScore() const;
  int GetSize() const;
  float GetSpeed();
  void togglePause();
  void increaseSpeed();
  void decreaseSpeed();

private:
  Snake snake;
  SDL_Point food;
  System system_;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  bool isPaused = false;
  float max_speed{0.30};
  float min_speed{0.20};
  int score{0};

  void PlaceFood();
  void Update();
};

#endif
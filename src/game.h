#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"


class Game : public std::enable_shared_from_this<Game>{
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  bool running;
  SDL_Point food;
  SDL_Point extra_food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_e_w;
  std::uniform_int_distribution<int> random_e_h;
  std::uniform_int_distribution<int> put_extra;
  int score{0};
  
  //std::shared_ptr<Game> get_shared_this() { return shared_from_this(); }
  
  void PlaceExtra();
  void PlaceFood();
  void Update();
  
  std::mutex _mutex;
};

#endif
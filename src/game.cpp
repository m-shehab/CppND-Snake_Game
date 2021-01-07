#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      random_e_w(0, static_cast<int>(grid_width)),
      random_e_h(0, static_cast<int>(grid_height)),
      put_extra(0,static_cast<int>(100)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  auto t = std::thread(&Game::PlaceExtra, this);
  renderer.Init_Screen();
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, renderer);
    if(snake.play == Snake::Play::end){
        
      //renderer.UpdateWindowTitle(score, snake.size, frame_count); 
      PlaceFood();
      score = 0;
      {
        std::unique_lock<std::mutex> lck(_mutex);
        extra_food.x = -1;
        extra_food.y = -1;
      }
      continue;
    }
    Update();
    renderer.Render(snake, food,extra_food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++; 
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, snake.size, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
  t.join();
}


void Game::PlaceExtra(){
  int x,y,p,i;
  while(running){
  	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    p = put_extra(engine);
    if(p > 70){
      x = random_e_w(engine);
      y = random_e_h(engine);
      if(!snake.SnakeCell(x, y)){
        std::unique_lock<std::mutex> lck(_mutex);
        extra_food.x = x;
        extra_food.y = y;
        lck.unlock();
        i=0;
        while( x != -1 && y != -1 && i < 10){
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));
          i++;
        }
        lck.lock();
        extra_food.x = -1;
        extra_food.y = -1;
      }      
    } else {
      std::unique_lock<std::mutex> lck(_mutex);
      extra_food.x = -1;
      extra_food.y = -1;
    }
  }
}


void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;
  if(snake.state == Snake::State::pause) return; 
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  
  // Check if there's extra food
  if (extra_food.x == new_x && extra_food.y == new_y){
    score +=3;
    std::unique_lock<std::mutex> lck(_mutex);
    extra_food.x = -1;
    extra_food.y = -1;
  }
  
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
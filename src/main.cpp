#include <iostream>
#include "game.h"
#include "controller.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  auto game = std::make_shared<Game>(kGridWidth, kGridHeight);
  std::cout << "Press s button to start a new game. Press e button to end the game.\n";
  std::cout << "Press p button to pause the game. Press r button to resume the game.\n";
  game->Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  
  return 0;
}

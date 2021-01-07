# CppND Capstone Project: Snake Game 

This is the capstone project of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). In this project, we add some features to the snake game. The starter code for this project was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Project Structure 
The Snake game code consists of four main classes: `Game`, `Snake`, `Controller`, and `Renderer`. The image below shows how the code functions

<img src="snake_game.png"/>

1. To begin, `main` creates a `Controller`, a `Game`, and a `Renderer` object. `Game` stores a `Snake` object as part of the state.
2. `main` calls `Game::Run` to start the game loop. 
3. The `Controller` object is responsible for handling user keyboard input.
4. The `Game` object is responsible for game logic. 
5. The `Renderer` object is responsible for showing graphics. 

## Project Added Features 
In this project we added some keyboard handles to make more interaction with user. A pause/resume feature is added so that the user can pause and resume his game.This is handled using p and r buttons respectively. Another feature is the start/end game so that the user can play more than one game. When the user wants to start a new game he presses s button, and when he wants to finish the game (if he loses for example) he presses e button. 

Another important feature is adding extra food randomly that stay for certain time. The snake, when eats the extra food, gets tripple score without increase in size or speed. To guarantee the concurrent response between the main flow of the game and the extra food feature, the feature is implemented using multithreading. 

On the Screen the user always can see snake score, size, and frames per second. 

## Rupric Points Achieved 
In this project we could achieve several rupric points which are divided into to two categories.

* General Rupric Points in the whole project:
1. The project code is clearly organized into functions.
2. The project accepts user input and processes the input.
3. The project uses Object Oriented Programming techniques.
4. Classes use appropriate access specifiers for class members. 
5. Class constructors utilize member initialization lists.
6. Classes encapsulate behavior.
7. The project makes use of references in function declarations.

* Specific Rupric Points in certain areas of the project:
1. The project uses smart pointers instead of raw pointers. In `main` we used `shared_ptr` to the game object.  
2. The project uses multithreading. In `Game` class, the function `Game::PlaceExtra()` at line 71 of `game.cpp` is executed in an independent thread. The thread is initiated in `Game::Run` function of `game.cpp` file at line 24. 
3. A mutex or lock is used in the project. A mutex is defined in `game.h` and a `unique_lock` is used to protect the `food_extra` variable representing the extra food aded randomely. This is because the variale is accesses from different functions in `game.cpp`: `Game::Update()`, `Game::PlaceExtra()`.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

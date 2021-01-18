# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

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

## Additional function and description

This snake had been extended by various function such as keep the player record (his/her name and score) at the beginning, pause/resume game (by pressing space)  , speed control ( press w to increse speed and press s to decrease speed) and also playing with renderer by changing the window text when it's pause and show the speed when it's on resume. 

The function keep player record controlled by system class, which receive input from user and move itself to game class to evaluate the result (record name and score).

The pause/resume and speed control created by modified game class (add pause status, toggle pause, min/max speed, increase/decrease speed function).

## Additional function and description

This snake had been extended by various function such as keep the player record (his/her name and score) at the beginning, pause/resume game (by pressing space)  , speed control ( press w to increse speed and press s to decrease speed) and also playing with renderer by changing the window text when it's pause and show the speed when it's on resume. 

The function keep player record controlled by system class, which receive input from user and move itself to game class to evaluate the result (record name and score).

The result of system ganerates the record text file in build folder, which keep all the played record.Update

The pause/resume and speed control created by modified game class (add pause status, toggle pause, min/max speed, increase/decrease speed function).

## Rubic Rubric Points


* The project demonstrates an understanding of C++ functions and control structures.
  * Throughout the game.cpp there are many code are working with such as if/else condition in game.cpp or while loop in system.cpp
* The project reads data from a file and process the data, or the program writes data to a file.
  * In system.cpp, this project checking for the record and read data inside before overwriting with new player record to the new one.
* The project accepts user input and processes the input.
  * Before the game start, the system will ask for input to keep the record.
* The project accepts user input and processes the input.
  * Addtional class and function are in formed of OOP techniques.
* Classes use appropriate access specifiers for class members.
  * The private can be accessed only by getter function when use with diffent class.
* Class constructors utilize member initialization lists.
  * Some class has been modified to get more argument and use member initialization lists.
* The project makes use of references in function declarations.
  * Throughout the project many of variables had been passed by reference.
* The project uses move semantics to move data, instead of copying it, where possible.
  * When the system have to working with game instead of main, it moved to game class to get final evaluation


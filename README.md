# UE Game Developer Course

This repository contains Visual Studio solution where each project is a C++ program written for specific homework assignments of _Unreal Engine Game Developer Course_ by Maciej Celmer & Laba.IT.

## 01. SphereVolume
Home Assignment No. 1:
* calculate sphere volume based on radius provided by user
* optional: convert the result into different units

Project has to be compiled with C++20 support as it references `std::numbers::pi` constant introduced there.

## 02. TicTacToe Game
Home Assignment No. 2:
* create TicTacToe game that can be played with computer
* bonus: allow for different board sizes

Implemented TicTacToe Game can be played with a computer opponent (AI 🤖) on user selectable game board size, for which memory is allocated dynamically during runtime.

AI algorithm maybe is not the best in the world, but serviceable and good enough for a challenge! When it's computer turn, it searches for the longest line on the board to which a sign can be added either to the beginning or end side of it. If line found is owned by AI, this move enlongens it and raises chances of computer winning (and SkyNet taking over the world 😉); if opponent's, it blocks further line extension in that direction. If neither AI's nor opponent's line can be found which is feasible of adding a new sign to it, a random cell on the board will be chosen (in edge case scenario where selected board size is big and board is almost full already this can take quite a while unfortunately).

There are, of course, obvious downsides to this implementation, which can be seen after a bit of play, and as such, there is room for improvement.

## 03. Complex Number Class
Home Assignment No. 3:
* write a class to represent complex numbers
* class should contain:
  * default, parametric & copying constructor
  * destructor
  * overloaded operators: `+`, `-`, `*`, `/`, `=`
  * `Print()` method to display complex number
* `main()` function should implement a set of tests of implemented complex number class & operations

## 04. Card Game
Home Assignment No. 4:
* implement a card game

Implemented game is based and follows the rules of Uno card game (https://www.unorules.org).

## 05. Book Library
Home Assignment No. 5:
* create a program simulating book library using class inheritance and data structures from C++ Standard Library
* program must support the following operations:
  * add book
  * delete book
  * rent book to a user
  * return book
  * display state of library
* optional: read/write library state from/to a file (not done).

## 06. Multithreaded App
Home Assignment No. 6:
* implement a simple app following producer-consumer template and using multi-threading and thread synchronization mechanisms
* optional: add statistics UI (number of producers, number of consumers, items processed)
* optional: add possibility to add/remove producers/consumers dynamically

## 07. Hangman Game
Home Assignment No. 7:
* implement Hangman word guessing game
* use Git to track changes
* word list should be read from file
* optional: introduce score system based on how fast user guesses a word and number of guesses left
* optional: introduce high scores system with data stored in file
___
All code written by Hubert Pitura (hpitura@gmail.com)

# UE Game Developer Course

This repository contains Visual Studio solution where each project is a C++ program written for specific homework assignments of _Unreal Engine Game Developer Course_ by Maciej Celmer & Laba.IT.

## 01. SphereVolume
Home Assignment No. 1:
* calculate sphere volume based on radius provided by user
* bonus: convert the result into different units

Project has to be compiled with C++20 support as it references `std::numbers::pi` constant introduced there.

## 02. TicTacToe Game
Home Assignment No. 2:
* create TicTacToe game that can be played with computer
* bonus: allow for different board sizes

Implemented TicTacToe Game can be played with a computer opponent (AI 🤖) on user selectable game board size, for which memory is allocated dynamically during runtime.

AI algoritm maybe is not the best in the world, but serviceable and good enough for a challenge! When it's computer turn, it searches for the longest line on the board to which a sign can be added either to the beginning or end side of it. If line found is owned by AI, this move enlongens it and raises chances of computer winning (and SkyNet taking over the world 😉); if opponent's, it blocks further line extension in that direction. If neither AI's nor opponent's line can be found which is feasible of adding a new sign to it, a random cell on the board will be chosen (in edge case scenario where selected board size is big and board is almost full already this can take quite a while unfortunately).

There are, of course, obvious downsides to this implementation, which can be seen after a bit of play, and as such, there is room for improvement.
___
All code written by Hubert Pitura (hpitura@gmail.com)

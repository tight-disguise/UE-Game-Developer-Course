/* 02. TicTacToe Game.cpp
 *
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 2:
 * - create TicTacToe game that can be played with a computer
 * - board size can be set arbitrarily
 *
 * Code written by Hubert Pitura(hpitura@gmail.com)
 */

#include <iostream>

using namespace std;

int main()
{
    // Welcome message
    cout << "<<< TicTacToe Game: XOXO TERMINAL Edition >>>\n";
    cout << "     ~~(X_X)~ ~~(O_O)~ ~(X_X)~~ ~(O_O)~~     \n";
    cout << "              ~~(X_X)~ ~(O_O)~~              \n";
    cout << "                  ~~(*_*)~~                  \n";
    cout << "                      ~                      \n" << endl;

    // Game host
    const char gameHost[] = "~(*_*)~";

    cout << gameHost << ": Welcome player to the battlegrounds!\n";
    cout << gameHost << ": Be prepared, this fight is TERMINAL!\n";
    cout << gameHost << ": There can be one winner only!\n" << endl;

    // Difficulty selection
    short difficulty = 1;

    cout << gameHost << ": Choose your challenge: 1) minuscule, 2) walk in a park, 3) I feel confident, 4) INSANITY!\n";
    cout << "~> Please enter number (1 - 4): ";
    cin >> difficulty;
}

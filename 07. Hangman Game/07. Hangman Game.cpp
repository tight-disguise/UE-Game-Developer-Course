/* 07. Hangman Game.cpp
*
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 7:
 * implement Hangman word guessing game
 * use Git to track changes
 * word list should be read from file
 * optional: introduce score system based on how fast user guesses a word and number of guesses left
 * optional: introduce high scores system with data stored in file
 * 
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */


#include <iostream>
#include <string>
#include <charconv> // for getInput() function, needs C++20
#include <cstdlib> // for system("pause")

using namespace std;

// Helper function to get correct input from user
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>);

/* MAIN PROGRAM CODE */
int main()
{

    int c = getInput("Test: ");
    
    system("pause");
    return 0;
}

// C++ black magic, not sure how this works, but it works :D
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>)
{
    T num {};
    
    for (string inp;;)
    {
        cin.clear();
        cout << prm;
        
        if (getline(cin, inp) && !inp.empty())
        {
            const auto first {find_if(inp.begin(), inp.end(), [](unsigned ch) {return !isspace(ch); })};
            const auto end {find_if(inp.rbegin(), inp.rend(), [](unsigned ch) {return !isspace(ch); }).base()};
            const auto res {from_chars(to_address(first), to_address(end), num)};

            if (res.ec == errc {} && res.ptr == to_address(end))
                return num;
        }

        // cout << "Invalid input. a(n) " << typeid(T).name() << '\n';
        
        cout << "Invalid input. ";
    }    
}

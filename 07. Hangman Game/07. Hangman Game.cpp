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

#define WINDOWS

#ifdef WINDOWS
#include <cstdlib> // for system("pause")
#endif

#include <iostream>
#include<fstream>
#include <string>
#include <charconv> // for getInput() function, needs C++20
#include <condition_variable> // for thread_wait
#include <random>
#include <vector>




using namespace std;

// Helper function to get correct input from user
template<typename T = int>
typename T getInput(const string& prm) requires (is_arithmetic_v<T>);

/* MAIN PROGRAM CODE */
int main()
{
    // Read words to a vector
    ifstream dictFile ("dictionary.txt");
    string word;
    vector<string> wordsVector;

    if (dictFile.is_open())
        while (getline(dictFile, word))
            wordsVector.emplace_back(word);
    else
    {
        cerr << "Unable to open dictionary.txt, game cannot continue." << endl;

        #ifdef WINDOWS
        system("pause");
        #endif

        return -1;
    }

    // Choose random word
    random_device rd;
    mt19937 e2(rd());
    uniform_int_distribution<int> dist(0, wordsVector.size() - 1);
    word = wordsVector.at(dist(e2));

    // test
    /*while ( true )
    {
        // Sleep for a while
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
        int c = dist(e2);
        cout << c << ": " << wordsVector.at(c) << endl;
    }*/
    
    int c = getInput("Say...:");
    
    #ifdef WINDOWS
    system("pause");
    #endif

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

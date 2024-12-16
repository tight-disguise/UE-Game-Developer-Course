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
#include <condition_variable> // used for sleep_for() for test only
#include <random>
#include <vector>




using namespace std;

// Helper function to get correct input from user
//template<typename T = char>
//typename T getInput(const string& prm) requires (is_arithmetic_v<T>);
char getInputChar(const string& prompt);

/* MAIN PROGRAM CODE */
int main()
{
    // Read words from dictionary file to a vector
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

    // Choose a random word (rand % size didn't work correctly)
    random_device rd;
    mt19937 e2(rd());
    uniform_int_distribution<int> dist(0, wordsVector.size() - 1);
    word = wordsVector.at(dist(e2));

    // some test
    /*while ( true )
    {
        // Sleep for a while
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
        int c = dist(e2);
        cout << c << ": " << wordsVector.at(c) << endl;
    }*/

    // in word we now have our target

    // prepare a mask for guesses
    short wordSize = word.size();
    cout << "Word size: " << wordSize << endl;
    
    short charsStillToGuess { wordSize };
    string guessWord {};
    
    for (int i = 0; i < wordSize; i++)
        guessWord += '*';

    // user input
    while (true)
    {
        // TODO: Check if game lost
        
        cout << guessWord << endl;

        char guessChar {};

        guessChar = getInputChar("Your guess letter [a - z]: ");

        for (int i = 0; i < wordSize; i++)
            if (word[i] == guessChar and guessWord[i] != guessChar)
            {
                guessWord[i] = guessChar;
                charsStillToGuess--;
            }
        
        if (charsStillToGuess == 0)
        {
            cout << guessWord << endl;
            cout << "You won!" << endl;
            break;
        }

        // flush input buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        cout << "Guess the word (/ continues):" << endl;

        string guessString {};
        getline(cin, guessString);
        
        if (guessString[0] == 47) // 47 = / key
            continue;
        else
        {
            // check if the word entered is the word needed
            bool wordFound { true };
            
            for (int i = 0; i < guessString.length(); i++)
                if (word[i] != guessString[i])
                {
                    wordFound = false;
                    //break;
                }

            if (wordFound)
            {
                cout << "Congrats, you guessed correctly! You won!" << endl;
                break;
            }
            else
            {
                cout << guessString << " and " << guessWord << " are not the same!" << endl;
                continue; // not needed but nice :)
            }
        }
    }
    
    #ifdef WINDOWS
    system("pause");
    #endif

    return 0;
}

char getInputChar(const string& prompt)
{
    cout << prompt;
    char inputChar {};
    bool inputOK { false };

    while (!inputOK)
    {
        cin >> inputChar;
        if (inputChar >= 'a' and inputChar <= 'z')
            inputOK = true;
        else
        {
            cout << prompt;
        }
    }    
    return inputChar;
}
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
#include <random>
#include <vector>

using namespace std;

#define STARTING_SCORE 100000 // points number at start
#define NO_OF_ROUNDS 10 // each round we decrement STARTING_SCORE / NO_OF_ROUNDS from score, if score <= 0, player looses

// Helper function to get char input from user
char getInputChar(const string& prompt);

/* MAIN PROGRAM CODE */
int main()
{
    // This is very simple implementation due to lack of time.
    // Fully functional, but quite bare bones and could be refactored :D
    // Anyway, the main learning objective was to use Git.
    // So have I done... and the game works too :)

    /*
     * INITIALIZE
     */
    
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
    
    // in word variable we now have our target word
    word = wordsVector.at(dist(e2));
    
    // some variables
    short wordSize = word.size();
    short charsStillToGuess { wordSize };
    short turn { 0 };
    int score { STARTING_SCORE };
    string guessWord {};

    // prepare mask for player guesses
    for (int i = 0; i < wordSize; i++)
        guessWord += '*';

    /*
     * SPLASH SCREEN
     */
    cout << ">>> Welcome to HANGMAN! <<<\n"
            "Game about death caused by your poor fluency in English vocabulary.\n" << endl;
    
    /*
     * GAME LOOP
     */
    while (true)
    {
        char guessChar {};
        bool charFound { false };
        turn++;
        
        // RENDER
        cout << "Turn: " << turn << " | Score: " << score << endl;
        cout << "Guessword: " << guessWord << endl;

        // USER INPUT
        guessChar = getInputChar("Your guess letter [a - z]: ");

        // GAME UPDATE
        for (int i = 0; i < wordSize; i++)
            if (word[i] == guessChar and guessWord[i] != guessChar)
            {
                guessWord[i] = guessChar;
                charsStillToGuess--;
                charFound = true;
            }

        // score counting
        if (charFound)
            score += STARTING_SCORE / NO_OF_ROUNDS;
        else
            score -= STARTING_SCORE / NO_OF_ROUNDS;

        // USER INPUT
        cout << "Guess word: " << guessWord << endl;

        // flush input buffer
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        cout << "Guess the word (Enter key continues):" << endl;

        string guessString {};
        
        getline(cin, guessString);

        // GAME UPDATE
        if (!guessString.empty())
        {
            // check if the word entered is the word needed
            bool wordFound { true };
            
            for (int i = 0; i < guessString.length(); i++)
                if (word[i] != guessString[i])
                    wordFound = false;

            // check the case if someone input starting substring of a word only
            if (wordFound and wordSize != guessString.length())
                wordFound = false;

            // Check winning/loosing conditions
            if (wordFound)
            {
                cout << "Congrats, you guessed correctly! You won! Your score: " << score << endl;
                break;
            }
            else
            {
                cout << guessString << " and " << guessWord << " are not the same!\n" << endl;
                continue; // not needed but nice :)
            }
        }

        // Check if game won due to all characters guessed
        if (charsStillToGuess == 0)
        {
            cout << guessWord << endl;
            cout << "You won! Your score: " << score << endl;
            break;
        }
        
        // Check if game lost due to score <= 0
        if (score <= 0)
        {
            cout << "You lost! Your score is 0!" << endl;
            cout << "The word was: " << word << endl;
            break;
        }
    }

    // some shenanigans
    #ifdef WINDOWS
    system("pause");
    #endif

    return 0;
}

// Get a char from user
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
/* 02. TicTacToe Game.cpp
 *
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 2:
 * - create TicTacToe game that can be played with a computer
 * - board size can be set arbitrarily
 *
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <cstdlib>  // srand() & rand()

using namespace std;

// Game board
char* gameBoard;
short BOARD_SIZE = 3;

// Board cell index either out of bounds or cell already taken opponent
#define NOT_AVAILABLE -1

const char emptySign = '-';
const char playerSign = 'X';
const char AISign = 'O';

// Game host
const char gameHost[] = "~(*_*)~";

char currentPlayerSign = playerSign;

int totalInputs = 0;

void Initialize();
void DisplayGameBoard();
void GetPlayerInput();
void GetRandomAIInput();
void GetSmartAIInput();
bool CheckGameState();
void ChangePlayer();
void Deintialize();

/* MAIN PROGRAM CODE */
// program does not have proper input data validation as it was not set as a requirement :)
int main()
{
    // Welcome message
    cout << "<<< TicTacToe Game: XOXO TERMINAL Edition >>>\n";
    cout << "     ~~(X_X)~ ~~(O_O)~ ~(X_X)~~ ~(O_O)~~     \n";
    cout << "              ~~(X_X)~ ~(O_O)~~              \n";
    cout << "                  ~~(*_*)~~                  \n";
    cout << "                      ~                      \n" << endl;

    cout << gameHost << ": Welcome to the deadly battlegrounds!\n";
    cout << gameHost << ": Be prepared, this fight is TERMINAL!\n";
    cout << gameHost << ": There can be one winner only!\n" << endl;

    // Difficulty selection
    char difficulty = '1';
    short inputOK = false;

    cout << gameHost << ": Please choose your challenge:\n"
                 "           1) minuscule\n"
                 "           2) walk in a park\n"
                 "           3) I feel confident\n"
                 "           4) madness!\n"
                 "           5) INSANITY!!\n"
                 "           6) ASTRONOMICAL...\n"
                 "              ...IMPOSSIBILITY!!!\n" << endl;
    
    while (!inputOK)
    {
        cout << "~> Please enter number (1 - 6): ";
        cin >> difficulty;

        if (!(difficulty < '1' or difficulty > '6'))
            inputOK = true;
    }

    cout << "\n" << gameHost << ": Let the game begin, you play with X!"
            "\n" << gameHost << ": Good luck!\n" << endl;

    // Set board size base on chosen difficulty
    switch (difficulty)
    {
        case '1':
            BOARD_SIZE = 3;
            break;
        case '2':
            BOARD_SIZE = 5;
            break;
        case '3':
            BOARD_SIZE = 7;
            break;
        case '4':
            BOARD_SIZE = 12;
            break;
        case '5':
            BOARD_SIZE = 20;
            break;
        case '6':
            BOARD_SIZE = 35; // max that looks nice on default terminal size
            break;
    }

    // Setup game board
    Initialize();
    
    // Game loop
    while (true)
    {
        DisplayGameBoard();
        
        if (currentPlayerSign == playerSign)
            GetPlayerInput();
        else
            //GetRandomAIInput();
            GetSmartAIInput();
        
        totalInputs++;

        if (CheckGameState())
        {
            DisplayGameBoard();
            
            if (currentPlayerSign == playerSign)
            {
                cout << gameHost << ": You win!\n";
                cout << gameHost << ": AI's gonna be TERMINALLED!" << endl;
            }
            else
            {
                cout << gameHost << ": You've been TERMINALLED!\n";
                cout << gameHost << ": AI wins, SkyNet's coming!" << endl;
            }
            break;
        }

        // Stop the game if we ran out of cells on board and nobody won
        if (totalInputs == BOARD_SIZE * BOARD_SIZE)
        {
            DisplayGameBoard();
            cout << gameHost << ": Sadly, there is no winner this time!\n";
            cout << gameHost << ": TERMINAL fight is over!" << endl;
            break;
        }
        else
            ChangePlayer();
    }

    // Free allocated memory
    Deintialize();
}

// Set up game board
void Initialize()
{
    gameBoard = new char[BOARD_SIZE * BOARD_SIZE];

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            *(gameBoard + y * BOARD_SIZE + x) = emptySign;
        }
    }
}

void DisplayGameBoard()
{
    // Board is displayed and input taken starting from 1, not 0 (more user friendly :))
    // Display column numbers
    if (BOARD_SIZE >= 10)
    {
        // Trailing spaces or tens digit
        cout << "           ";
        for (int x = 10; x <= BOARD_SIZE; x++)
        {
            cout << x / 10;
        }
        cout << "\n ";
    }

    cout << ' ';

    for (int x = 0; x < BOARD_SIZE; x++)
    {
        cout << (x + 1) % 10;
    }
    cout << endl;

    // Rows
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        // Trailing spaces or tens digit
        if (BOARD_SIZE >= 10)
        {
            if (y < 9)
                cout << " ";
            else
                cout << (y + 1) / 10;
        }

        // Row number (starting from 1)
        cout << (y + 1) % 10;

        for (int x = 0; x < BOARD_SIZE; x++)
        {
            cout << *(gameBoard + y * BOARD_SIZE + x);
        }
        cout << endl;
    }

    cout << endl;
}

void GetPlayerInput()
{
    bool inputOK = false;
    
    while(!inputOK)
    {
        short x, y;

        cout << "Input X: ";
        cin >> x;
        cout << "Input Y: ";
        cin >> y;

        // User provides input starting from 1, so we need to decrement cell indexes
        x--;
        y--;

        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        {
            if (*(gameBoard + y * BOARD_SIZE + x) == emptySign)
            {
                *(gameBoard + y * BOARD_SIZE + x) = playerSign;
                inputOK = true;
            }
            else
                cout << gameHost << ": Already taken, please try again!\n";
        }
        else
            cout << gameHost << ": Wrong input, please try again!\n";

        cout << endl;
    }
}

// Completely random AI input
// (this can take some serious time if called when board is filled already and it's big)
void GetRandomAIInput()
{
    short x, y;
    bool inputOK = false;

    srand(time(nullptr));

    while (!inputOK)
    {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
        
        if (*(gameBoard + y * BOARD_SIZE + x) == emptySign)
        {
            *(gameBoard + y * BOARD_SIZE + x) = AISign;
            inputOK = true;
        }        
    }

    // Indexes are displayed starting from 1
    cout << "Random AI X: " << x + 1 << "\nRandom AI Y: " << y + 1 << "\n" << endl;
}

// Lots of global variables ;)
// Used for searching of same sign sequences
short maxLineLength = 0;
short maxLineX = NOT_AVAILABLE;
short maxLineY = NOT_AVAILABLE;

short currentLineLength = 0;
short inFrontX = NOT_AVAILABLE;
short inFrontY = NOT_AVAILABLE;
short afterEndX = NOT_AVAILABLE;
short afterEndY = NOT_AVAILABLE;

// Helper function to search for the longest same sign sequence...
// ...at which beginning or an end a new AI sign can be placed.
// (either to prolong AI sequence or block the player)
void findSequence(char);

// A bit more sophisticated AI input
void GetSmartAIInput()
{    
    // Beginning of the game, no point in searching for lines at this stage, just put random AI sign somewhere
    if (totalInputs == 0 or totalInputs == 1)
    {
        GetRandomAIInput();
    }
    else
    {
        maxLineLength = 0;
        maxLineX = NOT_AVAILABLE;
        maxLineY = NOT_AVAILABLE;

        findSequence(AISign);
        // cout << "findSequence(AISign)    : maxLineLength = " << maxLineLength 
        //      << " | maxLineX = " << maxLineX << " | maxLineY = " << maxLineY << endl;
        
        findSequence(playerSign);
        // cout << "findSequence(playerSign): maxLineLength = " << maxLineLength 
        //      << " | maxLineX = " << maxLineX << " | maxLineY = " << maxLineY << endl;

        // Put AI sign on board
        if ((maxLineX != NOT_AVAILABLE) and (maxLineY != NOT_AVAILABLE))
        {
            *(gameBoard + maxLineY * BOARD_SIZE + maxLineX) = AISign;
            // Indexes are displayed starting from 1
            cout << "Smart AI X: " << maxLineX + 1 << "\nSmart AI Y: " << maxLineY + 1 << "\n" << endl;
        }
        else // no sequence found, choose random cell on board
        {
            // (this can take some serious time if called when board is filled already and it's big)
            GetRandomAIInput();
        }
    } // else
}

void findSequence(char signToLookFor)
{
    currentLineLength = 0;
    inFrontX = NOT_AVAILABLE;
    inFrontY = NOT_AVAILABLE;
    afterEndX = NOT_AVAILABLE;
    afterEndY = NOT_AVAILABLE;

    // Check for the longest AI line in rows
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        // We iterate over elements of a row
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (*(gameBoard + y * BOARD_SIZE + x) == signToLookFor)
            {
                // We found line start
                if (currentLineLength == 0)
                {
                    // Is it possible to put a sign in front of this line? If so, save position
                    // Is the index not out of bounds?
                    if (x - 1 >= 0)
                    {
                        // Is the board cell free?
                        if (*(gameBoard + y * BOARD_SIZE + (x - 1)) == emptySign)
                            inFrontX = x - 1;
                        // inFrontY = y; // not needed, column stays the same anyway
                    }
                    // It's not possible
                    else
                    {
                        inFrontX = NOT_AVAILABLE;
                        // inFrontY = NOT_AVAILABLE; // not needed, column stays the same anyway
                    }
                }

                // Count up the length
                currentLineLength++;

                // If we found AI sign at the last cell in a row,
                // we know it's not possible to put a sign after it
                if (x + 1 == BOARD_SIZE)
                {
                    // Is it the longest line found and is it possible to add a sign at the front of it?
                    if ((currentLineLength > maxLineLength) and (inFrontX != NOT_AVAILABLE))
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = inFrontX;
                        maxLineY = y;
                    }

                    currentLineLength = 0;
                    inFrontX = NOT_AVAILABLE;
                    afterEndX = NOT_AVAILABLE;
                    // afterEndY = NOT_AVAILABLE; // not needed, row stays the same anyway
                }

            }
            else if (*(gameBoard + y * BOARD_SIZE + x) == emptySign)
            {
                if (currentLineLength != 0)
                {
                    afterEndX = x;
                    // afterEndY = y; // not needed, row stays the same anyway
                }

                // Is it the longest line found?
                // (if we're here it's for sure possible to add AI sign at least at the end of a line)
                if (currentLineLength > maxLineLength)
                {
                    maxLineLength = currentLineLength;

                    // Select either front cell or end cell depending on what's available
                    if ((inFrontX != NOT_AVAILABLE) and (afterEndX != NOT_AVAILABLE))
                        maxLineX = (rand() % 2) ? inFrontX : afterEndX;
                    else if (inFrontX != NOT_AVAILABLE)
                        maxLineX = inFrontX;
                    else
                        maxLineX = afterEndX;

                    maxLineY = y;
                }

                currentLineLength = 0;
                inFrontX = NOT_AVAILABLE;
                afterEndX = NOT_AVAILABLE;
            }
            else // !(signToLookFor or emptySign)
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                {
                    // We can add AI sign at the front
                    if (inFrontX != NOT_AVAILABLE)
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = inFrontX;
                        maxLineY = y;
                    }

                    // It's not possible to add anything at the front nor the end
                }

                currentLineLength = 0;
                inFrontX = NOT_AVAILABLE;
                inFrontY = NOT_AVAILABLE;
                afterEndX = NOT_AVAILABLE;
                afterEndY = NOT_AVAILABLE;
            }
        } // x
    } // y

    currentLineLength = 0;
    inFrontX = NOT_AVAILABLE;
    inFrontY = NOT_AVAILABLE;
    afterEndX = NOT_AVAILABLE;
    afterEndY = NOT_AVAILABLE;

    // Check for the longest AI line in columns
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        //currentLineLength = 0;
        
        // We iterate over elements of a column
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (*(gameBoard + y * BOARD_SIZE + x) == signToLookFor)
            {
                // We found line start
                if (currentLineLength == 0)
                {
                    // Is it possible to put a sign in front (top) of this line? If so, save position
                    // Is the index not out of bounds?
                    if (y - 1 >= 0)
                    {
                        // Is the board cell free?
                        if (*(gameBoard + (y - 1) * BOARD_SIZE + x) == emptySign)
                            inFrontY = y - 1;
                            // inFrontX = x; // not needed, row stays the same anyway
                    }
                    // It's not possible
                    else
                    {
                        // inFrontX = NOT_AVAILABLE; // not needed, row stays the same anyway
                        inFrontY = NOT_AVAILABLE;
                    }
                }

                // Count up the length
                currentLineLength++;

                // If we found AI sign at the last cell in a column,
                // we know it's not possible to put a sign after it
                if (y + 1 == BOARD_SIZE)
                {
                    // Is it the longest line found and is it possible to add a sign at the front of it?
                    if ((currentLineLength > maxLineLength) and (inFrontY != NOT_AVAILABLE))
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = x;
                        maxLineY = inFrontY;
                    }

                    currentLineLength = 0;
                    inFrontY = NOT_AVAILABLE;
                    afterEndY = NOT_AVAILABLE;
                    // afterEndX = NOT_AVAILABLE; // not needed, column stays the same anyway
                }

            }
            else if (*(gameBoard + y * BOARD_SIZE + x) == emptySign)
            {
                if (currentLineLength != 0)
                {
                    // afterEndX = x;  // not needed, column stays the same anyway
                    afterEndY = y;
                }

                // Is it the longest line found?
                // (if we're here it's for sure possible to add AI sign at least at the end of a line)
                if (currentLineLength > maxLineLength)
                {
                    maxLineLength = currentLineLength;

                    // Select either front cell or end cell depending on what's available
                    if ((inFrontY != NOT_AVAILABLE) and (afterEndY != NOT_AVAILABLE))
                        maxLineY = (rand() % 2) ? inFrontY : afterEndY;
                    else if (inFrontY != NOT_AVAILABLE)
                        maxLineY = inFrontY;
                    else
                        maxLineY = afterEndY;

                    maxLineX = x;
                }

                currentLineLength = 0;
                inFrontY = NOT_AVAILABLE;
                afterEndY = NOT_AVAILABLE;
            }
            else // !(signToLookFor or emptySign)
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                {
                    // We can add AI sign at the front
                    if (inFrontY != NOT_AVAILABLE)
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = x;
                        maxLineY = inFrontY;
                    }

                    // It's not possible to add anything at the front nor the end
                }
                
                currentLineLength = 0;
                inFrontX = NOT_AVAILABLE;
                inFrontY = NOT_AVAILABLE;
                afterEndX = NOT_AVAILABLE;
                afterEndY = NOT_AVAILABLE;
            }
        } // y
    } // x

    currentLineLength = 0;
    inFrontX = NOT_AVAILABLE;
    inFrontY = NOT_AVAILABLE;
    afterEndX = NOT_AVAILABLE;
    afterEndY = NOT_AVAILABLE;

    // Look in \ diagonal...
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (*(gameBoard + i * BOARD_SIZE + i) == signToLookFor)
        {
            // We found line start
            if (currentLineLength == 0)
            {
                // Is it possible to put a sign in front of this line? If so, save position
                // Is the index not out of bounds?
                if (i - 1 >= 0)
                {
                    // Is the board cell free?
                    if (*(gameBoard + (i - 1) * BOARD_SIZE + (i - 1)) == emptySign)
                    {
                        inFrontX = i - 1;
                        inFrontY = i - 1;
                    }
                }
                // It's not possible
                else
                {
                    inFrontX = NOT_AVAILABLE;
                    inFrontY = NOT_AVAILABLE;
                }
            }

            // Count up the length
            currentLineLength++;

            // If we found AI sign at the last cell in a diagonal,
            // we know it's not possible to put a sign after it
            if (i + 1 == BOARD_SIZE)
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength > maxLineLength) and (inFrontX != NOT_AVAILABLE) and (inFrontY != NOT_AVAILABLE))
                {
                    maxLineLength = currentLineLength;
                    maxLineX = inFrontX;
                    maxLineY = inFrontY;
                }

                currentLineLength = 0;
                inFrontX = NOT_AVAILABLE;
                inFrontY = NOT_AVAILABLE;
                afterEndX = NOT_AVAILABLE;
                afterEndY = NOT_AVAILABLE;
            }
        }
        else if (*(gameBoard + i * BOARD_SIZE + i) == emptySign)
        {
            if (currentLineLength != 0)
            {
                afterEndX = i;
                afterEndY = i;
            }

            // Is it the longest line found?
            // (if we're here it's for sure possible to add AI sign at least at the end of a line within diagonal)
            if (currentLineLength > maxLineLength)
            {
                maxLineLength = currentLineLength;

                // Select either front cell or end cell depending on what's available
                // (checking only for X, as it's the same for Y)
                if ((inFrontX != NOT_AVAILABLE) and (afterEndX != NOT_AVAILABLE))
                {
                    maxLineX = (rand() % 2) ? inFrontX : afterEndX;
                    maxLineY = maxLineX;
                }
                else if (inFrontX != NOT_AVAILABLE)
                {
                    maxLineX = inFrontX;
                    maxLineY = maxLineX;
                }
                else
                {
                    maxLineX = afterEndX;
                    maxLineY = maxLineX;
                }
            }

            currentLineLength = 0;
            inFrontX = NOT_AVAILABLE;
            inFrontY = NOT_AVAILABLE;
            afterEndX = NOT_AVAILABLE;
            afterEndY = NOT_AVAILABLE;
        }
        else // !(signToLookFor or emptySign)
        {
            // Is it the longest line found and is it possible to add a sign at the front of it?
            if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
            {
                // We can add AI sign at the front
                if (inFrontX != NOT_AVAILABLE)
                {
                    maxLineLength = currentLineLength;
                    maxLineX = inFrontX;
                    // x = y
                    maxLineY = maxLineX;
                }

                // It's not possible to add anything at the front nor the end
            }

            currentLineLength = 0;
            inFrontX = NOT_AVAILABLE;
            inFrontY = NOT_AVAILABLE;
            afterEndX = NOT_AVAILABLE;
            afterEndY = NOT_AVAILABLE;
        }
    } // i

    currentLineLength = 0;
    inFrontX = NOT_AVAILABLE;
    inFrontY = NOT_AVAILABLE;
    afterEndX = NOT_AVAILABLE;
    afterEndY = NOT_AVAILABLE;

    // Look in / diagonal...
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (*(gameBoard + (BOARD_SIZE - 1 - i) * BOARD_SIZE + i) == signToLookFor)
        {
            // We found line start
            if (currentLineLength == 0)
            {
                // Is it possible to put a sign in front of this line? If so, save position
                // Is the index not out of bounds?
                if ((i - 1 >= 0) and (BOARD_SIZE - i >= 0))
                {
                    // Is the board cell free?
                    if (*(gameBoard + (BOARD_SIZE - i) * BOARD_SIZE + (i - 1)) == emptySign)
                    {
                        inFrontX = i - 1;
                        inFrontY = BOARD_SIZE - i;
                    }
                }
                // It's not possible
                else
                {
                    inFrontX = NOT_AVAILABLE;
                    inFrontY = NOT_AVAILABLE;
                }
            }

            // Count up the length
            currentLineLength++;

            // If we found AI sign at the last cell in a diagonal,
            // we know it's not possible to put a sign after it
            if (i + 1 == BOARD_SIZE)
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength > maxLineLength) and (inFrontX != NOT_AVAILABLE) and (inFrontY != NOT_AVAILABLE))
                {
                    maxLineLength = currentLineLength;
                    maxLineX = inFrontX;
                    maxLineY = inFrontY;
                }

                currentLineLength = 0;
                inFrontX = NOT_AVAILABLE;
                inFrontY = NOT_AVAILABLE;
                afterEndX = NOT_AVAILABLE;
                afterEndY = NOT_AVAILABLE;
            }
        }
        else if (*(gameBoard + (BOARD_SIZE - 1 - i) * BOARD_SIZE + i) == emptySign)
        {
            if (currentLineLength != 0)
            {
                afterEndX = i;
                afterEndY = BOARD_SIZE - 1 - i;
            }

            // Is it the longest line found?
            // (if we're here it's for sure possible to add AI sign at least at the end of a line within diagonal)
            if (currentLineLength > maxLineLength)
            {
                maxLineLength = currentLineLength;

                // Select either front cell or end cell depending on what's available
                // (checking only for X, as it's the same for Y)
                if ((inFrontX != NOT_AVAILABLE) and (afterEndX != NOT_AVAILABLE))
                {
                    switch (rand() % 2)
                    {
                    case 0:
                        maxLineX = inFrontX;
                        maxLineY = inFrontY;
                        break;
                    case 1:
                        maxLineX = afterEndX;
                        maxLineY = afterEndY;
                        break;
                    }
                }
                else if (inFrontX != NOT_AVAILABLE)
                {
                    maxLineX = inFrontX;
                    maxLineY = inFrontY;
                }
                else
                {
                    maxLineX = afterEndX;
                    maxLineY = afterEndY;
                }
            }

            currentLineLength = 0;
            inFrontX = NOT_AVAILABLE;
            inFrontY = NOT_AVAILABLE;
            afterEndX = NOT_AVAILABLE;
            afterEndY = NOT_AVAILABLE;
        }
        else // !(signToLookFor or emptySign)
        {
            // Is it the longest line found and is it possible to add a sign at the front of it?
            if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
            {
                // We can add AI sign at the front
                if (inFrontX != NOT_AVAILABLE)
                {
                    maxLineLength = currentLineLength;
                    maxLineX = inFrontX;
                    maxLineY = inFrontY;
                }

                // It's not possible to add anything at the front nor the end
            }

            currentLineLength = 0;
            inFrontX = NOT_AVAILABLE;
            inFrontY = NOT_AVAILABLE;
            afterEndX = NOT_AVAILABLE;
            afterEndY = NOT_AVAILABLE;
        }
    } // i
}

// Check if current player has won the game
bool CheckGameState()
{
    bool result = true;

    // Check for win state in rows
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        result = true;

        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (*(gameBoard + y * BOARD_SIZE + x) != currentPlayerSign)
            {
                result = false;
                break;
            }
        }
        if (result) 
            return true;
    }
    
    // Check for win state in columns
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        result = true;

        for (int y = 0; y < BOARD_SIZE; y++)
        {
            if (*(gameBoard + y * BOARD_SIZE + x) != currentPlayerSign)
            {
                result = false;
                break;
            }
        }
        if (result) 
            return true;
    }

    // Check for diagonals
    result = true;

    // It's either \ diagonal...
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (*(gameBoard + i * BOARD_SIZE + i) != currentPlayerSign)
            {
                result = false;
            }
    }
    if (result)
        return true;

    // ...or / diagonal
    result = true;
    
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (*(gameBoard + (BOARD_SIZE - 1 - i) * BOARD_SIZE + i) != currentPlayerSign)
            {
                result = false;
            }
    }
    if (result)
        return true;

    // No win this time
    return false;
}

void ChangePlayer()
{
    (currentPlayerSign == playerSign) ?
        currentPlayerSign = AISign : currentPlayerSign = playerSign;
}

void Deintialize()
{
    // Free allocated memory
    delete[] gameBoard;
}
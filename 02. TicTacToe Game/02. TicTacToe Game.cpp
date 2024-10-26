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
#include <cstdlib>  // rand()

using namespace std;

#define BOARD_SIZE      5

// Board cell index either out of bounds or cell already taken opponent
#define NOT_AVAILABLE   -1

char gameBoard[BOARD_SIZE][BOARD_SIZE];

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

//int main()
//{
//    while (1)
//    {
//        srand(time(nullptr));
//        int x = rand() % 3;
//        int y = rand() % 3;
//
//        cout << x << "  " << y << endl;
//        cin >> x;
//    }
//
//    return 0;
//}

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

    //// Difficulty selection
    //short difficulty = 1;

    //cout << gameHost << ": Choose your challenge: 1) minuscule, 2) walk in a park, 3) I feel confident, 4) INSANITY!\n";
    //cout << "~> Please enter number (1 - 4): ";
    //cin >> difficulty;


    Initialize();
    
    // Game loop
    while(true)
    {
        DisplayGameBoard();
        
        if (currentPlayerSign == playerSign)
            GetPlayerInput();
        else
            GetSmartAIInput();
        
        totalInputs++;

        if(CheckGameState())
        {
            DisplayGameBoard();
            cout << gameHost << ": " << currentPlayerSign << " player wins!" << endl;
            break;
        }

        // Stop the game if we ran out of cells on board and nobody won
        if (totalInputs == BOARD_SIZE * BOARD_SIZE)
        {
            DisplayGameBoard();
            cout << gameHost << ": Sadly, there are no winners this time!" << endl;
            break;
        }
        else
            ChangePlayer();
    }

    // Deintialize();
}

// Set up game board
void Initialize()
{
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        for(int y = 0; y < BOARD_SIZE; y++)
        {
            gameBoard[x][y] = emptySign;
        }
    }
}

void DisplayGameBoard()
{
    // display column numbers
    // TODO: support rows & columns >=10 (double digits)
    cout << ' ';
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        cout << x;
    }
    cout << endl;

    for(int y = 0; y < BOARD_SIZE; y++)
    {
        cout << y;

        for(int x = 0; x < BOARD_SIZE; x++)
        {
            cout << gameBoard[x][y];
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

        // TODO: add input validation
        cout << "Input X: ";
        cin >> x;
        cout << "Input Y: ";
        cin >> y;

        if(x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        {
            if (gameBoard[x][y] == emptySign)
            {
                gameBoard[x][y] = playerSign;
                inputOK = true;
            }
            else
                cout << gameHost << ": Already taken, please try again!\n";
        }

        cout << endl;
    }
}

// Completely random AI input
// (this can take some time if called when board is filled already)
void GetRandomAIInput()
{
    short x, y;
    bool inputOK = false;

    while (!inputOK)
    {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;

        if (gameBoard[x][y] == emptySign)
        {
            gameBoard[x][y] = AISign;
            inputOK = true;
        }        
    }

    cout << "Random AI X: " << x << "\nRandom AI Y: " << y << "\n" << endl;
}

// A bit more sophisticated AI input
void GetSmartAIInput()
{
    short maxLineLength = 0;
    short maxLineX = NOT_AVAILABLE;
    short maxLineY = NOT_AVAILABLE;

    short currentLineLength = 0;
    short inFrontX = NOT_AVAILABLE;
    short inFrontY = NOT_AVAILABLE;
    short afterEndX = NOT_AVAILABLE;
    short afterEndY = NOT_AVAILABLE;
    
    // Beginning of the game, no point in searching for lines at this stage, just put random AI sign somewhere
    if (totalInputs == 0 or totalInputs == 1)
    {
        GetRandomAIInput();
    }
    else
    {
        // Check for the longest AI line in rows
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            // We iterate over elements of a row
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                if (gameBoard[x][y] == AISign)
                {
                    // We found line start
                    if (currentLineLength == 0)
                    {
                        // Is it possible to put a sign in front of this line? If so, save position
                        // Is the index not out of bounds?
                        if (x - 1 >= 0)
                        {
                            // Is the board cell free?
                            if (gameBoard[x - 1][y] == emptySign)
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
                else if (gameBoard[x][y] == emptySign)
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

                        currentLineLength = 0;
                        inFrontX = NOT_AVAILABLE;
                        afterEndX = NOT_AVAILABLE;
                    }
                }
                else // playerSign
                {
                    // Is it the longest line found and is it possible to add a sign at the front of it?
                    if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                    {
                        // It's not possible to add anything at the front nor the end
                        if (inFrontX == NOT_AVAILABLE)
                        {
                            currentLineLength = 0;
                            inFrontX = NOT_AVAILABLE;
                            afterEndX = NOT_AVAILABLE;
                        }
                        else // We can add AI sign at the front
                        {
                            maxLineLength = currentLineLength;
                            maxLineX = inFrontX;
                            maxLineY = y;

                            currentLineLength = 0;
                            inFrontX = NOT_AVAILABLE;
                            afterEndX = NOT_AVAILABLE;
                        }
                    }

                    continue;
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
            // We iterate over elements of a column
            for (int y = 0; y < BOARD_SIZE; y++)
            {
                if (gameBoard[x][y] == AISign)
                {
                    // We found line start
                    if (currentLineLength == 0)
                    {
                        // Is it possible to put a sign in front (top) of this line? If so, save position
                        // Is the index not out of bounds?
                        if (y - 1 >= 0)
                        {
                            // Is the board cell free?
                            if (gameBoard[x][y - 1] == emptySign)
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
                else if (gameBoard[x][y] == emptySign)
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

                        currentLineLength = 0;
                        inFrontY = NOT_AVAILABLE;
                        afterEndY = NOT_AVAILABLE;
                    }
                }
                else // playerSign
                {
                    // Is it the longest line found and is it possible to add a sign at the front of it?
                    if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                    {
                        // It's not possible to add anything at the front nor the end
                        if (inFrontY == NOT_AVAILABLE)
                        {
                            currentLineLength = 0;
                            inFrontY = NOT_AVAILABLE;
                            afterEndY = NOT_AVAILABLE;
                        }
                        else // We can add AI sign at the front
                        {
                            maxLineLength = currentLineLength;
                            maxLineX = x;
                            maxLineY = inFrontY;

                            currentLineLength = 0;
                            inFrontY = NOT_AVAILABLE;
                            afterEndY = NOT_AVAILABLE;
                        }
                    }

                    continue;
                }
            } // x
        } // y
        
        currentLineLength = 0;
        inFrontX = NOT_AVAILABLE;
        inFrontY = NOT_AVAILABLE;
        afterEndX = NOT_AVAILABLE;
        afterEndY = NOT_AVAILABLE;

        // Look in \ diagonal...
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (gameBoard[i][i] == AISign)
            {
                // We found line start
                if (currentLineLength == 0)
                {
                    // Is it possible to put a sign in front of this line? If so, save position
                    // Is the index not out of bounds?
                    if (i - 1 >= 0)
                    {
                        // Is the board cell free?
                        if (gameBoard[i - 1][i - 1] == emptySign)
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
            else if (gameBoard[i][i] == emptySign)
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

                    currentLineLength = 0;
                    inFrontX = NOT_AVAILABLE;
                    inFrontY = NOT_AVAILABLE;
                    afterEndX = NOT_AVAILABLE;
                    afterEndY = NOT_AVAILABLE;
                }
            }
            else // playerSign
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                {
                    // It's not possible to add anything at the front nor the end
                    if (inFrontX == NOT_AVAILABLE)
                    {
                        currentLineLength = 0;
                        inFrontX = NOT_AVAILABLE;
                        inFrontY = NOT_AVAILABLE;
                        afterEndX = NOT_AVAILABLE;
                        afterEndY = NOT_AVAILABLE;
                    }
                    else // We can add AI sign at the front
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = inFrontX;
                        maxLineY = maxLineX;

                        currentLineLength = 0;
                        inFrontX = NOT_AVAILABLE;
                        inFrontY = NOT_AVAILABLE;
                        afterEndX = NOT_AVAILABLE;
                        afterEndY = NOT_AVAILABLE;
                    }
                }

                continue;
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
            if (gameBoard[i][BOARD_SIZE - 1 - i] == AISign)
            {
                // We found line start
                if (currentLineLength == 0)
                {
                    // Is it possible to put a sign in front of this line? If so, save position
                    // Is the index not out of bounds?
                    if ((i - 1 >= 0) and (BOARD_SIZE - i >= 0))
                    {
                        // Is the board cell free?
                        if (gameBoard[i - 1][BOARD_SIZE - i] == emptySign)
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
            else if (gameBoard[i][BOARD_SIZE - 1 - i] == emptySign)
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

                    currentLineLength = 0;
                    inFrontX = NOT_AVAILABLE;
                    inFrontY = NOT_AVAILABLE;
                    afterEndX = NOT_AVAILABLE;
                    afterEndY = NOT_AVAILABLE;
                }
            }
            else // playerSign
            {
                // Is it the longest line found and is it possible to add a sign at the front of it?
                if ((currentLineLength != 0) and (currentLineLength > maxLineLength))
                {
                    // It's not possible to add anything at the front nor the end
                    if (inFrontX == NOT_AVAILABLE)
                    {
                        currentLineLength = 0;
                        inFrontX = NOT_AVAILABLE;
                        inFrontY = NOT_AVAILABLE;
                        afterEndX = NOT_AVAILABLE;
                        afterEndY = NOT_AVAILABLE;
                    }
                    else // We can add AI sign at the front
                    {
                        maxLineLength = currentLineLength;
                        maxLineX = inFrontX;
                        maxLineY = inFrontY;

                        currentLineLength = 0;
                        inFrontX = NOT_AVAILABLE;
                        inFrontY = NOT_AVAILABLE;
                        afterEndX = NOT_AVAILABLE;
                        afterEndY = NOT_AVAILABLE;
                    }
                }

                continue;
            }
        } // i

        // --------- put the sign on board
        if ((maxLineX != NOT_AVAILABLE) and (maxLineY != NOT_AVAILABLE))
        {
            gameBoard[maxLineX][maxLineY] = AISign;
            cout << "Smart AI X: " << maxLineX << "\nSmart AI Y: " << maxLineY << "\n" << endl;
        }
        else
            GetRandomAIInput();
    } // else
}

// Check if current player has won the game
bool CheckGameState()
{
    bool result = true;

    // Check for win state in rows
    for(int y = 0; y < BOARD_SIZE; y++)
    {
        result = true;

        for(int x = 0; x < BOARD_SIZE; x++)
        {
            if(gameBoard[x][y] != currentPlayerSign)
            {
                result = false;
                break;
            }
        }
        if(result) 
            return true;
    }
    
    // Check for win state in columns
    for(int x = 0; x < BOARD_SIZE; x++)
    {
        result = true;

        for(int y = 0; y < BOARD_SIZE; y++)
        {
            if(gameBoard[x][y] != currentPlayerSign)
            {
                result = false;
                break;
            }
        }
        if(result) 
            return true;
    }

    // Check for diagonals
    result = true;

    // It's either \ diagonal...
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if(gameBoard[i][i] != currentPlayerSign)
            {
                result = false;
            }
    }
    if(result)
        return true;

    // ...or / diagonal
    result = true;
    
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        if(gameBoard[i][BOARD_SIZE - 1 - i] != currentPlayerSign)
            {
                result = false;
            }
    }
    if(result)
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
    // TODO
}
/* 04. Card Game.cpp
*
 * Unreal Engine Game Developer Course | Laba.IT
 *
 * Home Assignment No. 4:
 * - implement a card game
 * 
 * Code written by Hubert Pitura (hpitura@gmail.com)
 */

#include <iostream>
#include <vector>

using namespace std;

enum class CardColor
{
    red = 0, green, blue, yellow, wild
};

void Print(const CardColor color)
{
    switch (color)
    {
        case CardColor::red:
            cout << "Red";
            break;
        case CardColor::green:
            cout << "Green";
            break;
        case CardColor::blue:
            cout << "Blue";
            break;
        case CardColor::yellow:
            cout << "Yellow";
            break;
        case CardColor::wild:
            cout << "Wild Card";
            break;
        default:
            cout << "None";        
    }    
}

ostream& operator<<(ostream& os, const CardColor& color)
{
    switch (color)
    {
    case CardColor::red:
        os << "Red";
        break;
    case CardColor::green:
        os << "Green";
        break;
    case CardColor::blue:
        os << "Blue";
        break;
    case CardColor::yellow:
        os << "Yellow";
        break;
    case CardColor::wild:
        os << "Wild Card";
        break;
    default:
        os << "None";        
    }
    
    return os;
}

enum class CardType
{
    zero = 0, one, two, three, four, five, six, seven, eight, nine, skip, draw2, draw4, newColor, shuffleHands
};

void Print(const CardType type)
{
    switch (type)
    {
        case CardType::zero:
            cout << "0";
            break;
        case CardType::one:
            cout << "1";
            break;
        case CardType::two:
            cout << "2";
            break;
        case CardType::three:
            cout << "3";
            break;
        case CardType::four:
            cout << "4";
            break;
        case CardType::five:
            cout << "5";
            break;
        case CardType::six:
            cout << "6";
            break;
        case CardType::seven:
            cout << "7";
            break;
        case CardType::eight:
            cout << "8";
            break;
        case CardType::nine:
            cout << "9";
            break;
        case CardType::skip:
            cout << "Skip Round";
            break;
        case CardType::draw2:
            cout << "Draw 2";
            break;
        case CardType::draw4:
            cout << "Draw 4";
            break;
        case CardType::newColor:
            cout << "New Color";
            break;
        case CardType::shuffleHands:
            cout << "Shuffle Hands";
            break;
        default:
            cout << "None";
    }
}

ostream& operator<<(ostream& os, const CardType& type)
{
    switch (type)
    {
        case CardType::zero:
            os << "0";
            break;
        case CardType::one:
            os << "1";
            break;
        case CardType::two:
            os << "2";
            break;
        case CardType::three:
            os << "3";
            break;
        case CardType::four:
            os << "4";
            break;
        case CardType::five:
            os << "5";
            break;
        case CardType::six:
            os << "6";
            break;
        case CardType::seven:
            os << "7";
            break;
        case CardType::eight:
            os << "8";
            break;
        case CardType::nine:
            os << "9";
            break;
        case CardType::skip:
            os << "Skip Round";
            break;
        case CardType::draw2:
            os << "Draw 2";
            break;
        case CardType::draw4:
            os << "Draw 4";
            break;
        case CardType::newColor:
            os << "New Color";
            break;
        case CardType::shuffleHands:
            os << "Shuffle Hands";
            break;
        default:
            os << "None";
    }
    
    return os;
}

class Card
{
public:
    Card() = default;

    Card(const CardColor cardColor, const CardType cardType) : color_(cardColor), type_(cardType) {}

    Card(const Card& card) : color_(card.color_), type_(card.type_) {}

    CardColor GetColor() const
    {
        return color_;
    }

    void SetColor(const CardColor color)
    {
        this->color_ = color;
    }

    CardType GetType() const
    {
        return type_;
    }

    void SetType(const CardType type)
    {
        this->type_ = type;
    }

    friend ostream& operator<<(ostream& os, const Card& card);

private:
    CardColor color_;
    CardType type_;
};

ostream& operator<<(ostream& os, const Card& card)
{
    os << card.color_ << "|" << card.type_;
    
    return os;
}

class Deck
{
public:
    Deck() = default;

    Deck(const size_t noOfCards)
    {
        cards_.reserve(noOfCards);
    }

    void AppendCard(Card card)
    {
        cards_.emplace_back(card);
    }

    // Not all control paths in this method return value,
    // but in the code we always check first if deck's empty before calling it.
    Card DrawCard()
    {
        if (!cards_.empty())
        {
            Card card = cards_.back();
            cards_.pop_back();
            return card;
        }
        else
        {
            return {};
        }
    }

    // Not all control paths return a value
    Card GetCardAtIndex(const size_t index)
    {
        if (index < cards_.size())
            return cards_[index];    
    }
    
    void RemoveCardAtIndex(const size_t index)
    {
        cards_.erase(cards_.begin() + index);
    }

    bool IsEmpty() const
    {
        return cards_.empty();
    }
    
    void Print() const
    {
        /*for (const auto& card : cards_)
            cout << card << endl;*/
        for(size_t i = 0; i < cards_.size(); i++)
        {
            // just a bit of formatting, so everything's aligned
            if(i < 9 and cards_.size() >= 10)
                cout << " ";
            
            cout << i + 1 << ": " << cards_[i] << "\n";
        }
    }

    void PrintTopCard() const
    {
        cout << cards_.back() << endl;
    }
    
    size_t GetDeckSize() const
    {
        return cards_.size();
    }

    Card GetTopCard() const
    {
        return cards_.back();
    }

    Card GetCardAt(size_t position) const
    {
        return cards_.at(position);
    }

    void Shuffle()
    {
        size_t j { 0 }, deckSize { cards_.size() };
            
        srand(time(nullptr));

        for (size_t i = 0; i < deckSize; ++i)
        {
            j = rand() % deckSize;
            swap(cards_[i], cards_[j]);
        }
    }

protected:
    vector<Card> cards_;
};

class UnoDeck : Deck
{
public:
    UnoDeck()
    {        
        // Number of cards in game:
        // 2 cards of each type (0, 1, ..., draw4) for each color = 2 * 13 * 4 = 104
        // 4 new color wild cards + 2 shuffle hands wild cards = 6
        // total: 110 cards in game
        cards_.reserve(110);
        
        // Create color cards...
        for(short color = 0; color <= static_cast<short>(CardColor::yellow); ++color)
            for (short type = 0; type <= static_cast<short>(CardType::draw4); ++type)
            {
                cards_.emplace_back(static_cast<CardColor>(color),static_cast<CardType>(type));
                cards_.emplace_back(static_cast<CardColor>(color),static_cast<CardType>(type));
            }

        //...add to those four new color wild cards...
        for(short i = 0; i < 4; ++i)
            cards_.emplace_back(CardColor::wild, CardType::newColor);

        //...and two shuffle hands wild cards.
        for(short i = 0; i < 2; ++i)
            cards_.emplace_back(CardColor::wild, CardType::shuffleHands);
    }

    using Deck::AppendCard, Deck::DrawCard, Deck::IsEmpty, Deck::GetDeckSize, Deck::Print, Deck::Shuffle;
};

class UnoCardGame
{
public:
    // Create a hand for each player and initialize a game
    // Default game is for two players
    UnoCardGame()
    {       
        for(size_t i = 0; i < 2; ++i)
            hands_.emplace_back();

        noOfPlayers_ = 2;
        
        InitializeGame();
    }

    // Create a hand for each player and initialize a game
    UnoCardGame(size_t noOfPlayers)
    {
        // Game is for 10 players maximum
        if (noOfPlayers > 10)
            noOfPlayers = 10;
        
        for(size_t i = 0; i < noOfPlayers; ++i)
            hands_.emplace_back();

        noOfPlayers_ = noOfPlayers;
        
        InitializeGame();
    }

    // For logging purposes
    void PrintHand(size_t player) const
    {
        cout <<"Hand:\n";
        hands_[player].Print();
    }
    
    // For logging purposes
    void PrintDecks() const
    {
        cout << "Printing Decks\n"
                "Draw Pile:\n";
        drawPile_.Print();
        cout << "\nDiscard Pile:\n";
        discardPile_.Print();
        cout << "\nHands:\n";
        for(size_t i = 0; i < hands_.size(); ++i)
        {
            cout <<"Hand #" << i + 1 << ":\n";
            hands_[i].Print();
        }
    }

    void PrintTable() const
    {
        cout << "\nTABLE:"
                << "\nDraw Pile: " << drawPile_.GetDeckSize() << " card(s)"
                << " | Discard Pile: " << discardPile_.GetDeckSize() << " card(s)"
                << " | Top Card: ";
        discardPile_.PrintTopCard();

        for(size_t i = 0; i < hands_.size(); ++i)
        {
            cout << "Hand #" << i + 1 << ": " << hands_[i].GetDeckSize() << " card(s)";

            if(i != hands_.size() - 1)
                cout << " | ";
        }       
    }
    
    /*bool IsUno(size_t player) const
    {
        if(hands_[player].GetDeckSize() == 1)
            return true;
        else
            return false;
    }*/

    void PlayerTurn(size_t player)
    {
        CardType topCardType = discardPile_.GetTopCard().GetType();
        CardColor topCardColor = (colorOverride_) ? overridenColor_ : discardPile_.GetTopCard().GetColor();
        
        // handle special cards first!
        // Skip Round card
        if(topCardType == CardType::skip and skipRound_)
        {
            skipRound_ = false;
            return;
        }
        
        // Draw 2 card
        if(topCardType == CardType::draw2 and drawCards_)
        {
            for(size_t i = 0; i < 2; ++i)
            {
                if(drawPile_.IsEmpty())
                    Reshuffle();
                
                hands_[player].AppendCard(drawPile_.DrawCard());
            }
            
            cout << "\nPlayer " << player + 1 << ": drew two cards, skipping turn!\n";
            drawCards_ = false;
            return;
        }

        if(topCardType == CardType::draw4 and drawCards_)
        {
            for(size_t i = 0; i < 4; ++i)
            {
                if(drawPile_.IsEmpty())
                    Reshuffle();
                
                hands_[player].AppendCard(drawPile_.DrawCard());
            }
            cout << "\nPlayer " << player + 1 << ": drew four cards, skipping turn!\n";
            drawCards_ = false;
            return;
        }

        if(topCardType == CardType::newColor)
        {
            
        }

        if(topCardType == CardType::shuffleHands)
        {
            
        }
        
        // Look for and store indexes of cards in hand...
        // ...that can be played based on discard pile's top card
        // (either same color or same number)
        vector<size_t> viableCardsToPlay;
        Card currentCard;
        
        for(size_t i = 0; i < hands_[player].GetDeckSize(); ++i)
        {
            currentCard = hands_[player].GetCardAt(i);

            // either color or type has to match, or we can play a wild card
            if(currentCard.GetColor() == topCardColor or currentCard.GetType() == topCardType or currentCard.GetColor() == CardColor::wild)
                viableCardsToPlay.push_back(i);
        }

        /*for(auto cardIndex : viableCardsToPlay)
            cout << cardIndex << " ";
        cout << endl;*/

        // We found card(s) that can be played
        if(!viableCardsToPlay.empty())
        {
            // pick a card to play
            cout << "\nPlayer " << player + 1 << ": Viable cards that can be played are:\n";
            for(size_t i = 0; i < viableCardsToPlay.size(); ++i)
            {
                // just a bit of formatting, so everything's aligned
                if(i < 9 and viableCardsToPlay.size() >= 10)
                    cout << " ";
                
                cout << i + 1 << ": " << hands_[player].GetCardAt(viableCardsToPlay[i]) << "\n";
            }

            size_t index;
            bool inputOK = false;
            
            while(!inputOK)
            {
                cout << "Please select an option (1 - " << viableCardsToPlay.size() << "): ";
                cin >> index;
                if(index >= 1 and index <= viableCardsToPlay.size())
                    inputOK = true;
            }

            // we need to decrement index by 1
            index--;            
            
            // append a card from player's hand to discard pile...
            discardPile_.AppendCard(hands_[player].GetCardAt(viableCardsToPlay[index]));
            // ... and remove it from player's hand
            hands_[player].RemoveCardAtIndex(viableCardsToPlay[index]);

            if(colorOverride_) colorOverride_ = false;
            // Handle special cards behavior
            // Skip Turn action card
            if(discardPile_.GetTopCard().GetType() == CardType::skip)
            {
                skipRound_ = true;
            }

            // Draw Cards action card
            if(discardPile_.GetTopCard().GetType() == CardType::draw2 or
                discardPile_.GetTopCard().GetType() == CardType::draw4)
            {
                drawCards_ = true;
            }

            // New Color wild card
            if(discardPile_.GetTopCard().GetType() == CardType::newColor)
            {
                cout << "Please select new color:\n"
                        "1. Red\n"
                        "2. Green\n"
                        "3. Blue\n"
                        "4. Yellow\n";
            
                short color;
                inputOK = false;
            
                while(!inputOK)
                {
                    cout << "Please select an option (1 - 4): ";
                    cin >> color;
                    if(color >= 1 and color <= 4)
                        inputOK = true;
                }

                color--;
                overridenColor_ = static_cast<CardColor>(color);
                colorOverride_ = true;
            }

            // Shuffle Hands wild card
            if(discardPile_.GetTopCard().GetType() == CardType::shuffleHands)
            {
                ShuffleHands(player);
                cout << "Please select new color:\n"
                        "1. Red\n"
                        "2. Green\n"
                        "3. Blue\n"
                        "4. Yellow\n";
            
                short color;
                inputOK = false;
            
                while(!inputOK)
                {
                    cout << "Please select an option (1 - 4): ";
                    cin >> color;
                    if(color >= 1 and color <= 4)
                        inputOK = true;
                }

                color--;
                overridenColor_ = static_cast<CardColor>(color);
                colorOverride_ = true;
            }
        }
        else
        {
            cout << "\nPlayer " << player + 1 << ": nothing fit, I drew a card!\n";

            if(drawPile_.IsEmpty())
                Reshuffle();
            
            hands_[player].AppendCard(drawPile_.DrawCard());
        }

        /*cout << "Discard Pile:\n";
        discardPile_.Print();
        cout << "Player #" << player + 1 << ":\n";
        hands_[player].Print();*/

        // Scream UNO!
        if(hands_[player].GetDeckSize() == 1)
            cout << "\nPLAYER " << player + 1 << " screams UNO!!!" << endl; 
    }

    void AITurn(size_t player)
    {        
        CardType topCardType = discardPile_.GetTopCard().GetType();
        CardColor topCardColor = (colorOverride_) ? overridenColor_ : discardPile_.GetTopCard().GetColor();
        
        // handle special cards first!
        // Skip Round card
        if(topCardType == CardType::skip and skipRound_)
        {
            skipRound_ = false;
            return;
        }
        
        // Draw 2 card
        if(topCardType == CardType::draw2 and drawCards_)
        {
            for(size_t i = 0; i < 2; ++i)
            {
                if(drawPile_.IsEmpty())
                    Reshuffle();
                
                hands_[player].AppendCard(drawPile_.DrawCard());
            }
            
            cout << "\nPlayer " << player + 1 << ": drew two cards, skipping turn!\n";
            drawCards_ = false;
            return;
        }

        if(topCardType == CardType::draw4 and drawCards_)
        {
            for(size_t i = 0; i < 4; ++i)
            {
                if(drawPile_.IsEmpty())
                    Reshuffle();
                
                hands_[player].AppendCard(drawPile_.DrawCard());
            }
            cout << "\nPlayer " << player + 1 << ": drew four cards, skipping turn!\n";
            drawCards_ = false;
            return;
        }

        if(topCardType == CardType::newColor)
        {
            
        }

        if(topCardType == CardType::shuffleHands)
        {
            
        }
        
        // Look for and store indexes of cards in hand...
        // ...that can be played based on discard pile's top card
        // (either same color or same number)
        vector<size_t> viableCardsToPlay;
        Card currentCard;
        
        for(size_t i = 0; i < hands_[player].GetDeckSize(); ++i)
        {
            currentCard = hands_[player].GetCardAt(i);

            // either color or type has to match, or we can play a wild card
            if(currentCard.GetColor() == topCardColor or currentCard.GetType() == topCardType or currentCard.GetColor() == CardColor::wild)
                viableCardsToPlay.push_back(i);
        }

        /*for(auto cardIndex : viableCardsToPlay)
            cout << cardIndex << " ";
        cout << endl;*/

        // We found card(s) that can be played
        if(!viableCardsToPlay.empty())
        {
            // pick a random index
            srand(time(nullptr));
            size_t index = rand() % viableCardsToPlay.size();
            // append a card from player's hand to discard pile...
            discardPile_.AppendCard(hands_[player].GetCardAt(viableCardsToPlay[index]));
            // ... and remove it from player's hand
            hands_[player].RemoveCardAtIndex(viableCardsToPlay[index]);

            cout << "\nPlayer " << player + 1 << " played: " << discardPile_.GetTopCard() << endl;

            if(colorOverride_) colorOverride_ = false;
            
            // Handle special cards behavior
            // Skip Turn action card
            if(discardPile_.GetTopCard().GetType() == CardType::skip)
            {
                skipRound_ = true;
            }
            // Draw Cards action card
            if(discardPile_.GetTopCard().GetType() == CardType::draw2 or
                discardPile_.GetTopCard().GetType() == CardType::draw4)
            {
                drawCards_ = true;
            }
            // New Color wild card
            //if(hands_[player].GetCardAt(viableCardsToPlay[index]).GetType() == CardType::newColor)
            if(discardPile_.GetTopCard().GetType() == CardType::newColor)
            {
                // modulo 4 because we have four colors in the game
                overridenColor_ = static_cast<CardColor>(rand() % 4);
                colorOverride_ = true;

                cout << "\nPlayer " << player + 1 << " have chosen new color: ";
                Print(overridenColor_);
                cout << endl;
            }

            // Shuffle Hands wild card
            //if(hands_[player].GetCardAt(viableCardsToPlay[index]).GetType() == CardType::shuffleHands)
            if(discardPile_.GetTopCard().GetType() == CardType::shuffleHands)
            {
                ShuffleHands(player);
                // modulo 4 because we have four colors in the game
                overridenColor_ = static_cast<CardColor>(rand() % 4);
                colorOverride_ = true;
            }
        }
        else
        {
            cout << "\nPlayer " << player + 1 << ": nothing fit, I drew a card!\n";

            if(drawPile_.IsEmpty())
                Reshuffle();
            
            hands_[player].AppendCard(drawPile_.DrawCard());
        }

        /*cout << "Discard Pile:\n";
        discardPile_.Print();
        cout << "Player #" << player + 1 << ":\n";
        hands_[player].Print();*/

        // Scream UNO!
        if(hands_[player].GetDeckSize() == 1)
            cout << "\nPLAYER " << player + 1 << " screams UNO!!!" << endl;        
    }

    bool HasPlayerWon(size_t player) const
    {
        if(hands_[player].IsEmpty())
            return true;
        else
            return false;
    }

    bool SkipRound()
    {
        return skipRound_;
    }

private:
    UnoDeck drawPile_;
    Deck discardPile_;
    vector<Deck> hands_;
    size_t noOfPlayers_;
    bool skipRound_;
    bool drawCards_;
    CardColor overridenColor_;
    bool colorOverride_;

    void InitializeGame()
    {
        drawPile_ = UnoDeck();
        discardPile_ = Deck();
        skipRound_ = false;
        drawCards_ = false;
        colorOverride_ = false;

        drawPile_.Shuffle();

        // Deal 7 cards to each player
        for(size_t i = 0; i < 7; ++i)
            for(size_t player = 0; player < hands_.size(); ++player)
                hands_[player].AppendCard(drawPile_.DrawCard());

        // Prepare discard pile
        // When game starts, card on top has to be != action or wild card
        bool cardOK = false;
        Card card = drawPile_.DrawCard();
        
        while(!cardOK)
        {
            discardPile_.AppendCard(card);

            // In CardType enum all action cards are listed after CardType::nine
            if(card.GetColor() == CardColor::wild or
                card.GetType() > CardType::nine)
                card = drawPile_.DrawCard();
            else
                cardOK = true;
        }
        
        //PrintDecks();
    }

    // Shuffle cards in all player hands and re-deal them
    void ShuffleHands(size_t player)
    {
        Deck tempDeck;
        
        for(size_t p = 0; p < noOfPlayers_; ++p)
        {
            size_t deckSize = hands_[p].GetDeckSize();
            
            for(size_t c = 0; c < deckSize; ++c)
                tempDeck.AppendCard(hands_[p].DrawCard());
        }

        size_t deckSize = tempDeck.GetDeckSize();
        
        for(size_t c = 0; c < deckSize; ++c)
        {
            // we start dealing cards from the next player until they're gone
            hands_[(c + player + 1) % noOfPlayers_].AppendCard(tempDeck.DrawCard());
        }
        
    }

    void Reshuffle()
    {
        Card card = discardPile_.DrawCard();
        
        discardPile_.Shuffle();
        
        size_t deckSize = discardPile_.GetDeckSize();
        
        for(size_t c = 0; c < deckSize; ++c)
            drawPile_.AppendCard(discardPile_.DrawCard());

        discardPile_.AppendCard(card);
        
        
    }
};

static constexpr size_t NoOfPlayers = 2;

enum class CurrentPlayer { Player = 0, AI = 1 };

/*const char* to_string(CurrentPlayer player)
{
    switch (player)
    {
    case CurrentPlayer::Player: return "Player";
    case CurrentPlayer::AI: return "AI";
    default: return "unknown";
    }
}*/

/* MAIN PROGRAM CODE */
int main()
{
    // Welcome message
    cout << "<<< UNO Card Game >>>\n"
            "This game follows rules listed here: https://www.unorules.org\n" << endl;

    // Setup game
    UnoCardGame uno(NoOfPlayers);

    // Who starts?
    srand(time(nullptr));
    CurrentPlayer currentPlayer = static_cast<CurrentPlayer>(rand() % NoOfPlayers);
    
    cout << "Player 1: You!\n"
            "Player 2: AI\n";

    cout << "Player " << static_cast<short>(currentPlayer) + 1 << " starts the game.\n";
    
    while(true)
    {
        uno.PrintTable();

        // Two players game
        if(currentPlayer == CurrentPlayer::Player)
        {
            cout << "\n\n<< PLAYER 1 TURN >>\n";
            uno.PrintHand(static_cast<size_t>(currentPlayer));
            uno.PlayerTurn(static_cast<size_t>(currentPlayer));
        }
        else
        {          
            cout << "\n\n<< PLAYER 2 (AI) TURN >>";
            uno.AITurn(static_cast<size_t>(currentPlayer));
        }

        if(uno.HasPlayerWon(static_cast<size_t>(currentPlayer)))
        {
            cout << "\nPlayer " << static_cast<short>(currentPlayer) + 1 << " won!\n";
            break;
        }
        
        // Switch players
        (currentPlayer == CurrentPlayer::Player) ?
            currentPlayer = CurrentPlayer::AI : currentPlayer = CurrentPlayer::Player;        
    }

    return 0;
}

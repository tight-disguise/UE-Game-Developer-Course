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

enum class CardColor : uint8_t
{
    red, green, blue, yellow, wild
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

enum class CardType : uint8_t
{
    zero, one, two, three, four, five, six, seven, eight, nine, skip, draw2, draw4, newColor, shuffleHands
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

    CardColor getColor() const
    {
        return color_;
    }

    void setColor(const CardColor color)
    {
        this->color_ = color;
    }

    CardType getType() const
    {
        return type_;
    }

    void setType(const CardType type)
    {
        this->type_ = type;
    }

    friend ostream& operator<<(ostream& os, const Card& card);

private:
    CardColor color_ { CardColor::wild };
    CardType type_ { CardType::newColor };
};

ostream& operator<<(ostream& os, const Card& card)
{
    os << card.color_ << "|" << card.type_;
    
    return os;
}

class Deck
{
public:
    Deck()
    {
        cards_.reserve(110);
        
        // Create color cards...
        for(short color = 0; color <= static_cast<short>(CardColor::yellow); ++color)
            for (short type = 0; type <= static_cast<short>(CardType::draw4); ++type)
            {
                cards_.emplace_back(static_cast<CardColor>(color),static_cast<CardType>(type));
                cards_.emplace_back(static_cast<CardColor>(color),static_cast<CardType>(type));
            }

        //...add to those four new color wilds cards...
        for(short i = 0; i < 4; ++i)
            cards_.emplace_back(CardColor::wild, CardType::newColor);

        //...and two shuffle hands wild cards.
        for(short i = 0; i < 2; ++i)
            cards_.emplace_back(CardColor::wild, CardType::shuffleHands);
    }

    void Print() const
    {
        for (const auto& card : cards_)
            cout << card << endl;
    }

private:
    // Number of cards in game:
    // 2 cards of each type (0, 1, ..., draw4) for each color = 2 * 13 * 4 = 104
    // 4 new color wild cards + 2 shuffle hands wild cards = 6
    // total: 110 cards in game
    vector<Card> cards_;
};

int main()
{
    Deck deckOfCards;

    deckOfCards.Print();    
    
    return 0;
}

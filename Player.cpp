
#include "Player.h"

    Player::Player()
    {
        first_name = nullptr;
        second_name = nullptr;
        age = 0;
        wins = 0;
        CW = 0.0;
        CP = 0;
        current_cards = nullptr;
        cc_buffer = 0;
        ace_buffer = 0;
    }

    void Player::setFirstName(const char* name1)
    {
        first_name = new char[strlen(name1) + 1];
        strcpy_s(first_name, strlen(name1) + 1, name1);
    }

    char* Player::getFirstName() const
    {
        return first_name;
    }

    short int Player::getAceB()
    {
        return ace_buffer;
    }

    void Player::incrementAceB()
    {
        ace_buffer++;
    }

    void Player::decrementAceB()
    {
        ace_buffer--;
    }

    void Player::setSecondName(const char* name2)
    {
        second_name = new char[strlen(name2) + 1];
        strcpy_s(second_name, strlen(name2) + 1, name2);
    }

    char* Player::setSecondName() const
    {
        return second_name;
    }

    void Player::setCP(int cp)
    {
        CP += cp;
    }

    int Player::getCP() const
    {
        return CP;
    }

    void Player::setWins(int w)
    {
        wins = w;
    }

    int Player::getWins() const
    {
        return wins;
    }

    size_t Player::getCCB() const
    {
        return cc_buffer;
    }

    void Player::printPlayer() const
    {
        cout << getFirstName() << " " << setSecondName() << " "
            << getWins() << " " << getCP() << endl;
    }

    void Player::printCardBuffer() const
    {
        cout << "-----------------------------------\n";
        cout << getFirstName() << " " << setSecondName() << "'s cards\n";
        for (size_t i = 0; i < cc_buffer; i++)
        {
            current_cards[i].print();
        }
        cout << "Current points: " << getCP() << endl;
        cout << "-----------------------------------\n";
    }

    void Player::addCard(Card card)
    {
        Card* buffer_cards = new Card[cc_buffer + 1];
        for (size_t i = 0; i < cc_buffer; i++)
        {
            buffer_cards[i] = current_cards[i];
        }
        delete[] current_cards;
        buffer_cards[cc_buffer] = card;
        setCP(buffer_cards[cc_buffer].getValue());
        if (compare(buffer_cards[cc_buffer].getFace(), "Ace"))
            incrementAceB();
        current_cards = buffer_cards;
        cc_buffer++;
    }

#pragma once
#include "Deck.h"
#include "Card.h"

class Player
{
    char* first_name;
    char* second_name;
    short age;
    unsigned wins;
    double CW;   //Coeficient of wins
    unsigned CP; //Current points
    Card* current_cards; //Buffer of cards
    size_t cc_buffer; //Number of cards in a player's hand
    short int ace_buffer; //Number of aces in player's hand
public:

    Player();

    void setFirstName(const char* name1);

    char* getFirstName() const;

    short int getAceB();

    void incrementAceB();

    void decrementAceB();

    void setSecondName(const char* name2);

    char* setSecondName() const;

    void setCP(int cp);

    int getCP() const;

    void setWins(int w);

    int getWins() const;

    size_t getCCB() const;

    void printPlayer() const;

    void printCardBuffer() const;

    void addCard(Card card);

};

#pragma once
#include "Card.h"
#include<iostream>

class Deck
{
    Card* cards;
    size_t cardsInDeck;
    size_t notDrawnCards;
    char deck_series[10];
public:
    Deck();

    Deck(size_t num_cards, const char* d_series);

    void initDeck(size_t n, const char* deck_ser_num);

    void shuffles(size_t cardsInDeck);

    ~Deck();

    void setDeckSeries(const char* deckser);

    Card draw();

    void print() const;

    Card& getCard(size_t pos);

    void swap(size_t a, size_t b);

    int suit_count(const char* suit);

    int rank_count(const char* face);

};

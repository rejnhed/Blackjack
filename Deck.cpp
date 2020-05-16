#include "Deck.h"


    Deck::Deck()
    {
        cardsInDeck = 52;
        strcpy_s(deck_series, 8, "Default");
        initDeck(52, deck_series);
        shuffles(52);
        notDrawnCards = 0;
        //unsigned seed = rand();
        //shuffle(cards, cards + 52, default_random_engine(seed));
    }

    Deck::Deck(size_t num_cards, const char* d_series)
    {
        size_t memory_cards = 0;
        while (num_cards > memory_cards)
            memory_cards += 52;
        cardsInDeck = memory_cards;
        strcpy_s(deck_series, strlen(d_series) + 1, d_series);
        if (deck_series[0] == '\0')
            strcpy_s(deck_series, 7, "Custom");
        initDeck(memory_cards, deck_series);
        shuffles(memory_cards);
        cardsInDeck = num_cards;
        Card* cards_temp = new Card[num_cards];
        for (size_t i = 0; i < num_cards; i++)
        {
            cards_temp[i] = cards[i];
        }
        delete[] cards;
        cards = cards_temp;
    }

    void Deck::initDeck(size_t n, const char* deck_ser_num)
    {
        size_t memorycards = 0;
        while (n > memorycards)
            memorycards += 52;
        cards = new Card[memorycards];
        char numberstring[15];
        for (size_t k = 0; k < ceil(n / 52); k++) {
            for (size_t i = 0; i < 4; i++) {
                cards[0 + i * 13 + k * 52].setFace("Ace");
                cards[0 + i * 13 + k * 52].setValue(11);
                numberstring[1] = '\0';
                for (size_t j = 1; j < 9; j++) {
                    numberstring[0] = (j + 1) + '0';
                    cards[j + i * 13 + k * 52].setFace(numberstring);
                    cards[j + i * 13 + k * 52].setValue(j + 1);
                }
                strcpy_s(numberstring, 3, "10");
                cards[9 + i * 13 + k * 52].setFace(numberstring);
                cards[9 + i * 13 + k * 52].setValue(10);
                cards[10 + i * 13 + k * 52].setFace("Jack");
                cards[11 + i * 13 + k * 52].setFace("Queen");
                cards[12 + i * 13 + k * 52].setFace("King");
                cards[10 + i * 13 + k * 52].setValue(10);
                cards[11 + i * 13 + k * 52].setValue(10);
                cards[12 + i * 13 + k * 52].setValue(10);
            }
            for (size_t i = 0; i < 13; i++)
                cards[i + k * 52].setSuit("clubs");
            for (size_t i = 13; i < 26; i++)
                cards[i + k * 52].setSuit("diamonds");
            for (size_t i = 26; i < 39; i++)
                cards[i + k * 52].setSuit("hearts");
            for (size_t i = 39; i < 52; i++)
                cards[i + k * 52].setSuit("spades");
            for (size_t i = 0; i < 14; i++)
                numberstring[i] = '-';
            strcpy_s(numberstring, strlen(deck_ser_num) + 1, deck_ser_num);
            for (size_t i = 0; i < 52; i++)
            {
                numberstring[14] = '\0';
                numberstring[13] = (((i + k * 52) / 1) % 10) + '0';
                numberstring[12] = (((i + k * 52) / 10) % 10) + '0';
                numberstring[11] = (((i + k * 52) / 100) % 10) + '0';
                numberstring[10] = (((i + k * 52) / 1000) % 10) + '0';
                numberstring[strlen(deck_ser_num)] = '-';
                cards[i + k * 52].setSerial_number(numberstring);
            }
        }
    }

    void Deck::shuffles(size_t cardsInDeck)
    {
        size_t j = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            j = rand() % cardsInDeck;
            swap(i, j);
        }
    }

    Deck::~Deck() {
        delete[] cards;
    }

    void Deck::setDeckSeries(const char* deckser)
    {
        strcpy_s(deck_series, strlen(deckser) + 1, deckser);
    }

    Card Deck::draw()
    {
        for (size_t i = 0; i < cardsInDeck - 1; i++)
        {
            swap(i, i + 1);
        }
        cards[cardsInDeck - 1].setDrawn(true);
        return cards[cardsInDeck - 1];
    }

    void Deck::print() const
    {
        for (size_t i = 0; i < cardsInDeck; i++) {
            cards[i].print();
        }
    }

    Card& Deck::getCard(size_t pos)
    {
        return cards[pos];
    }

    void Deck::swap(size_t a, size_t b)
    {
        if (0 <= a && a < cardsInDeck && 0 <= b && b < cardsInDeck)
        {
            Card temp = cards[a];
            cards[a] = cards[b];
            cards[b] = temp;
        }
        else {
            cout << "Invalid arguments! a= " << a << " b= " << b << endl;
        }
    }

    int Deck::suit_count(const char* suit)
    {
        int suitCounter = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            if (compare(cards[i].getSuit(), suit))
                suitCounter++;
        }
        return suitCounter;
    }

    int Deck::rank_count(const char* face)
    {
        int suitCounter = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            if (!cards[i].getDrawn() && compare(cards[i].getFace(), face))
                suitCounter++;
        }
        return suitCounter;
    }

// Blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <stdio.h>
//#include <string.h>
//#include <cassert>
//#include <sstream>
//#include <cstdlib>
#include <ctime>
//#include <time.h>
//#include <algorithm>
//#include <chrono>
//#include <random>

using namespace std;

bool compare(const char* str1, const char* str2)
{
    size_t lenght;
    if (strlen(str1) > strlen(str2))
        lenght = strlen(str1);
    else lenght = strlen(str2);
    for (size_t i = 0; i < lenght; i++)
    {
        if (str1[i] != str2[i])
            return false;
    }
    return true;
}

class Value
{
    int card_number[9] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    char card_face[4] = { 'J', 'Q', 'K', 'A' };
};
// int a    int* pointer = &a  *pointer = 4
// 0x43AB   0x53BC
// 4        0x43AB
//
class Card
{
    int value;
    char* face; //  { 'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K' }; // { 1, 2, ..., 13 } // { 0, 1, ...,12}
    char* suit; //  { "clubs", "diamonds", "hearts", "spades" };        // { 'C', 'D', 'H', 'S' }
    char serial_number[15];
    bool drawn;
public:
    Card()
    {
        value = 0;
        face = nullptr;
        suit = nullptr;
        strcpy(serial_number, "Default");
        drawn = false;
    }

    ~Card()
    {
        //delete[] face;
        //delete[] suit;
    }

    void setFace(const char* f)
    {
        face = new char[strlen(f) + 1];
        strcpy(this->face, f);
    }

    const char* getFace() const
    {
        return face;
    }

    void setSuit(const char* s)
    {
        suit = new char[strlen(s) + 1];
        strcpy(this->suit, s);
    }

    const char* getSuit() const
    {
        return suit;
    }

    void setSerial_number(const char* s)
    {
        strcpy(this->serial_number, s);
    }

    const char* getSerial_number() const
    {
        return serial_number;
    }

    void setValue(int v)
    {
        value = v;
    }

    int getValue() const
    {
        return value;
    }

    void setDrawn(bool d)
    {
        drawn = d;
    }

    bool getDrawn() const
    {
        return drawn;
    }

    void print() const
    {
        cout << face << " of " << suit << " Ser#: " << getSerial_number() << endl;
        //cout << getFace() << " of " << getSuit() << endl;
    }
    /*
    void operator= (Card other)
    {
        value = other.value;

        strcpy(face, other.face);
        strcpy(suit, other.suit);
        strcpy(serial_number,other.serial_number);
    }
    */
    Card& operator=(const Card& other) {
        if (this != &other)
        {
            copy(other);
        }
        return *this;
    }

    void copy(const Card& other)
    {
        this->value = other.value;
        face = new char[strlen(other.face) + 1];
        strcpy(face, other.face);
        suit = new char[strlen(other.suit) + 1];
        strcpy(suit, other.suit);
        //serial_number = new char[strlen(other.serial_number) + 1];
        strcpy(serial_number, other.serial_number);
        this->drawn = other.drawn;
    }

};

class Deck
{
    Card* cards;
    size_t cardsInDeck;
    size_t notDrawnCards;
    char deck_series[10];
public:
    Deck()
    {
        cardsInDeck = 52;
        strcpy(deck_series, "Default");
        initDeck(52, deck_series);
        shuffles(52);
        notDrawnCards = 0;
        //unsigned seed = rand();
        //shuffle(cards, cards + 52, default_random_engine(seed));
    }

    Deck(size_t num_cards, const char* d_series)
    {
        size_t memory_cards = 0;
        while (num_cards > memory_cards)
            memory_cards += 52;
        cardsInDeck = memory_cards;
        strcpy(deck_series, d_series);
        if (deck_series[0] == '\0')
            strcpy(deck_series, "Custom");
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

    void initDeck(size_t n, const char* deck_ser_num)
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
                strcpy(numberstring, "10");
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
            strcpy(numberstring, deck_ser_num);
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

    void shuffles(size_t cardsInDeck)
    {
        Card* temp = new Card[1];
        size_t j = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            j = rand() % cardsInDeck;
            swap(i, j);
        }
    }

    ~Deck() {
        delete[] cards;
    }

    void setDeckSeries(const char* deckser)
    {
        strcpy(deck_series, deckser);
    }

    Card draw()
    {
        for (size_t i = 0; i < cardsInDeck - 1; i++)
        {
            swap(i, i + 1);
        }
        /*cards[cardsInDeck - 1].print();
        cout << "draw_test1" << endl;
        cards[cardsInDeck - 1].setDrawn(true);
        Card card = cards[cardsInDeck - 1];
        cout << "draw_test2" << endl;
        card.print();
        cout << "draw_test3" << endl;
        //return card;*/
        return cards[cardsInDeck - 1];
    }

    void print() const
    {
        for (size_t i = 0; i < cardsInDeck; i++) {
            cards[i].print();
        }
    }

    Card getCard(size_t pos)
    {
        return cards[pos];
    }

    void swap(size_t a, size_t b)
    {
        if (0 <= a && a < cardsInDeck && 0 <= b && b < cardsInDeck)
        {
            Card temp = cards[a];
            cards[a] = cards[b];
            cards[b] = temp;
            /*if (a == cardsInDeck - 2) {
                cards[cardsInDeck - 2].print();
                cout << "gore" << endl;
                cards[cardsInDeck - 1].print();
                cout << "2gore" << endl;
            }*/
        }
        else {
            cout << "Invalid arguments! a= " << a << " b= " << b << endl;
        }
    }

    int suit_count(const char* suit)
    {
        int suitCounter = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            if (compare(cards[i].getSuit(), suit))
                suitCounter++;
        }
        return suitCounter;
    }

    int rank_count(const char* face)
    {
        int suitCounter = 0;
        for (size_t i = 0; i < cardsInDeck; i++)
        {
            if (!cards[i].getDrawn() && compare(cards[i].getFace(), face))
                suitCounter++;
        }
        return suitCounter;
    }

};

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

    Player()
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

    void setFirstName(const char* name1)
    {
        first_name = new char[strlen(name1) + 1];
        strcpy(first_name, name1);
    }

    char* getFirstName() const
    {
        return first_name;
    }

    short int getAceB()
    {
        return ace_buffer;
    }

    void incrementAceB()
    {
        ace_buffer++;
    }

    void decrementAceB()
    {
        ace_buffer--;
    }

    void setSecondName(const char* name2)
    {
        second_name = new char[strlen(name2) + 1];
        strcpy(second_name, name2);
    }

    char* setSecondName() const
    {
        return second_name;
    }

    void setCP(int cp)
    {
        CP += cp;
    }

    int getCP() const
    {
        return CP;
    }

    void setWins(int w)
    {
        wins = w;
    }

    int getWins() const
    {
        return wins;
    }

    size_t getCCB() const
    {
        return cc_buffer;
    }

    void printPlayer() const
    {
        cout << getFirstName() << " " << setSecondName() << " "
            << getWins() << " " << getCP() << endl;
    }

    void printCardBuffer() const
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

    void addCard(Card card)
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

    //ccbbccbb  ccbccb//ccbbccbb  ccbccb
};

void Game()
{
    size_t numcards;
    cout << "Enter number cards ";
    cin >> numcards;
    Deck deck(numcards, "pas");
    Player b1;
    while (true)
    {

    }
}

int main()
{
    Player player1, dealer;
    dealer.setFirstName("Mr");
    dealer.setSecondName("Dealer");
    char fname[20];
    char sname[20];
    cout << "Choose a player or enter a new player: ";
    cin >> fname;
    cin >> sname;
    player1.setFirstName(fname);
    player1.setSecondName(sname);
    size_t n;
    char symbol;
    char sernumb[10];
    sernumb[0] = '\0';
    cout << "Enter number of cards: ";
    cin >> n;
    cout << "Do you want to select a series?";
    cout << endl << "Yes/No (enter 'y' or 'n'): ";
    cin >> symbol;
    switch (symbol)
    {
    case 'y':
        cout << "Enter deck series name: ";
        cin >> sernumb;
        break;
    default:
        break;
    }
    srand(time(NULL));
    Deck deck(n, sernumb);
    Card curr_card;
    /* Just for admins :)
    deck.print();
    cout << "Number of clubs = " << deck.suit_count("clubs") << endl;
    cout << "Number of diamonds = " << deck.suit_count("diamonds") << endl;
    cout << "Number of hearts = " << deck.suit_count("hearts") << endl;
    cout << "Number of spades = " << deck.suit_count("spades") << endl;
    //*/
    cout << "Start!" << endl;
    //(deck.draw()).print();
    player1.addCard(deck.draw());
    cout << endl;
    //deck.print();
    player1.printCardBuffer();
    //player1.addCard(deck.draw());
    cout << endl;
    bool game_flag = true;
    while (game_flag)
    {
        double prob = 0;
        short int denom = 0;
        cout << "Hit/Stand/Probability" << endl;
        cout << "Enter h,s or p: ";
        cin >> symbol;
        switch (symbol)
        {
        case 'h':
            player1.addCard(deck.draw());
            if (player1.getCP() > 21)
            {
                if (player1.getAceB() > 0) 
                {
                    player1.decrementAceB();
                    player1.setCP(-10);
                }
                else {
                    game_flag = false;
                }
            }
            player1.printCardBuffer();
            break;
        case 's':
            game_flag = false;
            break;
        case 'p':  
            for (size_t i = player1.getCCB(); i < n; i++)
            {
                if (21 - player1.getCP() == (deck.getCard(i)).getValue())
                    prob++;
                if (!(deck.getCard(i)).getDrawn())
                    denom++;
            }
            cout << "-----------------------------------\n";
            cout << "Probability is: " << prob / denom << endl;
            cout << "-----------------------------------\n";
            break;
        default:
            cout << "Enter letter again!\n";
            break;
        }
    }

    if (player1.getCP() > 21)
    {
        cout << "Too drew too much!\n";
        cout << "You lose!";
        game_flag = false;
    } else {

        while (dealer.getCP() <= 17)
        {
            dealer.addCard(deck.draw());
            if (dealer.getCP() > 21)
                if (dealer.getAceB() > 0)
                {
                    dealer.decrementAceB();
                    dealer.setCP(-10);
                }
        }
        if (player1.getCP() >= dealer.getCP() || dealer.getCP() > 21) {
            player1.printCardBuffer();
            dealer.printCardBuffer();
            cout << "You win!" << endl;
            player1.setWins(1);
        }
        else {
            player1.printCardBuffer();
            dealer.printCardBuffer();
            cout << "You lose!" << endl;
        }
    }
    //cout << "\nThe deck was:\n\n";
    //deck.print();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
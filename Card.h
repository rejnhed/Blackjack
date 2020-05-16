#pragma once
#include <iostream>

using namespace std;

bool compare(const char* str1, const char* str2);

class Card
{
    int value;
    char* face; //  { 'A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K' }; // { 1, 2, ..., 13 } // { 0, 1, ...,12}
    char* suit; //  { "clubs", "diamonds", "hearts", "spades" };        // { 'C', 'D', 'H', 'S' }
    char serial_number[15];
    bool drawn;
public:
    Card();

    ~Card();

    void setFace(const char* f);

    const char* getFace() const;

    void setSuit(const char* s);

    const char* getSuit() const;

    void setSerial_number(const char* s);

    const char* getSerial_number() const;

    void setValue(int v);
    
    int getValue() const;

    void setDrawn(bool d);

    bool getDrawn() const;

    void print() const;

    Card& operator=(const Card& other);

    Card(const Card& other);

private:
    void copy(const Card& other);

    void erase();
};

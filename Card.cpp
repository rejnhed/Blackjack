#include "Card.h"


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



    Card::Card()
    {
        value = 0;
        face = nullptr;
        suit = nullptr;
        strcpy_s(serial_number, 8, "Default");
        drawn = false;
    }

    Card::~Card()
    {
        erase();
    }

    void Card::setFace(const char* f)
    {
        this->face = new char[strlen(f) + 1];
        strcpy_s(this->face, strlen(f) + 1, f);
    }

    const char* Card::getFace() const
    {
        return this->face;
    }

    void Card::setSuit(const char* s)
    {
        suit = new char[strlen(s) + 1];
        strcpy_s(this->suit, strlen(s) + 1, s);
    }

    const char* Card::getSuit() const
    {
        return suit;
    }

    void Card::setSerial_number(const char* s)
    {
        strcpy_s(this->serial_number, strlen(s) + 1, s);
    }

    const char* Card::getSerial_number() const
    {
        return serial_number;
    }

    void Card::setValue(int v)
    {
        value = v;
    }

    int Card::getValue() const
    {
        return value;
    }

    void Card::setDrawn(bool d)
    {
        drawn = d;
    }

    bool Card::getDrawn() const
    {
        return drawn;
    }

    void Card::print() const
    {
        cout << face << " of " << suit << " Ser#: " << getSerial_number() << endl;
    }

    Card& Card::operator=(const Card& other) {
        if (this != &other)
        {
            erase();
            copy(other);
        }
        return *this;
    }

    Card::Card(const Card& other) {
        this->copy(other);
    }

    void Card::copy(const Card& other)
    {
        this->value = other.value;
        face = new char[strlen(other.face) + 1];
        strcpy_s(face, strlen(other.face) + 1, other.face);
        suit = new char[strlen(other.suit) + 1];
        strcpy_s(suit, strlen(other.suit) + 1, other.suit);
        //serial_number = new char[strlen(other.serial_number) + 1];
        strcpy_s(serial_number, strlen(other.serial_number) + 1, other.serial_number);
        this->drawn = other.drawn;
    }

    void Card::erase() {
        delete[] this->face;
        delete[] this->suit;
    }

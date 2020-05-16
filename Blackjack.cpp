// Blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include <stdio.h>
//#include <string.h>
//#include <cassert>
//#include <sstream>
//#include <cstdlib>
#include <ctime>
#include "Player.h"
//#include <time.h>
//#include <algorithm>
//#include <chrono>
//#include <random>

using namespace std;

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
    //* Just for admins :)
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
    }
    else {

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
    cout << "\nThe deck was:\n\n";
    deck.print();
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
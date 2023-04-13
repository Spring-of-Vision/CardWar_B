#include "card.hpp"
#include <iostream>
using namespace std;

namespace ariel
{
    int number; //1: A, 2-10: 2-10, 11-13: J,Q,K
    int suit; // 1- heart, 2- clubs, 3- diamond, 4- spades

    //try writing the program without this constructor
    Card::Card()
    {
        number = 0;
        suit = 0;
    }

    Card::Card(int n, int shape)
    {
        number = n;
        suit = shape;
    }

    int Card::getNumber()
    {
        return number;
    }

    string Card::toString()
    {
        string letter = "";
        string shape = "";
        if(number == 1)
        {
            letter = "Ace";
        }
        else if(number == 11)
        {
            letter = "Prince";
        }
        else if(number == 12)
        {
            letter = "Queen";
        }
        else if(number == 13)
        {
            letter = "King";
        }
        else
        {
            letter = to_string(number);
        }

        if(suit == 1)
        {
            shape = "Hearts";
        }
        else if(suit == 2)
        {
            shape = "Clubs";
        }
        else if(suit == 3)
        {
            shape = "Diamonds";
        }
        else if(suit == 4)
        {
            shape = "Spades";
        }
        else
        {
            return "null card";
        }

        return letter + " of " + shape;
    }
}
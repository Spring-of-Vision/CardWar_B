#include "card.hpp"
#include <iostream>
using namespace std;

namespace ariel
{
    //empty card constructor
    Card::Card()
    {
        number = 0;
        suit = 0;
    }

    //Contructor with values
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

        //Print the card based on values of number and suit
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
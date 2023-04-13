#pragma once

#include <iostream>

#ifndef Cards_hpp
#define Cards_hpp

namespace ariel
{ 
    class Card
    {
        //fields
        int number; //1 = ace, 11= prince, 12= queen, 13= king
        int suit; // 1- heart, 2- clubs, 3- diamond, 4- spades

        public:
            //constructors
            Card();
            Card(int n, int shape);

            //methods
            int getNumber();
            std::string toString();
    };
}

#endif
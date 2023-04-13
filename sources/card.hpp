#pragma once

#include <iostream>

#ifndef Cards_hpp
#define Cards_hpp

namespace ariel
{ 
    class Card
    {
        char number;
        int suit; // 1- heart, 2- clubs, 3- diamond, 4- spades

        public:
            Card();
            Card(int n, int shape);
            int getNumber();
            std::string toString();
    };
}

#endif
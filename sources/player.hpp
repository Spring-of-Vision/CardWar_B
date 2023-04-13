#pragma once

#ifndef Player_hpp
#define Player_hpp

#include "card.hpp"
#include <iostream>
#include <stack>

namespace ariel
{
    class Player
    {
        //Fields
        std::string name;
        bool isPlaying;
        std::stack<Card> deck;
        int won;

        public:
            //Constructor
            Player(std::string str);

            //Methods
            int stacksize();
            Card draw();
            void addCard(Card&);
            void updateWin(int);
            void setPlaying(bool);
            int cardesTaken();
            bool getPlaying();
            std::string getName();
    };
}

#endif
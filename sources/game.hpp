#pragma once

#ifndef Game_hpp
#define Game_hpp
#include "player.hpp"

namespace ariel
{
    class Game
    {
        //Fields
        Player& one;
        Player& two;
        std::string log;
        int onesWins = 0;
        int twosWins = 0;
        int turns = 0;
        int draws = 0;

        public:

            //Constructor
            Game(Player &pl1, Player &pl2);
            
            //Methods
            bool playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();
    };
}

#endif
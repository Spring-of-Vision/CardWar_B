#include <stack>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "player.hpp"
#include "game.hpp"

#define DECK_SIZE 52

using namespace std;

namespace ariel
{

    Card gameDeck[DECK_SIZE];

    Game::Game(Player& pl1, Player& pl2) : one(pl1), two(pl2)
    {
        //Claim the players
        if(one.getPlaying() || two.getPlaying())
        {
            throw runtime_error("One or both players is already in a game!");
        }
        one.setPlaying(true);
        two.setPlaying(true);

        //Create the deck
        for(int i = 0; i < DECK_SIZE; i++)
        {
            Card x(i%13 + 1, i/13 +1);
            gameDeck[i] = x;
        }

        //Shuffle the deck a random number of times between 2 and 20
        int shuffles = rand() %10 + rand() %10 + 2;
        for(int k=0; k < shuffles; k++)
        {
            srand(time(NULL));
            //Shuffle the deck (Fisher-Yates)
            for(int i = 0; i < DECK_SIZE; i++)
            {
                int j = rand() % DECK_SIZE;
                Card x = gameDeck[i];
                gameDeck[i] = gameDeck[j];
                gameDeck[j] = x;
            }
        }

        //Distribute to the players
        for(int i=0; i < DECK_SIZE; i+=2)
        {
            //add a reference to the card instead of card itself?
            one.addCard(gameDeck[i]);
            two.addCard(gameDeck[i+1]);
        }

        log+= "Game created with players " + one.getName() + " and " + two.getName() + ".";
    }

    //Returns true if game ended, false otherwise
    bool Game::playTurn()
    {
        if(!one.getPlaying() || !two.getPlaying() || &one == &two)
        {
            if(&one == &two)
            {
                throw runtime_error("Only one player");
            }
            else
            {
                throw __throw_bad_function_call;
            }
        }

        //Each draws a card
        Card onesCard = one.draw();
        Card twosCard = two.draw();

        //Check that the stacks haven't depleted
        if(onesCard.getNumber() == 0 || twosCard.getNumber() == 0)
        {
            //Configure end-game
            log += "\n Game ended.";

            one.setPlaying(false);
            two.setPlaying(false);

            return true;
        }

        bool draw = true;
        int cardsWon = 2;
        turns++;

        log+= "\n";

        //Compare card number to see who wins or play a draw until someone wins or no more cards
        while(draw)
        {
            log += one.getName() + " played a " + onesCard.toString() + ". " + two.getName() + " played a " + twosCard.toString() + ". ";
            
            //If someone has an ace and the other doesn't have an ace or a 2, they win
            if(onesCard.getNumber() == 1)
            {
                if(twosCard.getNumber() != 1 && twosCard.getNumber() != 2)
                {
                    //Player one wins
                    onesWins++;
                    one.updateWin(cardsWon);
                    draw = false;
                    log += one.getName() + " wins.";
                    break;
                }
            }
            else if(twosCard.getNumber() == 1)
            {
                if(onesCard.getNumber() != 1 && onesCard.getNumber() != 2)
                {
                    //Player two wins
                    twosWins++;
                    two.updateWin(cardsWon);
                    draw = false;
                    log += two.getName() + " wins.";
                    break;
                }
            }

            //Player one wins
            if(onesCard.getNumber() > twosCard.getNumber())
            {
                onesWins++;
                one.updateWin(cardsWon);
                draw = false;
                log += one.getName() + " wins.";
            }
            //Player two wins
            else if(onesCard.getNumber() < twosCard.getNumber())
            {
                twosWins++;
                two.updateWin(cardsWon);
                draw = false;
                log += two.getName() + " wins.";
            }
            //A draw
            else
            {
                log += "Draw. ";
                draws++;

                //face down cards (not saved as they are not used)
                one.draw();
                two.draw();

                if(onesCard.getNumber() == 0 || twosCard.getNumber() == 0)
                {
                    //Configure end-game
                    log += "\n Game ended.";

                    one.setPlaying(false);
                    two.setPlaying(false);

                    //The pile is split evenly
                    one.updateWin(cardsWon/2);
                    two.updateWin(cardsWon/2);
                    return true;
                }

                //face up cards
                onesCard = one.draw();
                twosCard = two.draw();

                if(onesCard.getNumber() == 0 || twosCard.getNumber() == 0)
                {
                    //Configure end-game
                    log += "\n Game ended.";

                    one.setPlaying(false);
                    two.setPlaying(false);

                    //The two face down cards are added to the pile, and the pile is split evenly
                    cardsWon+=2;
                    one.updateWin(cardsWon/2);
                    two.updateWin(cardsWon/2);                   
                    return true;
                }
                cardsWon += 4;
            }

        }

        return false;

    }

    void Game::printLastTurn()
    {
        //Each turn represents a line- prints the last line
        if(turns == 0)
        {
            throw __throw_bad_function_call;
        }
        cout << "\n" + log.substr(log.find_last_of("\n"), string::npos) << "\n";
    }

    void Game::playAll()
    {
        //Play each turn until the game ends
        bool gameEnd = false;
        while(!gameEnd)
        {
            gameEnd = playTurn();
        }
    }

    void Game::printWiner()
    {
        //Find the winner based on cards taken
        if(one.cardesTaken() > two.cardesTaken())
        {
            cout << one.getName() + " wins the game!\n";
        }
        else if(two.cardesTaken() > one.cardesTaken())
        {
            cout << two.getName() + " wins the game!\n";
        }
        else
        {
            cout << "The game is a tie!\n";
        }
    }
    
    void Game::printLog()
    {
        cout << "\n" << log << "\n\n";
    }

    void Game::printStats()
    {
        double p1_win_rate = 100 * double(onesWins)/turns;
        double p2_win_rate = 100 * double(twosWins)/turns;
        double draw_rate = 100 * double(draws)/turns;

        cout << one.getName() + "'s win rate: " + to_string(p1_win_rate) + "% with " + to_string(one.cardesTaken()) + " cards collected.\n";
        cout << two.getName() + "'s win rate: " + to_string(p2_win_rate) + "% with " + to_string(two.cardesTaken()) + " cards collected.\n";
        cout << "The draw rate was " + to_string(draw_rate) + "% with " + to_string(draws) + " draw(s).\n";
        cout << "There were " + to_string(turns) + " turns in total, were any draw within a draw is counted as the same turn.\n";

    }
}
#include <iostream>
#include <stack>
#include "player.hpp"
#include "card.hpp"
using namespace std;

namespace ariel
{

    Player::Player(string str)
    {
        name = str;
        won = 0;
        isPlaying = false;
    }

    void Player::addCard(Card &a)
    {
        deck.push(a);
        //cout << "Last inserted card for player " << name << " is " << deck.top().getNumber()  << " and it is card number " << deck.size() << "\n";
    }

    Card Player::draw()
    {
        if(deck.empty())
        {
            return Card(); //empty card
        }
        Card top = deck.top(); //save top card
        deck.pop(); //remove top card
        return top;
        //if empty?
    }

    void Player::updateWin(int num)
    {
        won += num;
    }

    void Player::setPlaying(bool b)
    {
        isPlaying = b;
    }

    int Player::stacksize()
    {
        return deck.size();
    }

    int Player::cardesTaken()
    {
        return won;
    }

    bool Player::getPlaying()
    {
        return isPlaying;
    }

    string Player::getName()
    {
        return name;
    }
}
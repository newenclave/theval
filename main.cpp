#include <iostream>

#include <stdint.h>
#include "theval.hpp"

class card {

public:

    card( theval::eval::card_value v, theval::eval::card_suit s )
        :value_(v)
        ,suit_(s)
    { }

    static card from_string( const char *str )
    {
        theval::eval::card_value v;
        theval::eval::card_suit  s;

        switch (str[0]) {
        case '2':
            v = theval::eval::CARD_2; break;
        case '3':
            v = theval::eval::CARD_3; break;
        case '4':
            v = theval::eval::CARD_4; break;
        case '5':
            v = theval::eval::CARD_5; break;
        case '6':
            v = theval::eval::CARD_6; break;
        case '7':
            v = theval::eval::CARD_7; break;
        case '8':
            v = theval::eval::CARD_8; break;
        case '9':
            v = theval::eval::CARD_9; break;
        case 'T':
        case 't':
            v = theval::eval::CARD_T; break;
        case 'J':
        case 'j':
            v = theval::eval::CARD_J; break;
        case 'Q':
        case 'q':
            v = theval::eval::CARD_Q; break;
        case 'K':
        case 'k':
            v = theval::eval::CARD_K; break;
        case 'A':
        case 'a':
            v = theval::eval::CARD_A; break;
        default:
            v = theval::eval::CARD_0; break;
        }

        switch (str[1]) {
        case 'c':
        case 'C':
            s = theval::eval::SUIT_C; break;
        case 'd':
        case 'D':
            s = theval::eval::SUIT_D; break;
        case 'h':
        case 'H':
            s = theval::eval::SUIT_H; break;
        case 's':
        case 'S':
            s = theval::eval::SUIT_S; break;
        default:
            s = theval::eval::SUIT_0; break;
        }
        return card( v, s );
    }

    bool valid( ) const
    {
        return  ( value_ != theval::eval::CARD_0 ) &&
                ( suit_  != theval::eval::SUIT_0 );
    }

    theval::eval::card_value value( ) const
    {
        return value_;
    }

    theval::eval::card_suit suit( ) const
    {
        return suit_;
    }

private:
    theval::eval::card_value value_;
    theval::eval::card_suit  suit_;
};

class hand {

};

int main(int argc, char *argv[])
{
    return 0;
}

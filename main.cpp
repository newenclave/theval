#include <iostream>
#include <set>

#include <stdint.h>
#include <algorithm>
#include "theval.hpp"

/*
5 out 7 masks

3 4 5 6 7
2 4 5 6 7
2 3 5 6 7
2 3 4 6 7
2 3 4 5 7
2 3 4 5 6

1 4 5 6 7
1 3 5 6 7
1 3 4 6 7
1 3 4 5 7
1 3 4 5 6

1 2 5 6 7
1 2 4 5 7
1 2 4 5 7
1 2 4 5 6

1 2 3 6 7
1 2 3 5 7
1 2 3 5 6

1 2 3 4 7
1 2 3 4 6

1 2 3 4 5

*/


class card {

public:

    class name {

    public:
        name( )
        {
            str[0] =
            str[1] =
            str[2] =
            str[3] = '\0';
        }

        const char *c_str( ) const
        {
            return &str[0];
        }

        char &operator []( size_t id )
        {
            return str[id];
        }

        const char &operator []( size_t id ) const
        {
            return str[id];
        }

    private:
        char str[4];
    };

    struct value_less {
        bool operator ( )( const card &lh, const card &rh ) const
        {
            return lh.value( ) > rh.value( );
        }
    };

    struct full_less {
        bool operator ( )( const card &lh, const card &rh ) const
        {
            return lh.full( ) > rh.full( );
        }
    };

    card( theval::eval::card_value v, theval::eval::card_suit s )
    {
        card_ = (v << 4) | s;
    }

    card( )
        :card_(0)
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

    name to_string( ) const
    {
        static const name zero;
        name n;

        switch (value( )) {
        case theval::eval::CARD_2: n[0] = '2'; break;
        case theval::eval::CARD_3: n[0] = '3'; break;
        case theval::eval::CARD_4: n[0] = '4'; break;
        case theval::eval::CARD_5: n[0] = '5'; break;
        case theval::eval::CARD_6: n[0] = '6'; break;
        case theval::eval::CARD_7: n[0] = '7'; break;
        case theval::eval::CARD_8: n[0] = '8'; break;
        case theval::eval::CARD_9: n[0] = '9'; break;
        case theval::eval::CARD_T: n[0] = 'T'; break;
        case theval::eval::CARD_J: n[0] = 'J'; break;
        case theval::eval::CARD_Q: n[0] = 'Q'; break;
        case theval::eval::CARD_K: n[0] = 'K'; break;
        case theval::eval::CARD_A: n[0] = 'A'; break;
        default:
            return zero;
        }

        switch (suit( )) {
        case theval::eval::SUIT_C: n[1] = 'c'; break;
        case theval::eval::SUIT_D: n[1] = 'd'; break;
        case theval::eval::SUIT_H: n[1] = 'h'; break;
        case theval::eval::SUIT_S: n[1] = 's'; break;
        default:
            return zero;
        }

        return n;
    }

    bool valid( ) const
    {
        return  (value( ) != 0) && (suit( ) != 0);
    }

    theval::eval::card_value value( ) const
    {
        std::uint8_t val = (card_ >> 4) & 0xF;
        switch (val) {
        case theval::eval::CARD_2:
        case theval::eval::CARD_3:
        case theval::eval::CARD_4:
        case theval::eval::CARD_5:
        case theval::eval::CARD_6:
        case theval::eval::CARD_7:
        case theval::eval::CARD_8:
        case theval::eval::CARD_9:
        case theval::eval::CARD_T:
        case theval::eval::CARD_J:
        case theval::eval::CARD_Q:
        case theval::eval::CARD_K:
        case theval::eval::CARD_A:
            return static_cast<theval::eval::card_value>(val);
        }
        return theval::eval::CARD_0;
    }

    theval::eval::card_suit suit( ) const
    {
        std::uint8_t val = card_ & 0xF;
        switch (val) {
        case theval::eval::SUIT_C:
        case theval::eval::SUIT_D:
        case theval::eval::SUIT_H:
        case theval::eval::SUIT_S:
            return static_cast<theval::eval::card_suit>(val);
        }
        return theval::eval::SUIT_0;
    }

    std::uint8_t full( ) const
    {
        return card_;
    }

private:

    std::uint8_t card_;

};

std::ostream &operator << ( std::ostream &o, const card &c )
{
    card::name n = c.to_string( );
    return o << n.c_str( );
}

bool operator < ( const card &lh, const card &rh )
{
    card::full_less less;
    return less( lh, rh );
}

class hand {

public:

    struct state {

        state( )
            :value(0)
            ,mask(0)
            ,flush(false)
            ,streight(false)
        { }

        std::uint64_t value;
        std::uint16_t mask;
        bool flush;
        bool streight;
    };

    hand( )
        :count_(0)
    { }

    void add( card c )
    {
        all_[count_++] = c;
    }

    size_t size( ) const
    {
        return count_;
    }

    void finalize( )
    {
        sort( );

        st_.value = theval::eval::value( all_[0].value( ), all_[1].value( ),
                                         all_[2].value( ), all_[3].value( ),
                                         all_[4].value( ) );

        st_.mask = theval::eval::mask( all_[0].value( ), all_[1].value( ),
                                       all_[2].value( ), all_[3].value( ),
                                       all_[4].value( ) );

        st_.flush = theval::eval::flush( all_[0].suit( ), all_[1].suit( ),
                                         all_[2].suit( ), all_[3].suit( ),
                                         all_[4].suit( ) );

        st_.streight = theval::eval::straight( st_.mask );
    }

    std::string to_string( ) const
    {
        std::string res;

        for( size_t i=0; i<count_; i++ ) {
            card::name n = all_[i].to_string( );
            res = res += n.c_str( );
        }

        return res;
    }

private:

    void sort( )
    {
        std::sort( &all_[0], &all_[count_] );
    }

    card    all_[5];
    size_t  count_;
    state   st_;
};

std::ostream &operator << ( std::ostream &o, const hand &c )
{
    return o << c.to_string( );
}

#define T 10
#define J 11
#define Q 12
#define K 13
#define A 14

#define HAND0 T, T, T, 2, 2
#define HAND1 T, T, 2, 2, 2

std::uint64_t from_bin( const char *p )
{
    std::uint64_t res;
    while( *p ) {
        switch (*p) {
        case '0':
            res <<= 1; break;
        case '1':
            res = (res << 1) | 1;
            break;
        case '_':
        case '-':
        case ' ':
            break;
        default:
            return 0;
        }
        p++;
    }
    return res;
}

int main(int argc, char *argv[])
{

    auto c1 = card::from_string( "Ac" );
    auto c2 = card::from_string( "Kc" );
    auto c3 = card::from_string( "2s" );
    auto c4 = card::from_string( "5h" );
    auto c5 = card::from_string( "Ad" );

    hand h;
    h.add( c1 );
    h.add( c2 );
    h.add( c3 );
    h.add( c4 );
    h.add( c5 );

    h.finalize( );

    std::cout << h << "\n";

    std::set<card> cset;
    cset.insert( c1 );
    cset.insert( c2 );
    cset.insert( c3 );
    cset.insert( c4 );
    cset.insert( c5 );
    cset.insert( c1 );

    for( auto s: cset ) {
        std::cout << s << " ";
    }


    auto m = theval::eval::mask(  HAND1 );
    auto v = theval::eval::value( HAND1 );

    std::cout << theval::eval::get_weight(v, m, false) << "\n";

    std::cout << from_bin( "1111 0000 0000 0001" ) % 15 << "\n";

    return 0;
}

#ifndef THEVAL_HPP
#define THEVAL_HPP

#include <cstdint>

namespace theval {

    struct eval {

        enum card_value {
            CARD_0 =  0, /// invalid value
            CARD_2 =  2,
            CARD_3 =  3,
            CARD_4 =  4,
            CARD_5 =  5,
            CARD_6 =  6,
            CARD_7 =  7,
            CARD_8 =  8,
            CARD_9 =  9,
            CARD_T = 10,
            CARD_J = 11,
            CARD_Q = 12,
            CARD_K = 13,
            CARD_A = 14,
        };

        enum card_suit {
            SUIT_0 =  0, /// invalid value
            SUIT_C =  1,
            SUIT_D =  2,
            SUIT_H =  4,
            SUIT_S =  8,
        };

        enum hand_weight {
            WEIGHT_INVALID   =  0,
            WEIGHT_HIGH      =  1,
            WEIGHT_PAIR      =  2,
            WEIGHT_2_PAIRS   =  3,
            WEIGHT_3_A_KIND  =  4,
            WEIGHT_STREIGHT  =  5,
            WEIGHT_FLUSH     =  6,
            WEIGHT_FHOUSE    =  7,
            WEIGHT_4_A_KIND  =  8,
            WEIGHT_SFLUSH    =  9,
            WEIGHT_RFLUSH    = 10,
        };

        std::uint16_t mask( std::uint16_t c1, std::uint16_t c2,
                            std::uint16_t c3, std::uint16_t c4,
                            std::uint16_t c5 )
        {
            return  1 << c1 | 1 << c2 | 1 << c3 | 1 << c4 | 1 << c5 ;
        }

        bool straight( std::uint16_t mask )
        {
            return ( mask == 0x403C ) ||
                   ( mask / ( mask & std::uint16_t(-mask) ) == 0x1F ) ;
        }

        int flush( std::uint16_t s1, std::uint16_t s2, std::uint16_t s3,
                   std::uint16_t s4, std::uint16_t s5 )
        {
            return s1 == ( s2 | s3 | s4 | s5 );
        }

        std::uint64_t value( std::uint16_t c1, std::uint16_t c2,
                             std::uint16_t c3, std::uint16_t c4,
                             std::uint16_t c5 )
        {
            std::uint64_t res   = 0;
            std::uint64_t place = 0;

            place = (res >> ((c1 - 2) << 2) & 0xFF );
            place = ((place << 1) | 1);
            res  |= (place & 0xF)  << ((c1 - 2) << 2);

            place = (res >> ((c2 - 2) << 2) & 0xFF );
            place = ((place << 1) | 1);
            res  |= (place & 0xF)  << ((c2 - 2) << 2);

            place = (res >> ((c3 - 2) << 2) & 0xFF );
            place = ((place << 1) | 1);
            res  |= (place & 0xF)  << ((c3 - 2) << 2);

            place = (res >> ((c4 - 2) << 2) & 0xFF );
            place = ((place << 1) | 1);
            res  |= (place & 0xF)  << ((c4 - 2) << 2);

            place = (res >> ((c5 - 2) << 2) & 0xFF );
            place = ((place << 1) | 1);
            res  |= (place & 0xF) << ((c5 - 2) << 2);

            return res;
        }

        hand_weight get_weight ( std::uint64_t value, std::uint16_t mask,
                                 bool is_flush )
        {
            static const hand_weight values[ ] = {
                WEIGHT_HIGH     ,
                WEIGHT_PAIR     ,
                WEIGHT_2_PAIRS  ,
                WEIGHT_3_A_KIND ,
                WEIGHT_STREIGHT ,
                WEIGHT_FLUSH    ,
                WEIGHT_FHOUSE   ,
                WEIGHT_4_A_KIND ,
                WEIGHT_SFLUSH   ,
                WEIGHT_RFLUSH   ,
            };

            static const size_t value_size = sizeof(values) / sizeof(values[0]);

            value =  ( value % 15 ) - ( straight( mask ) ? 3 : 1 );
            value -= ( is_flush * ( (mask == 0x7c00) ? -5 : 1) );

            return value >= value_size ? WEIGHT_INVALID : values[value];
        }

    };
}

#endif // THEVAL_HPP

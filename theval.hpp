#ifndef THEVAL_HPP
#define THEVAL_HPP

#include <cstdint>

namespace theval {

    struct eval {

        enum hand_waight {
            HAND_INVALID   =  0,
            HAND_HIGH      =  1,
            HAND_PAIR      =  2,
            HAND_2_PAIRS   =  3,
            HAND_3_A_KIND  =  4,
            HAND_STREIGHT  =  5,
            HAND_FLUSH     =  6,
            HAND_FHOUSE    =  7,
            HAND_4_A_KIND  =  8,
            HAND_SFLUSH    =  9,
            HAND_RFLUSH    = 10,
        };

        std::uint16_t mask( std::uint16_t c1, std::uint16_t c2,
                            std::uint16_t c3, std::uint16_t c4,
                            std::uint16_t c5 )
        {
            return  1 << c1 | 1 << c2 | 1 << c3 | 1 << c4 | 1 << c5 ;
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

        hand_waight get_weight ( std::uint64_t value, std::uint16_t mask,
                                 bool is_flush )
        {
            static const hand_waight values[ ] = {
                HAND_HIGH     ,
                HAND_PAIR     ,
                HAND_2_PAIRS  ,
                HAND_3_A_KIND ,
                HAND_STREIGHT ,
                HAND_FLUSH    ,
                HAND_FHOUSE   ,
                HAND_4_A_KIND ,
                HAND_SFLUSH   ,
                HAND_RFLUSH   ,
            };

            static const size_t value_size = sizeof(values) / sizeof(values[0]);

            value =  ( value % 15 ) - ( straight( mask ) ? 3 : 1 );
            value -= ( is_flush * ( (mask == 0x7c00) ? -5 : 1) );

            return value >= value_size ? HAND_INVALID : values[value];
        }

    };
}

#endif // THEVAL_HPP

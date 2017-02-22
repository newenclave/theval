#include <stdio.h>
#include "theval.h"


uint16_t mask( uint16_t c1, uint16_t c2, uint16_t c3,
               uint16_t c4, uint16_t c5 )
{
    return  1 << c1 | 1 << c2 | 1 << c3 | 1 << c4 | 1 << c5 ;
}

uint64_t value( uint16_t c1, uint16_t c2, uint16_t c3,
                uint16_t c4, uint16_t c5 )
{
    uint64_t res   = 0;
    uint64_t place = 0;

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

int straight( uint16_t mask )
{
    return ( mask == 0x403C ) ||
           ( mask / ( mask & (uint16_t)(-mask) ) == 0x1F ) ;
}

int flush( uint16_t s1, uint16_t s2, uint16_t s3,
           uint16_t s4, uint16_t s5 )
{
    return s1 == ( s2 | s3 | s4 | s5 );
}

int get_weight ( uint64_t value, uint16_t mask, int is_flush )
{
    static const int values[ ] = {
        THEVAL_4_A_KIND,
        THEVAL_SFLUSH  ,
        THEVAL_STREIGHT,
        THEVAL_FLUSH   ,
        THEVAL_HIGH    ,
        THEVAL_PAIR    ,
        THEVAL_2_PAIRS ,
        THEVAL_RFLUSH  ,
        THEVAL_3_A_KIND,
        THEVAL_FHOUSE  ,
    };

    static const uint32_t value_size = sizeof(values) / sizeof(values[0]);

    value =  ( value % 15 ) - ( straight( mask ) ? 3 : 1 );
    value -= ( is_flush * ( (mask == 0x7c00) ? -5 : 1) );

    return value >= value_size ? THEVAL_INVALID : values[value];
}


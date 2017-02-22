#ifndef THEVAL_H
#define THEVAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define THEVAL_CARD_2  2
#define THEVAL_CARD_3  3
#define THEVAL_CARD_4  4
#define THEVAL_CARD_5  5
#define THEVAL_CARD_6  6
#define THEVAL_CARD_7  7
#define THEVAL_CARD_8  8
#define THEVAL_CARD_9  9

#define THEVAL_CARD_T 10
#define THEVAL_CARD_J 11
#define THEVAL_CARD_Q 12
#define THEVAL_CARD_K 13
#define THEVAL_CARD_A 14

#define THEVAL_CARD_MIN THEVAL_CARD_2
#define THEVAL_CARD_MAX THEVAL_CARD_A

#define THEVAL_SUIT_C 1
#define THEVAL_SUIT_D THEVAL_SUIT_C << 1
#define THEVAL_SUIT_H THEVAL_SUIT_C << 2
#define THEVAL_SUIT_S THEVAL_SUIT_C << 3

#define THEVAL_INVALID   0
#define THEVAL_HIGH      1
#define THEVAL_PAIR      2
#define THEVAL_2_PAIRS   3
#define THEVAL_3_A_KIND  4
#define THEVAL_STREIGHT  5
#define THEVAL_FLUSH     6
#define THEVAL_FHOUSE    7
#define THEVAL_4_A_KIND  8
#define THEVAL_SFLUSH    9
#define THEVAL_RFLUSH   10

struct theval_hand_name_weight {
    int         weight;
    const char *name;
};

uint16_t mask( uint16_t c1, uint16_t c2, uint16_t c3,
               uint16_t c4, uint16_t c5 );

uint64_t value( uint16_t c1, uint16_t c2, uint16_t c3,
                uint16_t c4, uint16_t c5 );

int straight( uint16_t mask );

int flush( uint16_t s1, uint16_t s2, uint16_t s3,
           uint16_t s4, uint16_t s5 );

int get_weight( uint64_t value, uint16_t mask, int is_flush );

#ifdef __cplusplus
}
#endif

#endif // THEVAL_H

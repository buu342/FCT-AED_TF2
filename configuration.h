#ifndef _CONFIG
#define _CONFIG

    #define DEBUG_MODE      1

    #define bool            char
    #define FALSE           0
    #define TRUE            1

    #define status          char
    #define FAILURE         0
    #define SUCCESS         1

    #define MAX_INPUT       140
    #define MAX_TRAMPOLINES 500
    #define MAX_CLIENTS     1500
    #define MAX_STOCK       3000

    #define KEYTYPE_INT     0
    #define KEYTYPE_STRING  1

    #define NUM_FOOD        3
    #define FOOD_COFFEE     'C'
    #define FOOD_JUICE      'S'
    #define FOOD_CAKE       'B'

    #define LOCATION_LINE           'L'
    #define LOCATION_TRAMPOLINES    'T'
    #define LOCATION_BAR            'B'

    #define max(a,b) ((a)>(b) ? a:b)

#endif
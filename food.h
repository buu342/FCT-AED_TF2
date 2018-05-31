#ifndef _H_FOOD
#define _H_FOOD

    typedef struct _food * food;

    food    food_create(int stock, float price);
    void    food_destroy(food f);
    void    food_destroy_all(void* f);

    int     food_get_stock(food f);
    float   food_get_price(food f);

    void    food_set_stock(food f, int stock);

#endif
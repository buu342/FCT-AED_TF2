#include <stdlib.h>
#include "configuration.h"
#include "food.h"

struct _food
{
    int     stock;
    float   price;
};

/*===================================
             food_create
 Allocate memory for a new food item 
            and return it
===================================*/

food food_create(int stock, float price)
{
    // Allocate memory for the food
    food f = (food) malloc(sizeof(struct _food));

    // Make sure we managed to allocate memory.
    if (f == NULL) 
        return NULL;

    f->stock = stock;
    f->price = price;

    return f;
}


/*===================================
           food_destroy
 Free memory occupied by a food item
===================================*/

void food_destroy(food f)
{
    free(f);
}


/*===================================
         food_destroy_all
  Free memory occupied by all food
===================================*/

void food_destroy_all(void* f)
{
    food_destroy((food) f);
}


/*===================================
         food_get_stock
  Return the stock for this specific
             item
===================================*/

int food_get_stock(food f)
{
    return f->stock;
}


/*===================================
         food_set_stock
   Set the stock for this specific
             item
===================================*/

void food_set_stock(food f, int stock)
{
    f->stock = stock;
}


/*===================================
         food_get_price
  Return the price for this specific
             item
===================================*/

float food_get_price(food f)
{
    return f->price;
}

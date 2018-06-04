#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "configuration.h"
#include "food.h"


/*===================================
           Global Variables
===================================*/

struct _food
{
    int     stock;
    float   price;
    char*   name;
};


/*===================================
             food_create
 Allocate memory for a new food item 
            and return it
===================================*/

food food_create(int stock, float price, char* name)
{
    // Allocate memory for the food
    food f = (food) malloc(sizeof(struct _food));

    // Make sure we managed to allocate memory.
    if (f == NULL)
        return NULL;

    f->stock = stock;
    f->price = price;
    f->name = (char*) malloc(sizeof(char)*strlen(name)+1);
    strcpy(f->name, name);

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
  Return the stock of this specific
               item
===================================*/

int food_get_stock(food f)
{
    return f->stock;
}


/*===================================
            food_set_stock
   Set the stock of this specific
                item
===================================*/

void food_set_stock(food f, int stock)
{
    f->stock = stock;
}


/*===================================
            food_get_price         
  Return the price of this specific
                item
===================================*/

float food_get_price(food f)
{
    return f->price;
}


/*===================================
            food_get_name              
  Return the name of this specific
               item
===================================*/

char* food_get_name(food f)
{
    return f->name;
}


/*===================================
       food_get_key_from_index              
Return the key from an index (for for
               loops)
===================================*/

char* food_get_key_from_index(int index)
{
    char* key;
    switch(index)
    {
        case 0: key = FOOD_COFFEE; break;
        case 1: key = FOOD_JUICE; break;
        case 2: key = FOOD_CAKE; break;
    }
    return key;
}


/*===================================
       food_get_name_from_index              
  Return the name from an index (for 
              for loops)
===================================*/

char* food_get_name_from_index(int index)
{
    char* name;
    switch(index)
    {
        case 0: name = "cafe"; break;
        case 1: name = "sumo"; break;
        case 2: name = "bolo"; break;
    }
    return name;
}
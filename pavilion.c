#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // For debugging
#include "configuration.h"
#include "iterador.h"
#include "dicionario.h"
#include "client.h"
#include "food.h"
#include "pavilion.h"


/*===================================
           Global Variables
===================================*/

struct _pavilion
{
    float cash;
    int num_trampolines;

    dicionario clients;
    dicionario bar;
};


/*===================================
              Prototypes            
===================================*/

status pavilion_add_food(pavilion p, int index, int stock, float price);


/*===================================
          create_pavilion
  Allocate memory for our starting 
      pavilion and return it
===================================*/

pavilion pavilion_create()
{
    // Variables
    int i;

    // Allocate memory for our pavilion and make sure it works
    pavilion p = (pavilion) malloc(sizeof(struct _pavilion));
    if (p == NULL) 
        return NULL;

    // Create a dictionary to store our clients and make sure it works
    p->clients = criaDicionario(MAX_CLIENTS, KEYTYPE_INT);
    if (p->clients == NULL)
    {
        free(p);
        return NULL;
    }

    // Create a dictionary to store our food and make sure it works
    p->bar = criaDicionario(NUM_FOOD, KEYTYPE_STRING);
    if (p->bar == NULL)
    {
        free(p);
        return NULL;
    }

    // Set default values and request trampoline number and bar stock+price
    p->cash = 0.0;
    if (!DEBUG_MODE)
    {
        int stock;
        float price;
        scanf("%d", &(p->num_trampolines));

        for (i=0;i<NUM_FOOD;i++)
        {
            printf("%d - ", i);
            scanf("%d %f", &stock, &price);
            if (pavilion_add_food(p, i, stock, price) == FAILURE)
                return NULL;
            printf("%d - %d %f\n", i, stock, price);
        }
    }
    else
    {
        int stock;
        float price;

        p->num_trampolines = rand()%20;
        printf("%d\n", p->num_trampolines);

        for (i=0;i<NUM_FOOD;i++)
        {
            stock = rand()%MAX_STOCK;
            price = ((float)(rand()%9999))/100;
            printf("%d %.2f\n", stock, price);
            if (pavilion_add_food(p, i, stock, price) == FAILURE)
                return NULL;
        }
    }

    return p;
}


/*===================================
         pavilion_destroy
Free the memory used by the pavilion
          and its structs
===================================*/

void pavilion_destroy(pavilion p)
{
    destroiDicEElems(p->clients, client_destroy_all);
    destroiDicEElems(p->bar, food_destroy_all);
    free(p);
}


/*===================================
         pavilion_get_cash
     Return the amount of cash
===================================*/

float pavilion_get_cash(pavilion p)
{
    return p->cash;
}


/*===================================
         pavilion_set_cash
       Set the amount of cash
===================================*/

void pavilion_set_cash(pavilion p, float cash)
{
    p->cash = cash;
}


/*===================================
        pavilion_add_client
    Add a client to the pavilion
===================================*/

status pavilion_add_client(pavilion p, char* name, int num_id, int num_tax)
{
    // Create a variable so we don't access the ID variable directly
    int key = num_id;

    // Create a client
    client c = client_create(name, num_tax);

    // Make sure he returned properly
    if (c == NULL)
        return FAILURE;

    // Check if the client isn't already in the pavilion
    if (pavilion_exists_client(p, key) == TRUE)
        return FAILURE;

    // Add him to the dictionary with his ID as the key
    status ret = adicionaElemDicionario(p->clients, (void*)&key, c);

    // Make sure it returned success, and if so return success
    if (ret == FAILURE)
        client_destroy(c);

    return SUCCESS;
}


/*===================================
       pavilion_remove_client
  Remove a client from the pavilion
===================================*/

client pavilion_remove_client(pavilion p, int num_id)
{
    int key = num_id;
    return (client) removeElemDicionario(p->clients, (void*)&key);
}


/*===================================
        pavilion_exists_client
  Check if a client with a given ID 
        exists in the pavilion
===================================*/

bool pavilion_exists_client(pavilion p, int num_id)
{
    int key = num_id;
    return existeElemDicionario(p->clients, (void*)&key);
}


/*===================================
        pavilion_get_client
    Return a client using an id
===================================*/

client pavilion_get_client(pavilion p, int num_id)
{
    int key = num_id;
    return (client) elementoDicionario(p->clients, (void*)&key);
}


/*===================================
       pavilion_count_clients      
     Return the number of clients
===================================*/

int pavilion_count_clients(pavilion p)
{
    return tamanhoDicionario(p->clients);
}



/*===================================
        pavilion_add_food
Helper function to add a food element
      to the bar dictionary
===================================*/

status pavilion_add_food(pavilion p, int index, int stock, float price)
{
    // Variables
    char key;
    switch  (index)
    {
        case 0: key = FOOD_COFFEE; break;
        case 1: key = FOOD_JUICE; break;
        case 2: key = FOOD_CAKE; break;
    }

    // Create the food item and check it works
    food f = food_create(stock, price);
    if (f == NULL)
        return FAILURE;

    // Add it to the dictionary with the char as the key
    status ret = adicionaElemDicionario(p->bar, (void*)&key, f);

    // Make sure it returned success
    if (ret == FAILURE)
    {
        food_destroy(f);
        return FAILURE;
    }
    return SUCCESS;
}


/*===================================
        pavilion_exists_food
  Check if a food item with a given
      index  exists in the bar
===================================*/

bool pavilion_exists_food(pavilion p, char item)
{
    char key = item;
    return existeElemDicionario(p->bar, (void*)&key);
}


/*===================================
        pavilion_get_food
Return a food item using a character
===================================*/

food pavilion_get_food(pavilion p, char item)
{
    char key = item;
    return (food) elementoDicionario(p->bar, (void*)&key);
}
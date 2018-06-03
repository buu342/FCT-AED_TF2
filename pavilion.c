#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"
#include "iterador.h"
#include "dicionario.h"
#include "fila.h"
#include "sequencia.h"
#include "quicksort.h"
#include "client.h"
#include "food.h"
#include "slot.h"
#include "trampoline.h"
#include "pavilion.h"

#if DEBUG_MODE
    #include <time.h>
#endif

/*===================================
           Global Variables
===================================*/

struct _pavilion
{
    float cash;
    int num_trampolines;

    dicionario  clients;
    dicionario  bar;
    fila        queue;
    sequencia   trampolines;
};


/*===================================
              Prototypes            
===================================*/

status pavilion_add_food(pavilion p, int index, int stock, float price); // Not in pavillion.h


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

    // Create a queue to store our clients
    p->queue = criaFila(MAX_CLIENTS);
    if (p->queue == NULL)
    {
        free(p);
        return NULL;
    }

    // Set default values and request trampoline number and bar stock+price
    p->cash = 0.0;
    if (!DEBUG_MODE)
    {
        scanf("%d", &(p->num_trampolines));

        for (i=0;i<NUM_FOOD;i++)
        {
            int stock;
            float price;
            scanf("%d %f", &stock, &price);
            if (pavilion_add_food(p, i, stock, price) == FAILURE)
                return NULL;
        }
    }
    else
    {
        p->num_trampolines = 1+(rand()%19);
        printf("%d\n", p->num_trampolines);

        for (i=0;i<NUM_FOOD;i++)
        {
            int stock = rand()%MAX_STOCK;
            float price = ((float)(rand()%9999))/100;
            printf("%d %.2f\n", stock, price);
            if (pavilion_add_food(p, i, stock, price) == FAILURE)
                return NULL;
        }
    }


    // Create a sequence of trampolines and fill it up with an empty trampoline struct
    p->trampolines = criaSequencia(p->num_trampolines);
    if (p->trampolines == NULL)
    {
        free(p);
        return NULL;
    }
    for (i=0;i<p->num_trampolines;i++)
    {
        trampoline t = trampoline_create();
        if (t == NULL)
            return NULL;
        adicionaPosSequencia(p->trampolines, t, i+1);
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
    destroiFilaEElems(p->queue, slot_destroy_all);
    destroiSeqElems(p->trampolines, trampoline_destroy_all);
    free(p);
}


/*===================================
           pavilion_close
  Force everyone out of the pavilion
===================================*/

void pavilion_close(pavilion p)
{
    iterador it = iteradorDicionario(p->clients);
    while (temSeguinteIterador(it))
    {
        client c = seguinteIterador(it);
        if (client_get_location(c) == LOCATION_TRAMPOLINE)
        {
            client_set_time(c, 1440 - client_get_time(c));
            pavilion_set_cash(p, pavilion_get_cash(p) + client_get_bill(c) + ((1+max(ceil(client_get_time(c), 30)-1,0))*5));
        }
        else
            pavilion_set_cash(p, pavilion_get_cash(p) + client_get_bill(c));
    }
    destroiIterador(it);
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
    {
        return FAILURE;
    }

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
       pavilion_sort_clients
   Sort (alphabetically) a list of 
          clients and keys
===================================*/

void pavilion_sort_clients(pavilion p, char temp_name[MAX_CLIENTS][MAX_INPUT], int temp_keys[MAX_CLIENTS])
{
    // Variables
    int min = 0;
    int max = pavilion_count_clients(p)-1;
    iterador it = iteradorChaveDicionario(p->clients);
    int i = 0;

    // Fill our temp name and keys arrays with names and keys
    while (temSeguinteIterador(it))
    {
        int* key = seguinteIterador(it);
        client c = pavilion_get_client(p, *key);
        strcpy(temp_name[i], client_get_name(c));
        temp_keys[i] = *key;
        i++;
    }

    // Quick sort through the names and keys
    quick_sort(temp_name, temp_keys, min, max);

    // Free the memory used by our iterator
    destroiIterador(it);
}


/*===================================
         pavilion_printdebug       
  Print the queue size and list of
     clients in the trampolines
===================================*/

#if DEBUG_MODE
    void pavilion_printdebug(pavilion p)
    {
        int i=0;
 
        if (vaziaFila(p->queue) == TRUE)
            printf("\x1b[31m Queue Empty \x1b[0m\n");
        else
            printf("\x1b[31m Queue Size %d \x1b[0m\n", tamanhoFila(p->queue));

        iterador it = iteradorSequencia(p->trampolines);
        while (temSeguinteIterador(it))
        {
            trampoline t = seguinteIterador(it);
            i++;
            if (trampoline_empty(t) == TRUE)
                printf("\x1b[31m Trampoline %2d - Empty \x1b[0m\n", i);
            else
                printf("\x1b[31m Trampoline %2d - %s \x1b[0m\n", i, client_get_name(trampoline_get_client(t)));
        }
        destroiIterador(it);
    }
#endif


/*===================================
       pavilion_move_client
  Move a client around the pavilion
===================================*/

int pavilion_move_client(pavilion p, int helper, char location)
{
    int i=0;
    if (location == LOCATION_QUEUE)
    {
        // Get a client from the ID and set his location
        client c = pavilion_get_client(p, helper);
        if (c == NULL)
            return 0;
        client_set_location(c, location);

        // Allocate memory for a slot in the queue
        slot s = slot_create(c, helper);
        if (s == NULL)
            return 0;

        // Add the slot to the queue
        adicionaElemFila(p->queue, s);
    }
    else if (location == LOCATION_TRAMPOLINE)
    {
        iterador it = iteradorSequencia(p->trampolines);
        while (temSeguinteIterador(it))
        {
            trampoline t = seguinteIterador(it);
            if (!trampoline_empty(t) && !temSeguinteIterador(it))
                return TRAMPOLINE_EMPTY;
            else if (trampoline_empty(t))
            {
                if (vaziaFila(p->queue))
                    continue;

                slot s = removeElemFila(p->queue);
                if (s == NULL)
                {
                    destroiIterador(it);
                    return TRAMPOLINE_BUSY;
                }
                i++;
                client c = slot_get_client(s);
                trampoline_set_client(t, c, slot_get_id(s));
                client_set_location(c, location);
                client_set_time(c, client_get_time(c) + helper);
            }
        }
        destroiIterador(it);
    }
    else if (location == LOCATION_BAR)
    {
        iterador it = iteradorSequencia(p->trampolines);
        while (temSeguinteIterador(it))
        {
            trampoline t = seguinteIterador(it);
            if (trampoline_get_id(t) == helper)
            {
                trampoline_remove_client(t);
                client c = pavilion_get_client(p, helper);
                client_set_location(c, LOCATION_BAR);
                destroiIterador(it);
                return SUCCESS;
            }
        }
        destroiIterador(it);
        return TRAMPOLINE_NULL;
    }

    #if DEBUG_MODE
        pavilion_printdebug(p);
    #endif

    return i;
}


/*===================================
        pavilion_add_food
Helper function to add a food element
      to the bar dictionary
===================================*/

status pavilion_add_food(pavilion p, int index, int stock, float price)
{
    // Variables
    char* key = food_get_key_from_index(index);
    char* name = food_get_name_from_index(index);

    // Create the food item and check it works
    food f = food_create(stock, price, name);
    if (f == NULL)
        return FAILURE;

    // Add it to the dictionary with the char as the key
    status ret = adicionaElemDicionario(p->bar, key, f);

    //printf("Added %s, new size: %d, found %d", name, tamanhoDicionario(p->bar), existeElemDicionario(p->bar, key));

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

bool pavilion_exists_food(pavilion p, char* item)
{
    char* key = item;
    return existeElemDicionario(p->bar, key);
}


/*===================================
          pavilion_get_food
Return a food item using a character
===================================*/

food pavilion_get_food(pavilion p, char* item)
{
    char* key = item;
    return (food) elementoDicionario(p->bar, key);
}


/*===================================
  pavilion_get_trampoline_clientid
 Return the ID of the client in the 
        specified trampoline
===================================*/

int pavilion_get_trampoline_clientid(pavilion p, int index)
{
    int i=1;
    iterador it = iteradorSequencia(p->trampolines);
    while (temSeguinteIterador(it))
    {
        trampoline t = seguinteIterador(it);
        if (i == index)
        {
            destroiIterador(it);
            if (trampoline_empty(t))
                return TRAMPOLINE_EMPTY;
            else
                return trampoline_get_id(t);
        }
        i++;
    }
    destroiIterador(it);
    return TRAMPOLINE_NULL;
}



int pavilion_find_trampoline(pavilion p, int num_id)
{
    int i=1;
    iterador it = iteradorSequencia(p->trampolines);
    while (temSeguinteIterador(it))
    {
        trampoline t = seguinteIterador(it);
        if (trampoline_get_id(t) == num_id)
        {
            destroiIterador(it);
            return i;
        }
        i++;
    }

    // This shouldn't happen... But just in case!
    destroiIterador(it);
    return TRAMPOLINE_NULL;
}
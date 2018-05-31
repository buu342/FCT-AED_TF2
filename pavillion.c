#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // For debugging
#include "configuration.h"
#include "iterador.h"
#include "dicionario.h"
#include "client.h"
#include "pavillion.h"


/*===================================
           Global Variables
===================================*/

struct _pavillion
{
    float cash;
    int num_trampolines;
    dicionario clients;
};


/*===================================
          create_pavillion
  Allocate memory for our starting 
      pavillion and return it
===================================*/

pavillion pavillion_create()
{
    // Allocate memory for our pavillion
    pavillion p = (pavillion) malloc(sizeof(struct _pavillion));

    // Make sure we managed to allocate memory
    if (p == NULL) 
        return NULL;

    // Create a dictionary to store our clients
    p->clients = criaDicionario(MAX_CLIENTS,0 );

    // Make sure we managed to allocate memory for the clients
    if (p->clients == NULL)
    {
        free(p);
        return NULL;
    }

    // Set default values and request stuff
    p->cash = 0.0;

    if (!DEBUG_MODE)
    {
        char command[MAX_INPUT];
        fgets(command, MAX_INPUT, stdin);
        sscanf(command, "%d", &(p->num_trampolines));
    }
    else
    {
        p->num_trampolines = rand()%20;
        printf("%d\n", p->num_trampolines);
    }

    return p;
}


/*===================================
         pavillion_destroy
Free the memory used by the pavilion
          and its structs
===================================*/

void pavillion_destroy(pavillion p)
{
    destroiDicEElems(p->clients, client_destroy_all);
    free(p);
}


/*===================================
         pavillion_get_cash
     Return the amount of cash
===================================*/

float pavillion_get_cash(pavillion p)
{
    return p->cash;
}


/*===================================
        pavillion_add_client
    Add a client to the pavillion
===================================*/

status pavillion_add_client(pavillion p, char* name, int num_id, int num_tax)
{
    // Create a variable so we don't access the ID variable directly
    int key = num_id;

    // Create a client
    client c = client_create(name, num_tax);

    // Make sure he returned properly
    if (c == NULL)
        return FAILURE;

    // Check if the client isn't already in the pavillion
    if (pavillion_exists_client(p, key) == TRUE)
        return FAILURE;

    // Add him to the dictionary with his ID as the key
    status ret = adicionaElemDicionario(p->clients, (void*)&key, c);

    // Make sure it returned success, and if so return success
    if (ret == FAILURE)
        client_destroy(c);

    return SUCCESS;
}


/*===================================
       pavillion_remove_client
  Remove a client from the pavillion
===================================*/

client pavillion_remove_client(pavillion p, int num_id)
{
    int key = num_id;
    return (client) removeElemDicionario(p->clients, (void*)&key);
}


/*===================================
        pavillion_exists_client
  Check if a client with a given ID 
        exists in the pavillion
===================================*/

bool pavillion_exists_client(pavillion p, int num_id)
{
    int key = num_id;
    return existeElemDicionario(p->clients, (void*)&key);
}


/*===================================
        pavillion_get_client
    Return a client using an id
===================================*/

client pavillion_get_client(pavillion p, int num_id)
{
    int key = num_id;
    return (client) elementoDicionario(p->clients, (void*)&key);
}
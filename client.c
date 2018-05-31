#include <stdlib.h>
#include "configuration.h"
#include "client.h"


/*===================================
           Global Variables
===================================*/

struct _client
{
    char*   name;
    int     num_tax;
    int     time;
    float   bill;
    char    location;
};


/*===================================
           client_create
Allocate memory for a new client and
            return him
===================================*/

client client_create(char* name, int num_tax)
{
    // Allocate memory for the client
    client c = (client) malloc(sizeof(struct _client));

    // Make sure we managed to allocate memory.
    if (c == NULL) 
        return NULL;

    // Set the variables and return him
    c->name = name;
    c->num_tax = num_tax;
    c->time = 0;
    c->bill = 0.0;
    c->location = LOCATION_BAR;

    return c;
}


/*===================================
           client_destroy
  Free memory occupied by a client
===================================*/

void client_destroy(client c)
{
    free(c);
}


/*===================================
         client_destroy_all
 Free memory occupied by all clients
===================================*/

void client_destroy_all(void* c)
{
    client_destroy((client) c);
}

/*===================================
           client_get_name
      Return the client's name
===================================*/

char* client_get_name(client c)
{
    return c->name;
}


/*===================================
         client_get_num_tax
    Return the client's tax number
===================================*/

int client_get_num_tax(client c)
{
    return c->num_tax;
}


/*===================================
           client_get_time
Return the client's time of entry to
       a trampoline (in minutes)
===================================*/

int client_get_time(client c)
{
    return c->time;
}


/*===================================
           client_set_time
 Set the client's time of entry to a
       trampoline (in minutes)
===================================*/

void client_set_time(client c, int time)
{
    c->time = time;
}


/*===================================
           client_get_bill
      Return the client's bill
===================================*/

float client_get_bill(client c)
{
    return c->bill;
}


/*===================================
           client_set_bill
        Set the client's bill
===================================*/

void client_set_bill(client c, float bill)
{
    c->bill = bill;
}


/*===================================
         client_get_location
    Return the client's location
===================================*/

char client_get_location(client c)
{
    return c->location;
}


/*===================================
         client_set_location
      Set the client's location
===================================*/

void client_set_location(client c, char location)
{
    c->location = location;
}
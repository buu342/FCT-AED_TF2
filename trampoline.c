#include <stdlib.h>
#include "configuration.h"
#include "client.h"
#include "trampoline.h"


/*===================================
           Global Variables
===================================*/

struct _trampoline
{
    client c;
    int num_id;
};


/*===================================
          trampoline_create
   Allocate memory for a trampoline
===================================*/

trampoline trampoline_create()
{
    // Allocate memory for the trampoline
    trampoline t = (trampoline) malloc(sizeof(struct _trampoline));

    // Make sure we managed to allocate memory.
    if (t == NULL) 
        return NULL;

    t->c = NULL;
    t->num_id = 0;

    return t;
}


/*===================================
         trampoline_destroy
Free the memory used by a trampoline
===================================*/

void trampoline_destroy(trampoline t)
{
    free(t);
}


/*===================================
       trampoline_destroy_all
     Free the memory used by all
            trampolines
===================================*/

void trampoline_destroy_all(void* t)
{
    trampoline_destroy((trampoline) t);
}


/*===================================
        trampoline_set_client
 Set the client using the trampoline
===================================*/

void trampoline_set_client(trampoline t, client c, int num_id)
{
    t->c = c;
    t->num_id = num_id;
}


/*===================================
       trampoline_remove_client
 Remove a client from the trampoline
===================================*/

void trampoline_remove_client(trampoline t)
{
    t->c = NULL;
    t->num_id = 0;
}


/*===================================
          trampoline_empty
  Return if the trampoline is empty
===================================*/

bool trampoline_empty(trampoline t)
{
    return (t->c == NULL);
}


/*===================================
        trampoline_get_client
 Return the client in the trampoline
===================================*/

client trampoline_get_client(trampoline t)
{
    return t->c;
}


/*===================================
          trampoline_get_id
   Return the ID in the trampoline
===================================*/

int trampoline_get_id(trampoline t)
{
    return t->num_id;
}
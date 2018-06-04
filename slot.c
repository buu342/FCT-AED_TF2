#include <stdlib.h>
#include "configuration.h"
#include "fila.h"
#include "client.h"
#include "slot.h"


/*===================================
           Global Variables
===================================*/

struct _slot
{
    client c;
    int num_id;
};


/*===================================
             slot_create
  Allocate memory for a slot in the
                queue
===================================*/

slot slot_create(client c, int num_id)
{
    // Allocate memory for the queue
    slot s = (slot) malloc(sizeof(struct _slot));

    // Make sure we managed to allocate memory.
    if (s == NULL) 
        return NULL;

    // Set the variables and return him
    s->c = c;
    s->num_id = num_id;
    return s;
}


/*===================================
            slot_destroy
     Free memory used by a slot
===================================*/

void slot_destroy(slot s)
{
    free(s);
}


/*===================================
          slot_destroy_all
    Free memory used by all slots
===================================*/

void slot_destroy_all(void* s)
{
    slot_destroy((slot) s);
}


/*===================================
          slot_get_client
 Return the client in the queue slot
===================================*/

client slot_get_client(slot s)
{
    return s->c;
}


/*===================================
             slot_get_id
   Return the ID in the queue slot
===================================*/

int slot_get_id(slot s)
{
    return s->num_id;
}
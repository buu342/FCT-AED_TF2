#include <stdlib.h>
#include "configuration.h"
#include "fila.h"
#include "client.h"
#include "slot.h"

struct _slot
{
    client c;
    int num_id;
};

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

void slot_destroy(slot s)
{
    free(s);
}

client slot_get_client(slot s)
{
    return s->c;
}

int slot_get_id(slot s)
{
    return s->num_id;
}
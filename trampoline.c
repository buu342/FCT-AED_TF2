#include <stdlib.h>
#include "configuration.h"
#include "client.h"
#include "trampoline.h"

struct _trampoline
{
    client c;
    int num_id;
};

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

void trampoline_set_client(trampoline t, client c, int num_id)
{
    t->c = c;
    t->num_id = num_id;
}

bool trampoline_empty(trampoline t)
{
    return (t->c == NULL);
}

client trampoline_get_client(trampoline t)
{
    return t->c;
}
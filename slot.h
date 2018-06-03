#ifndef _H_QUEUE
#define _H_QUEUE

    typedef struct _slot * slot;

    slot    slot_create(client c, int num_id);
    void    slot_destroy(slot s);
    void    slot_destroy_all(void* s);
    client  slot_get_client(slot s);
    int     slot_get_id(slot s);

#endif
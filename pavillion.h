#ifndef _H_PAVILLION
#define _H_PAVILLION

    typedef struct _pavillion * pavillion;

    pavillion   pavillion_create();
    void        pavillion_destroy(pavillion p);

    float       pavillion_get_cash(pavillion p);

    status      pavillion_add_client(pavillion p, char* name, int num_id, int num_tax);
    client      pavillion_remove_client(pavillion p, int num_id);
    bool        pavillion_exists_client(pavillion p, int num_id);
    client      pavillion_get_client(pavillion p, int num_id);

#endif
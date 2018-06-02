#ifndef _H_PAVILION
#define _H_PAVILION

    typedef struct _pavilion * pavilion;

    pavilion    pavilion_create();
    void        pavilion_destroy(pavilion p);
    void        pavilion_close(pavilion p);

    float       pavilion_get_cash(pavilion p);
    void        pavilion_set_cash(pavilion p, float cash);

    status      pavilion_add_client(pavilion p, char* name, int num_id, int num_tax);
    client      pavilion_remove_client(pavilion p, int num_id);
    bool        pavilion_exists_client(pavilion p, int num_id);
    client      pavilion_get_client(pavilion p, int num_id);
    int         pavilion_count_clients(pavilion p);

    bool        pavilion_exists_food(pavilion p, char item);
    food        pavilion_get_food(pavilion p, char item);

    void        pavilion_display_clients(pavilion p);

#endif
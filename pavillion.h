#ifndef _PAVILLION
#define _PAVILLION

    typedef struct _pavillion * pavillion;

    pavillion create_pavillion();
    void destroy_pavillion();
    int pavillion_add_client(int num_id, int num_tax, char* name);

#endif
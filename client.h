#ifndef _H_CLIENT
#define _H_CLIENT

    typedef struct _client * client;

    client  client_create(char* name, int num_tax);
    void    client_destroy(client c);
    void    client_destroy_all(void* c);

    char*   client_get_name(client c);
    int     client_get_num_tax(client c);
    int     client_get_time(client c);
    float   client_get_bill(client c);
    char    client_get_location(client c);

    void    client_set_time(client c, int time);
    void    client_set_bill(client c, float bill);
    void    client_set_location(client c, char location);

#endif
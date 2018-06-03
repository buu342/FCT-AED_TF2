#ifndef _H_TRAMPOLINE
#define _H_TRAMPOLINE

    typedef struct _trampoline * trampoline;

    trampoline  trampoline_create();
    void        trampoline_destroy(trampoline t);
    void        trampoline_destroy_all(void* t);
    bool        trampoline_empty(trampoline t);

    client      trampoline_get_client(trampoline t);
    int         trampoline_get_id(trampoline t);

    void        trampoline_set_client(trampoline t, client c, int num_id);

    void        trampoline_remove_client(trampoline t);

#endif
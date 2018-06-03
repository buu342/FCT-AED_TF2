#ifndef _H_TRAMPOLINE
#define _H_TRAMPOLINE

    typedef struct _trampoline * trampoline;

    trampoline  trampoline_create();
    void        trampoline_set_client(trampoline t, client c, int num_id);
    bool        trampoline_empty(trampoline t);
    client      trampoline_get_client(trampoline t);

#endif
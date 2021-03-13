#ifndef _CYCLE_H_INCLUDED_
#define _CYCLE_H_INCLUDED_

#include "config.h"

#define gc_malloc malloc
#define gc_free   free
#define string(str) {sizeof(str) - 1,(u_char*)str}



struct net_s {
    void                  ****conf_ctx;


    connection_t         *free_connections;
    uint_t                free_connection_n;

    module_t             **modules;
    uint_t               modules_n;

    listening_t          *listening;

    uint_t                connection_n;

    connection_t         *connections;
    event_t              *read_events;
    event_t              *write_events;

    int_t                is_daemon;
    log_t                *log;

};


struct module_s{
    int_t           (*init_master)();

    int_t           (*init_module)(net_t *net);

    int_t           (*init_process)(net_t *net);
    int_t           (*init_thread)(net_t *net);
    void                (*exit_thread)(net_t *net);
    void                (*exit_process)(net_t *net);

    void                (*exit_master)(net_t *net);
};

extern module_t event_core_module;
extern module_t http_core_module;
extern module_t* modules[];

net_t *init_net();

#endif /* _CYCLE_H_INCLUDED_ */

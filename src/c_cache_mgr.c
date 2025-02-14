#include "c_cache.h"
#include <stdio.h>
#define MAX_CACHE_SIZE 10

c_cache_manager_t *global_cache_manager;

// Singleton cache manager initializer
c_cache_manager_t* get_cache_manager() {
    if (!global_cache_manager) {
        global_cache_manager = (c_cache_manager_t*)malloc(sizeof(c_cache_manager_t));
        if (!global_cache_manager) {
            perror("Cache Manager allocation failed");
            return NULL;
        }
        global_cache_manager->create = create_cache;
        global_cache_manager->set = add_entry;
        global_cache_manager->delete = remove_entry;
        global_cache_manager->get = get_entry;
        global_cache_manager->flush = flush_cache;
        global_cache_manager->destroy = destroy_cache;

        global_cache_manager->cache = global_cache_manager->create(MAX_CACHE_SIZE);
        if(global_cache_manager->cache == NULL) {
            perror("Cache creation failed");
            free(global_cache_manager);
            global_cache_manager = NULL;
            return NULL;
        }
    }
    return global_cache_manager;
}

void destroy_cache_manager() {
    if (global_cache_manager) {
        global_cache_manager->destroy(global_cache_manager->cache);
        //destroy_cache(global_cache_manager->cache);
        free(global_cache_manager);
        global_cache_manager = NULL;
    }
}
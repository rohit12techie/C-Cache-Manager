#ifndef C_CACHE_H
#define C_CACHE_H

#include <stdlib.h>

typedef struct cache_node_ {
    int key_;
    void *value_;
} cache_node_t;

typedef struct cache_list_ {
    cache_node_t *node_;
    struct cache_list_ *next;
    struct cache_list_ *prev;
}cache_list_t;

typedef struct cache_ {
    cache_list_t *head;
    cache_list_t *tail;
    int counter_;
    int size_;
} cache_t;

cache_t* create_cache(int size);
void add_entry(cache_t *cache, const int key, const char *value);
void remove_entry(cache_t *cache, const int key);
void *get_entry(cache_t *cache, const int key);
void flush_cache(cache_t *cache);
void destroy_cache(cache_t *cache);


typedef struct c_cache_manager {
    cache_t *cache;
    cache_t* (*create)(int size);
    void (*set)(cache_t *cache, const int key, const char *value);
    void (*delete)(cache_t *cache, const int key);
    void *(*get)(cache_t *cache, const int key);
    void (*flush)(cache_t *cache);
    void (*destroy)(cache_t *cache);
} c_cache_manager_t;

c_cache_manager_t *global_cache_manager = NULL;

c_cache_manager_t* get_cache_manager();
void destroy_cache_manager();

#endif // C_CACHE_H
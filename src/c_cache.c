#include "c_cache.h"
#include <stdio.h>
static void handle_null_cache(cache_t *cache, int key, void *value);
static void handle_empty_cache_list(cache_t *cache, int key, void *value);
static void handle_non_empty_cache_list(cache_t *cache, int key, void *value);

static cache_list_t* create_cache_list_node(int key, void *value) {
    cache_list_t *new_node = (cache_list_t *)malloc(sizeof(cache_list_t));
    if(new_node == NULL) {
        return NULL;
    }

    new_node->node_ = (cache_node_t *)malloc(sizeof(cache_node_t));
    if(new_node->node_ == NULL) {
        free(new_node);
        return NULL;
    }

    new_node->node_->key_ = key;
    new_node->node_->value_ = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

static void handle_null_cache(cache_t *cache, int key, void *value) {
    if(cache == NULL) {
        return;
    }

    cache = (cache_t *)malloc(sizeof(cache_t));
    if (cache == NULL) {
        return;
    }

    handle_empty_cache_list(cache, key, value);
}

static void handle_empty_cache_list(cache_t *cache, int key, void *value) {
    if(cache == NULL || cache->head != NULL) {
        return;
    }

    cache_list_t *new_entry = create_cache_list_node(key, value);
    if(new_entry == NULL) {
        return;
    }

    cache->head = new_entry;
    cache->tail = new_entry;
    cache->counter_++;
}

static void handle_non_empty_cache_list(cache_t *cache, int key, void *value) {
    if (cache == NULL || cache->head == NULL) {
        return;
    }

    cache_list_t *new_entry = create_cache_list_node(key, value);
    if(new_entry == NULL) {
        return;
    }

    if(cache->counter_ >= cache->size_) {
        cache_list_t *free_entry = cache->tail;
        cache->tail = cache->tail->prev;
        free_entry->prev->next = NULL;
        free_entry != NULL ? free (free_entry) : NULL;
        cache->counter_--;
    }

    new_entry->next = cache->head;
    cache->head = new_entry;
    cache->counter_++;
}

static void handle_new_entry(cache_t *cache, int key, void *value) {
    if(cache == NULL) {
        return handle_null_cache(cache, key, value);
    }

    if(cache->head == NULL) {
        return handle_empty_cache_list(cache, key, value);
    }

    return handle_non_empty_cache_list(cache, key, value);
}

static void handle_remove_entry(cache_t *cache, int key) {
    if(cache == NULL || cache->head == NULL) {
        return;
    }

    cache_list_t *ptrv = cache->head;
    while(ptrv != NULL) {
        if(ptrv->node_->key_ == key) {
            if(ptrv->prev != NULL) {
                ptrv->prev->next = ptrv->next;
            } else {
                cache->head = ptrv->next;
            }

            if(ptrv->next != NULL) {
                ptrv->next->prev = ptrv->prev;
            } else {
                cache->tail = ptrv->prev;
            }

            free(ptrv->node_);
            free(ptrv);
            cache->counter_--;
            return;
        }
        ptrv = ptrv->next;
    }
}

cache_t* create_cache(int size) {
    cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
    if (cache == NULL) {
        return NULL;
    }
    cache->head = NULL;
    cache->tail = NULL;
    cache->counter_ = 0;
    cache->size_ = size;
    return cache;
}

void add_entry(cache_t *cache, const int key, const char *value) {
    if(cache == NULL) {
        return;
    }
    return handle_new_entry(cache, key, (void *)value);
}

void remove_entry(cache_t *cache, const int key) {
    if(cache == NULL) {
        return;
    }
    return handle_remove_entry(cache, key);
}

void flush_cache(cache_t *cache) {
    if(cache == NULL) {
        return;
    }

    cache_list_t *ptrv = cache->head;
    while(ptrv != NULL) {
        cache_list_t *next = ptrv->next;
        free(ptrv->node_);
        free(ptrv);
        ptrv = next;
    }

    cache->head = NULL;
    cache->tail = NULL;
    cache->counter_ = 0;
}

void* get_entry(cache_t *cache, const int key) {
    if(cache == NULL) {
        return NULL;
    }

    cache_list_t *ptrv = cache->head;
    while(ptrv != NULL) {
        if(ptrv->node_->key_ == key) {
            return ptrv->node_->value_;
        }
        ptrv = ptrv->next;
    }
    return NULL;
}

void destroy_cache(cache_t *cache) {
    if(cache == NULL) {
        return;
    }
    flush_cache(cache);
    free(cache);
}





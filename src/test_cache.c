#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_cache.h"

char input[4][10] = {"test", "test2", "test3", "test4"};

void test_get() {
    c_cache_manager_t *cache_manager = get_cache_manager();
    if(cache_manager == NULL) {
        printf("%s::failed\n", __func__);
        return;
    }

    int true = 0;
    int i = 0;
    for(i = 0; i < 3; i++) {
        int key = (i+1)*2;
        if (strcmp(input[i], (char*)(cache_manager->get(cache_manager->cache, key))) == 0) {
            true++;
        }
    }
    if(true != 3) {
        printf("%s::failed\n", __func__);
        return;
    }
    printf("%s::passed\n", __func__);
}

void test_remove() {
    c_cache_manager_t *cache_manager = get_cache_manager();
    if(cache_manager == NULL) {
        printf("%s::failed\n", __func__);
        return;
    }
    cache_manager->delete(cache_manager->cache, 2);
    if(cache_manager->get(cache_manager->cache, 2) != NULL) {
        printf("%s::failed\n", __func__);
        return;
    }
    printf("%s::passed\n", __func__);
}

void test_set() {
    c_cache_manager_t *cache_manager = get_cache_manager();
    if(cache_manager == NULL) {
        printf("%s::failed\n", __func__);
        return;
    }

    int i = 0;
    for(i = 0; i < 3; i++) {
        cache_manager->set(cache_manager->cache, (i+1)*2, input[i]);
    }

    int true = 0;
    for(i = 0; i < 3; i++) {
        int key = (i+1)*2;
        if (strcmp(input[i], (char*)(cache_manager->get(cache_manager->cache, key))) == 0) {
            true++;
        }
    }
    if(true != 3) {
        printf("%s::failed\n", __func__);
        return;
    }
    printf("%s::passed\n", __func__);
}

void test_flush() {
    c_cache_manager_t *cache_manager = get_cache_manager();
    if(cache_manager == NULL) {
        printf("%s::failed\n", __func__);
        return;
    }
    cache_manager->flush(cache_manager->cache);
    if(cache_manager->get(cache_manager->cache, 2) != NULL) {
        printf("%s::failed\n", __func__);
        return;
    }
    printf("%s::passed\n", __func__);
}

void test_cache_creation() {
    c_cache_manager_t *cache_manager = get_cache_manager();
    if(cache_manager == NULL) {
        printf("%s::failed\n", __func__);
        return;
    }
    printf("%s::passed\n", __func__);
}



int main() {
    test_cache_creation();
    test_set();
    test_get();
    test_remove();
    test_flush();
    destroy_cache_manager();
    return 0;
}
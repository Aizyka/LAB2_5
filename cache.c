#include "header.h"
#include <stdlib.h>
#include <string.h>

Cache* cache_create() {
    Cache* cache = malloc(sizeof(Cache));
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

void cache_delete(Cache* cache) {
    CacheEntry* current = cache->head;
    while (current != NULL) {
        CacheEntry* next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    free(cache);
}

void cache_add(Cache* cache, const char* key, const char* value) {
    // Check if the key is already in the cache
    CacheEntry* current = cache->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Key already in cache, update value and move to front
            free(current->value);
            current->value = strdup(value);
            if (current != cache->head) {
                current->prev->next = current->next;
                if (current == cache->tail) {
                    cache->tail = current->prev;
                } else {
                    current->next->prev = current->prev;
                }
                current->prev = NULL;
                current->next = cache->head;
                cache->head->prev = current;
                cache->head = current;
            }
            return;
        }
        current = current->next;
    }
    // Key not in cache, add new entry to front
    CacheEntry* entry = malloc(sizeof(CacheEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->prev = NULL;
    entry->next = cache->head;
    if (cache->head != NULL) {
        cache->head->prev = entry;
    } else {
        cache->tail = entry;
    }
    cache->head = entry;
    if (cache->size == MAX_CACHE_SIZE) {
        // Cache full, remove least recently used entry from tail
        CacheEntry* to_remove = cache->tail;
        cache->tail = to_remove->prev;
        if (cache->tail != NULL) {
            cache->tail->next = NULL;
        } else {
            cache->head = NULL;
        }
        free(to_remove->key);
        free(to_remove->value);
        free(to_remove);
    } else {
        cache->size++;
    }
}

char* cache_get(Cache* cache, const char* key) {
    // Find the key in the cache and move it to front
    CacheEntry* current = cache->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (current != cache->head) {
                current->prev->next = current->next;
                if (current == cache->tail) {
                    cache->tail = current->prev;
                } else {
                    current->next->prev = current->prev;
                }
                current->prev = NULL;
                current->next = cache->head;
                cache->head->prev = current;
                cache->head = current;
            }
            return current->value;
        }
        current = current->next;
    }

    return search_ip_file(cache, "dns.txt", key);
}
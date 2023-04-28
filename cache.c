#include "header.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash(const char* str, unsigned int seed) {
    unsigned int hash = seed;
    while (*str) {
        hash = hash * 101 + *str++;
    }
    return hash;
}

unsigned int hash_function(const char* key, int table_size) {
    return hash(key, 0) % table_size;
}

HashTable* hashtable_create() {
    HashTable* table = malloc(sizeof(HashTable));
    table->size = MAX_CACHE_SIZE;
    table->table = malloc(sizeof(HashEntry*) * table->size);
    for (int i = 0; i < table->size; i++) {
        table->table[i] = NULL;
    }
    return table;
}

void hashtable_delete(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashEntry* current = table->table[i];
        while (current != NULL) {
            HashEntry* next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            current = next;
        }
    }
    free(table->table);
    free(table);
}

int internal_lookup(HashTable* table, const char* key) {
    int founded = 0;
    unsigned int index = hash_function(key, table->size);
    HashEntry* current = table->table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if(is_valid_ip(current->value) == 1)
                printf("Found IP: %s\n", current->value);
            else
                hashtable_lookup(table, current->value);
            founded = 1;
        }
        current = current->next;
    }
    return founded;
}

void hashtable_lookup(HashTable* table, const char* key) {

    if(internal_lookup(table,key) == 0) {
        search_ip_file(table, "dns.txt", key);
    }
    else{
        return;
    }
    internal_lookup(table,key);
}

void hashtable_add(HashTable* table, const char* key, const char* value) {
    unsigned int index = hash_function(key, table->size);
    HashEntry* entry = malloc(sizeof(HashEntry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->prev = NULL;
    entry->next = table->table[index];
    if (table->table[index] != NULL) {
        table->table[index]->prev = entry;
    }
    table->table[index] = entry;
}
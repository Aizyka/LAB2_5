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
    table->size = MAX_HASH_SIZE;
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
    unsigned int index = hash_function(key, table->size);
    HashEntry* current = table->table[index];
    HashEntry* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("Found IP: %s\n", current->value);
            if (prev != NULL) {
                prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = prev;
                }
                current->prev = NULL;
                current->next = table->table[index];
                table->table[index]->prev = current;
                table->table[index] = current;
            }
            HashEntry* next = current->next;
            while (next != NULL) {
                next->prev = next->prev == current ? NULL : current;
                current->next = next;
                current->prev = prev;
                prev = current;
                current = next;
                next = next->next;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void hashtable_lookup(HashTable* table, const char* key) {
    if(internal_lookup(table,key) == 0) {
        search_ip_file(table, "dns.txt", key, NULL);
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
    int count = 0;
    if(table->table[index] != NULL) {
        HashEntry* current = table->table[index];
        while(current != NULL) {
            count++;
            if(count >= MAX_CACHE_SIZE-1 && current->next != NULL) {
                printf("REMOVING: %s\n", current->next->key);
                free(current->next);
                current->next = NULL;
                break;
            }
            current = current->next;
        }
    }
    entry->prev = NULL;
    entry->next = table->table[index];
    if (table->table[index] != NULL) {
        table->table[index]->prev = entry;
    }
    table->table[index] = entry;
}
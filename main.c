#include "header.h"
#include <stdio.h>

void find_ip(HashTable* cache) {
    char* dns;
    printf("Write DNS: ");
    scanf("%s", dns);
    /*const char* result = hashtable_lookup(cache, dns);
    if(result != NULL && is_valid_ip(result) == 0) {
        result = hashtable_lookup(cache, result);
    }
    if(result == NULL)
        printf("No IP found\n");
    else
        printf("Found IP: %s", result);*/
    hashtable_lookup(cache, dns);
}

void add_ip(HashTable* cache) {
    char* dns;
    char* ip;
    printf("Write DNS: ");
    scanf("%s", dns);
    printf("Write IP: ");
    scanf("%s", ip);
    add_dns_entry("dns.txt", dns, ip);
}

void get_all_ip(HashTable* cache) {
    char* ip;
    printf("Write IP: ");
    scanf("%s", ip);
    print_dns_names_by_ip(cache,ip,"dns.txt");
}

void write_all_entries(HashTable* cache) {

    printf("\n");
    HashEntry * current = NULL;
    for(int i = 0; i < cache->size; i++) {
        current = cache->table[i];
        while (current != NULL) {
            printf("%s %s\n", current->key, current->value);
            current = current->next;
        }
    }

}


int main() {
    HashTable* cache = hashtable_create();
    int work = 1;
    while(work) {
        int choice;

        printf("\nMenu:\n1 - Find\n2 - Add\n3 - Get all IP\n4 - Clear Cache\n5 - Write Cache\n6 - Exit\nYour choice: ");
        while(scanf("%d", &choice) == 0 || choice < 1 || choice > 6) {
            printf("\nInvalid choice\nYour choice: ");
            rewind(stdin);
        }

        switch (choice) {
            case 1:
                find_ip(cache);
                break;
            case 2:
                add_ip(cache);
                break;
            case 3:
                get_all_ip(cache);
                break;
            case 4:
                hashtable_delete(cache);
                cache = hashtable_create();
                break;
            case 5:
                write_all_entries(cache);
                break;
            default:
                work = 0;
                break;
        }
    }
    hashtable_delete(cache);
    return 0;
}
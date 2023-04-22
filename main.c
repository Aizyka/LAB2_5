#include "header.h"
#include <stdio.h>

void find_ip(Cache* cache) {
    char* dns;
    printf("Write DNS: ");
    scanf("%s", dns);
    const char* result = cache_get(cache, dns);
    if(result == NULL)
        printf("No IP found\n");
    else
        printf("Found IP: %s", result);
}

void add_ip(Cache* cache) {
    char* dns;
    char* ip;
    printf("Write DNS: ");
    scanf("%s", dns);
    printf("Write IP: ");
    scanf("%s", ip);
    add_dns_entry("dns.txt", dns, ip);
}

void write_all_entries(Cache* cache) {

    CacheEntry* current = cache->head;
    if(current == NULL) {
        printf("No entries in cache\n");
    }
    else {
        printf("All entries in cache:\n");
    }
    while (current != NULL) {
        printf("%s %s\n", current->key, current->value);
        current = current->next;
    }
}


int main() {
    Cache* cache = cache_create();
    int work = 1;
    while(work) {
        int choice;

        printf("\nMenu:\n1 - Find\n2 - Add\n3 - Clear Cache\n4 - Write Cache\n5 - Exit\nYour choice: ");
        while(scanf("%d", &choice) == 0 || choice < 1 || choice > 5) {
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
                cache_delete(cache);
                cache = cache_create();
                break;
            case 4:
                write_all_entries(cache);
                break;
            default:
                work = 0;
                break;
        }
    }
    if(cache != NULL)
        cache_delete(cache);
    return 0;
}
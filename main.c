#include "header.h"
#include <stdio.h>

void find_ip(HashTable* cache) {
    char dns[100];
    printf("Write DNS: ");
    scanf("%99s", dns);
    hashtable_lookup(cache, dns);
}

void add_ip() {
    char dns[100];
    char ip[16];
    printf("Write DNS: ");
    scanf("%99s", dns);
    printf("Write IP: ");
    scanf("%15s", ip);
    add_dns_entry("dns.txt", dns, ip);
}

void get_all_ip() {
    char ip[16];
    printf("Write IP: ");
    scanf("%15s", ip);
    print_dns_names_by_ip(ip,"dns.txt");
}

void write_all_entries(const HashTable* cache) {
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
                add_ip();
                break;
            case 3:
                get_all_ip();
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
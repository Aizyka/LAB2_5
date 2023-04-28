#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void search_ip_file(HashTable* cache, const char* filename, const char* dns) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* found_dns = strtok(line, " \n");
        if (strcmp(found_dns, dns) == 0) {
            char* ip = strtok(NULL, " \n");
            hashtable_add(cache, dns, ip);
        }
    }
    fclose(file);
    return;
}



void print_dns_names_by_ip(HashTable* cache, const char* ip_address, const char* filename) {
    /*CacheEntry* current = cache->head;
    while (current != NULL) {
        if (strstr(current->value, ip_address) != NULL) {
            printf("%s\n", current->key);
        }
        current = current->next;
    }*/

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        char* found_dns = strtok(line, " \n");
        char* ip = strtok(NULL, " \n");
        if (strcmp(ip, ip_address) == 0) {
            printf("%s\n", found_dns);
        }
    }
    fclose(file);
}

int is_valid_ip(const char* ip) {
    int octet = 0, num_octets = 0;
    char* line = strdup(ip);
    char* ptr = strtok(line, ".\n");
    while (ptr != NULL) {
        num_octets++;
        octet = atoi(ptr);
        if (octet < 0 || octet > 255 || (num_octets == 1 && octet == 0)) {
            return 0;
        }
        ptr = strtok(NULL, ".\n");
    }
    if (num_octets != 4) {
        return 0;
    }
    return 1;
}

void add_dns_entry(const char* filename, const char* dns_name, const char* ip_address) {
    if(is_valid_ip(ip_address) == 0) {
        printf("Invalid IP Address\n");
        return;
    }

    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error: could not open file '%s'\n", filename);
        return;
    }

    char line[1024];
    char* current_dns;
    while (fgets(line, sizeof(line), file) != NULL) {
        current_dns = strtok(line, " ");
        if (strcmp(current_dns, dns_name) == 0) {
            printf("Error: IP address '%s' already exists in file\n", dns_name);
            fclose(file);
            return;
        }
    }

    fseek(file, 0, SEEK_END);
    fprintf(file, "\n%s %s", dns_name, ip_address);
    fclose(file);
}
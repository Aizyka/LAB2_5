#ifndef APP_HEADER_H
#define APP_HEADER_H
#define MAX_CACHE_SIZE 1000

typedef struct HashEntry {
    char* key;
    char* value;
    struct HashEntry* prev;
    struct HashEntry* next;
} HashEntry;

typedef struct HashTable {
    int size;
    HashEntry** table;
} HashTable;

unsigned int hash_function(const char* key, int table_size);
HashTable* hashtable_create();
void hashtable_delete(HashTable* table);
void hashtable_lookup(HashTable* table, const char* key);
void hashtable_add(HashTable* table, const char* key, const char* value);
void add_dns_entry(const char* filename, const char* dns_name, const char* ip_address);
void search_ip_file(HashTable* cache, const char* filename, const char* dns);
void print_dns_names_by_ip(const char* ip_address, const char* filename);
int is_valid_ip(const char* ip);
#endif //APP_HEADER_H

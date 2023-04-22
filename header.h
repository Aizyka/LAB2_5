#ifndef APP_HEADER_H
#define APP_HEADER_H
#define MAX_CACHE_SIZE 1000
typedef struct CacheEntry {
    char* key;
    char* value;
    struct CacheEntry* prev;
    struct CacheEntry* next;
} CacheEntry;

typedef struct Cache {
    int size;
    CacheEntry* head;
    CacheEntry* tail;
} Cache;

Cache* cache_create();
void cache_delete(Cache* cache);
void cache_add(Cache* cache, const char* key, const char* value);
char* cache_get(Cache* cache, const char* key);
void add_dns_entry(const char* filename, const char* dns_name, const char* ip_address);
char* search_ip_file(Cache* cache, const char* filename, const char* dns);
#endif //APP_HEADER_H

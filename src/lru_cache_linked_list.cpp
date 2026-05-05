#include "lru_cache_linked_list.hpp"

LRUCacheLinkedList::LRUCacheLinkedList(int capacity) : m_capacity(capacity) {}

int LRUCacheLinkedList::get(int key) {
    auto it = cacheMap.find(key);
    if (it == cacheMap.end()) {
        return -1;
    }
    lruList.splice(lruList.begin(), lruList, it->second);
    return it->second->second;
}

void LRUCacheLinkedList::put(int key, int value) {
    (void)key;
    (void)value;
}

#pragma once
#include <unordered_map>
#include <list>

class LRUCacheLinkedList {
public:
    LRUCacheLinkedList(int capacity);
    int get(int key);
    void put(int key, int value);

private:
    int m_capacity;
    using CacheEntry = std::pair<int, int>;
    using ListIt = std::list<CacheEntry>::iterator;

    std::list<CacheEntry> lruList;
    std::unordered_map<int, ListIt> cacheMap;
};

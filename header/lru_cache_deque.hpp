#pragma once
#include <deque>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(int capacity);
    int get(int key);
    void put(int key, int value);
private:
    int m_capacity;
    std::deque<int> m_lru; // in m_lru we store keys
    std::unordered_map<int,int> m_kv;
};

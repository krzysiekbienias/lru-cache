#include "lru_cache_deque.hpp"

#include <deque>
#include <unordered_map>


LRUCache::LRUCache(int capacity) : m_capacity(capacity) {
};


int LRUCache::get(int key) {
    auto it = m_kv.find(key);
    if (it == m_kv.end()) return -1;

    auto pos = std::find(m_lru.begin(), m_lru.end(), key);
    if (pos != m_lru.end()) {
        m_lru.erase(pos);
    }
    m_lru.push_front(key);
    return it->second;
}


void LRUCache::put(int key, int value) {
    // 1) key exists
    auto it = m_kv.find(key); //um has find in interface and you have O(1) time complexity
    if (it != m_kv.end()) {
        it->second = value; //refresh value,
        //then we need to remove from the current position and put on the front of the deque
        //important! deque finds an element using linear scan from std::find, O(n) always
        auto pos = std::find(m_lru.begin(), m_lru.end(), key);
        if (pos != m_lru.end()) m_lru.erase(pos);
        m_lru.push_front(key);
        return;
    }
    //2 ) key is new but we have already reached capacity
    if (m_kv.size() >= m_capacity) {
        int lruKey = m_lru.back();
        m_lru.pop_back(); //remove from deque from the end and make space
        m_kv.erase(lruKey); // remove the key that was last in deque.
    }

    m_kv[key] = value;
    m_lru.push_front(key);
}

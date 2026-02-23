Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

`LRUCache(int capacity)` Initialize the LRU cache with positive size capacity.

* `int get(int key)` Return the value of the key if the key exists, otherwise return $-1$.
* `void put(int key, int value)` Update the value of the key if the key exists. Otherwise, add the key-value pair to the
  cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

The functions get and put must each run in $O(1)$ average time complexity.

### Game Plan (`deque<int>`)

> 🇵🇱 Trzymasz dane w `unordered_map<int,int> m_kv` (szybkie lookup wartości) oraz osobno kolejkę “ostatnio używane” w
`m_lru`, gdzie przód oznacza MRU, a tył LRU. W `get()` robisz poprawny wzorzec LRU: najpierw find w mapie, a przy
> trafieniu odświeżasz kolejność przez usunięcie klucza z bieżącej pozycji w `m_lru` i `push_front(key)`. W `put()`
> rozróżniasz dwa przypadki: jeśli klucz istnieje, aktualizujesz wartość i też przerzucasz go na front; jeśli klucz jest
> nowy i cache jest pełny, usuwasz element z końca `m_lru` i ten sam klucz z mapy, po czym wstawiasz nową parę i ustawiasz
> ją jako MRU. Semantycznie wszystko jest spójne; jedyny “słaby punkt” testów LRU to złożoność — `std::find` + `erase` w
`deque` kosztuje $O(n)$, więc przy dużych danych standardowo przechodzi się na list + iterator map dla $O(1)$.

> 🇬🇧 You keep values in `unordered_map<int,int> m_kv` for fast key→value lookup and maintain recency in `m_lru`, where
> the front is MRU and the back is LRU. In `get()`, you follow the correct LRU pattern: find in the map, and on a hit you
> refresh recency by removing the key from its current position in `m_lru` and pushing it to the front. In `put()`, you
> handle two cases: if the key exists, update the value and promote it to MRU; if it’s a new key and the cache is at
> capacity, evict `m_lru.back()` and erase the same key from the map, then insert the new pair and mark it MRU.
> Correctness-wise this is consistent; the typical remaining risk in LRU test suites is performance—`std::find` + middle
> erase on a deque is $O(n)$, so the canonical upgrade is list and key→iterator for true $O(1)$.
>
| ⏱️Time Complexity | 💾 Space complexity | 
|-------------------|---------------------| 
| $O(n)$            | $O(1)$              |
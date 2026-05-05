#include <gtest/gtest.h>
#include "lru_cache_deque.hpp"


TEST(LRUCacheDequeTests, GetMissingReturnsMinusOne) {
    LRUCacheDeque cache(2);

    EXPECT_EQ(cache.get(42), -1);
    EXPECT_EQ(cache.get(-7), -1);
}

TEST(LRUCacheDequeTests, PutThenGetReturnsValue) {
    LRUCacheDeque cache(2);

    cache.put(1, 100);
    cache.put(2, 200);

    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
}

TEST(LRUCacheDequeTests, EvictsLeastRecentlyUsedOnCapacityOverflow) {
    // capacity = 2
    LRUCacheDeque cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    // Cache is full: [2 (MRU?) ,1] depends on your ordering, but both are present.

    cache.put(3, 30); // should evict key=1 (LRU), assuming 2 is more recent than 1 due to insertion order

    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheDequeTests, GetMakesKeyMostRecentAffectingNextEviction) {
    // capacity = 2
    LRUCacheDeque cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    // Access key=1, now key=2 should become LRU.
    EXPECT_EQ(cache.get(1), 10);

    cache.put(3, 30); // should evict key=2 now

    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheDequeTests, PutOnExistingKeyUpdatesValueAndRefreshesRecency) {
    // capacity = 2
    LRUCacheDeque cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    // Update key=1, should become most recent, value updated
    cache.put(1, 111);

    cache.put(3, 30); // should evict key=2 (now LRU)

    EXPECT_EQ(cache.get(1), 111);
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheDequeTests, CapacityOneAlwaysKeepsOnlyMostRecentKey) {
    LRUCacheDeque cache(1);

    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);

    cache.put(2, 20); // evicts 1
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);

    // Access 2, still only 2
    EXPECT_EQ(cache.get(2), 20);

    cache.put(3, 30); // evicts 2
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
}
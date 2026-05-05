#include <gtest/gtest.h>
#include "lru_cache_linked_list.hpp"

TEST(LRUCacheLinkedListTests, GetMissingReturnsMinusOne) {
    LRUCacheLinkedList cache(2);

    EXPECT_EQ(cache.get(42), -1);
    EXPECT_EQ(cache.get(-7), -1);
}

TEST(LRUCacheLinkedListTests, PutThenGetReturnsValue) {
    LRUCacheLinkedList cache(2);
 
    cache.put(1, 100);
    cache.put(2, 200);

    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
}

TEST(LRUCacheLinkedListTests, EvictsLeastRecentlyUsedOnCapacityOverflow) {
    LRUCacheLinkedList cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);  // should evict key=1

    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheLinkedListTests, GetRefreshesRecencyAndChangesEvictionCandidate) {
    LRUCacheLinkedList cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    EXPECT_EQ(cache.get(1), 10);  // key=1 becomes most recent

    cache.put(3, 30);  // key=2 should be evicted

    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheLinkedListTests, PutOnExistingKeyUpdatesValueAndRefreshesRecency) {
    LRUCacheLinkedList cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(1, 111);  // update + refresh key=1
    cache.put(3, 30);   // key=2 should be evicted

    EXPECT_EQ(cache.get(1), 111);
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheLinkedListTests, CapacityOneAlwaysKeepsOnlyMostRecentKey) {
    LRUCacheLinkedList cache(1);

    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);

    cache.put(2, 20);  // evicts 1
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);

    cache.put(3, 30);  // evicts 2
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheLinkedListTests, MultipleEvictionsPreserveOnlyNewestKeys) {
    LRUCacheLinkedList cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(4, 40);  // evict 1
    cache.put(5, 50);  // evict 2

    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
    EXPECT_EQ(cache.get(4), 40);
    EXPECT_EQ(cache.get(5), 50);
}

TEST(LRUCacheLinkedListTests, AccessPatternAffectsLaterEvictions) {
    LRUCacheLinkedList cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(2), 20);

    cache.put(4, 40);  // key=3 should be evicted

    EXPECT_EQ(cache.get(3), -1);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(2), 20);
    EXPECT_EQ(cache.get(4), 40);
}

TEST(LRUCacheLinkedListTests, SupportsNegativeKeysAndValues) {
    LRUCacheLinkedList cache(2);

    cache.put(-1, -10);
    cache.put(-2, -20);

    EXPECT_EQ(cache.get(-1), -10);
    EXPECT_EQ(cache.get(-2), -20);
}

TEST(LRUCacheLinkedListTests, RepeatedGetDoesNotCorruptState) {
    LRUCacheLinkedList cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(1), 10);

    cache.put(3, 30);  // key=2 should be evicted

    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(3), 30);
}

//
// Created by rozhin on 30.05.23.
//

#include <gtest/gtest.h>
#include <lru_cache.h>

TEST(lru, simple_put) {
    lc::lru_cache<char, char> lru(6);
    lru.put('A', 'a');
    lru.put('B', 'b');
    lru.put('C', 'c');

    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');
}

TEST(lru, advanced_put) {
    lc::lru_cache<char, char> lru(6);
    lru.put('A', 'a');
    lru.put('B', 'b');
    lru.put('C', 'c');
    auto status = lru.put('D', 'd');

    lc::lru_cache<char, char>::status expected_status = lc::lru_cache<char, char>::status::bad;
    ASSERT_EQ(expected_status, status);
    
    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');
}

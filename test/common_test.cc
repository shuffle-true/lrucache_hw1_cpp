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

TEST(lru, not_alloc_case) {
    lc::lru_cache<char, char> lru(6);
    lru.put('A', 'a');
    lru.put('B', 'b');
    lru.put('C', 'c');
    
    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');

    lru.put('A', 'c');
    lru.put('B', 'b');
    lru.put('C', 'a');

    ASSERT_EQ(lru.get('A'), 'c');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'a');
}

TEST(lru, no_alloc_case_with_random_value) {
    lc::lru_cache<char, char> lru(6);
    lru.put('A', 'a');
    lru.put('B', 'b');
    lru.put('C', 'c');
    
    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');

    lru.put('A', 'D');
    lru.put('B', 'E');
    lru.put('C', 'F');

    ASSERT_EQ(lru.get('A'), 'D');
    ASSERT_EQ(lru.get('B'), 'E');
    ASSERT_EQ(lru.get('C'), 'F');
}

//
// Created by rozhin on 30.05.23.
//

#include <gtest/gtest.h>
#include "lru_cache.h"
#include <random>

TEST(lru, simple_put_get) {
    lc::lru_cache<char, char> lru(4);
    ASSERT_EQ(lc::status::ok, lru.put('A', 'a'));
    ASSERT_EQ(lc::status::ok, lru.put('B', 'b'));
    ASSERT_EQ(lc::status::ok, lru.put('C', 'c'));

    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');

    ASSERT_EQ(lru.get('D'), char());

    ASSERT_EQ(lc::status::ok, lru.put('D', 'd'));
    ASSERT_EQ(lru.get('D'), 'd');
}

TEST(lru, key_update) {
    lc::lru_cache<char, char> lru(4);
    ASSERT_EQ(lc::status::ok, lru.put('A', 'a'));
    ASSERT_EQ(lc::status::ok, lru.put('B', 'b'));
    ASSERT_EQ(lc::status::ok, lru.put('C', 'c'));

    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');

    ASSERT_EQ(lc::status::ok, lru.put('A', 'A'));
    ASSERT_EQ(lc::status::ok, lru.put('B', 'B'));
    ASSERT_EQ(lc::status::ok, lru.put('C', 'C'));

    ASSERT_EQ(lru.get('A'), 'A');
    ASSERT_EQ(lru.get('B'), 'B');
    ASSERT_EQ(lru.get('C'), 'C');
}


TEST(lru, eviction) {
    lc::lru_cache<char, char> lru(3);
    ASSERT_EQ(lc::status::ok, lru.put('A', 'a'));
    ASSERT_EQ(lc::status::ok, lru.put('B', 'b'));
    ASSERT_EQ(lc::status::ok, lru.put('C', 'c'));

    ASSERT_EQ(lru.get('A'), 'a');
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');

    ASSERT_EQ(lc::status::ok, lru.put('D', 'd'));

    ASSERT_EQ(lru.get('A'), char()); // такого ключа больше нет
    ASSERT_EQ(lru.get('B'), 'b');
    ASSERT_EQ(lru.get('C'), 'c');
    ASSERT_EQ(lru.get('D'), 'd');

    ASSERT_EQ(lc::status::ok, lru.put('X', 'x'));
    ASSERT_EQ(lc::status::ok, lru.put('Y', 'y'));
    ASSERT_EQ(lc::status::ok, lru.put('Z', 'z'));

    ASSERT_EQ(lru.get('B'), char());
    ASSERT_EQ(lru.get('C'), char());
    ASSERT_EQ(lru.get('D'), char());
    ASSERT_EQ(lru.get('X'), 'x');
    ASSERT_EQ(lru.get('Y'), 'y');
    ASSERT_EQ(lru.get('Z'), 'z');
}

TEST(lru, erase) {
    lc::lru_cache<char, char> lru(3);
    ASSERT_EQ(lc::status::ok, lru.put('A', 'a'));
    ASSERT_EQ(lc::status::ok, lru.put('B', 'b'));

    ASSERT_EQ(lru.buffer.size(), 2);
    ASSERT_EQ(lru.map.size(), 2);

    lru.erase('A');
    ASSERT_EQ(lru.buffer.size(), 1);
    ASSERT_EQ(lru.map.size(), 1);

    lru.erase('B');
    ASSERT_EQ(lru.buffer.size(), 0);
    ASSERT_EQ(lru.map.size(), 0);

    /*
     * Такого ключа нет, проверим что сантизайер не ругается
     */
    lru.erase('C');
    ASSERT_EQ(lru.buffer.size(), 0);
    ASSERT_EQ(lru.map.size(), 0);
}

TEST(lru, stress) {
    lc::lru_cache<std::string, int64_t> lru(100);
    std::random_device rng;

    for (size_t i = 0; i < 1000000; i++) {
        int64_t rng_int = rng();
        if (rng_int % 2 == 0) {
            ASSERT_EQ(lc::status::ok, lru.put(std::to_string(rng() % 500), rng_int % 42));
        } else {
            lru.get(std::to_string(rng() % 500));
        }
    }
}

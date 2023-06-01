//
// Created by rozhin on 30.05.23.
//

#ifndef LRUCACHE_HW1_CPP_LRU_CACHE_H
#define LRUCACHE_HW1_CPP_LRU_CACHE_H

#include <cstddef>
#include <unordered_map>
#include <list>

namespace lc {

template<typename Key,
         typename Value>
class lru_cache {
public:
    using key_type = Key;
    using value_type = Value;

    enum class status { ok, bad };
public:
    lru_cache(size_t max_size) {
        max_size_ = max_size > 1 ? max_size : 10 * (sizeof(key_type) + sizeof(value_type));
    }
    ~lru_cache() = default;

    status put(const key_type& key, const value_type& value) {
        if (compute_size() >= max_size_) {
            return status::bad;
        }

        /*
         *  Ищется ключ для решения - вставить новый или обновить.
         *  Если ключ обновляется, то аллокации не происходит.
         */
        auto map_it = map.find(key);
        if (map_it != map.end()) {
            buffer.splice(buffer.end(), buffer, map_it->second);
        } else {
            buffer.push_back(value);
        }
        map[key] = --buffer.end();
        return status::ok;
    }

    void erase(const key_type& key) noexcept {
        buffer.erase(map[key]);
        map.erase(key);
    }

    value_type get(const key_type& key) {
        return *map[key];
    }

private:
    size_t compute_size() {
        return sizeof(value_type) * buffer.size() + sizeof(key_type) * map.size();
    }

    /*
     * Deprecated
     */
    bool contains(const key_type& key) {
        if (map.find(key) != map.end()) {
            return true;
        }
        return false;
    }

public:
    size_t max_size_;
    std::list<value_type> buffer;
    std::unordered_map<key_type,
                        typename std::list<value_type>::iterator> map;
};

}

#endif //LRUCACHE_HW1_CPP_LRU_CACHE_H

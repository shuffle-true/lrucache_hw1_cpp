//
// Created by rozhin on 30.05.23.
//

#ifndef LRUCACHE_HW1_CPP_LRU_CACHE_H
#define LRUCACHE_HW1_CPP_LRU_CACHE_H

#include <cstddef>
#include <unordered_map>
#include <list>

namespace lc {

enum class status { ok, bad };

template<typename Key,
         typename Value>
class lru_cache {
public:
    using key_type = Key;
    using value_type = Value;

public:
    explicit lru_cache(size_t max_size) {
        max_size_ = max_size;
    }
    ~lru_cache() = default;

    status put(const key_type& key, const value_type& value) {
        // FIXME: вроде это не нужно. Никогда не сработает.

        /*
         * Если ключ существует, не аллоцируем.
         * Просто обновим последнее обращение и значение.
        */

        auto map_it = map.find(key);
        if (map_it != map.end()) {
            buffer.splice(buffer.end(), buffer, map_it->second);
            map_it->second->second = value;
            return status::ok;
        }

        /*
         * Алгоритм LRU.
         * Удаляем наиболее неиспользуемую пару ключ-значение.
         */

        if (buffer.size() == max_size_) {
            auto last_key = buffer.begin()->first;
            buffer.pop_front();
            map.erase(last_key);
        }
        buffer.push_back({key, value});
        map[key] = --buffer.end();
        return status::ok;
    }

    void erase(const key_type& key) noexcept {
        auto map_it = map.find(key);
        if (map_it != map.end()) {
            buffer.erase(map_it->second);
            map.erase(key);
        }
    }

    value_type get(const key_type& key) noexcept {
        auto map_it = map.find(key);
        if (map_it != map.end()) {
            buffer.splice(buffer.end(), buffer, map_it->second);
            return map_it->second->second;
        } else {
            return value_type();
        }
    }

private:
    /*
     * Remove
     */
    inline size_t compute_size(const key_type& key, const value_type& value) {
        return sizeof(key) + sizeof(value);
    }

public:
    size_t max_size_;
    std::list<std::pair<key_type, value_type>> buffer;
    std::unordered_map<key_type,
                        typename std::list<std::pair<key_type, value_type>>::iterator> map;
};

}

#endif //LRUCACHE_HW1_CPP_LRU_CACHE_H

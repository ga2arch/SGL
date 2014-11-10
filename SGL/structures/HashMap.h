//
//  HashMap.h
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__HashMap__
#define __SGL__HashMap__

#include <string>
#include <utility>

template <typename K, typename V>
class HashNode {
public:
    
    explicit HashNode(): key(nullptr), value(nullptr) {};
    explicit HashNode(const K* key, V* value): key(key),
                                               value(value) {}
    
    const K* key;
    V* value;
};

template <typename T>
struct Hasher {
    static size_t hash(T t);
};

template <typename T>
struct STLHasher: Hasher<T> {
    static size_t hash(T t) {
        std::hash<T> h_fun;
        return h_fun(t);
    }
};

class Linear {
    
public:
    template <typename K, typename V, class H, size_t SIZE>
    void put(const K&& key, V&& value, HashNode<K, V>(&values)[SIZE]) {
        auto h = H::hash(key);
        size_t i = h % SIZE;
        
        if (values[i].key == nullptr || *values[i].key == key) {
            values[i] = HashNode<K,V>(&key, &value);
        } else {
            
            auto fun =  [](const K* k1)
            { return k1 == nullptr; };
            
            i = linear_search<K, V, decltype(fun), SIZE>(i, fun, values);
            
            values[i] = HashNode<K,V>(&key, &value);
        }

    }
    
    template <typename K, typename V, typename H, size_t SIZE>
    HashNode<K, V>* find(const K&& key, HashNode<K, V>(&values)[SIZE]) {
        auto h = STLHasher<K>::hash(key);
        size_t i = h % SIZE;

        if (values[i].key == nullptr)
            throw std::invalid_argument("Error: key not found");
        
        if (*values[i].key == key)
            return &values[i];
        
        if (values[i].key != nullptr) {
            auto fun = [&key](const K* k1)
            { if (k1 != nullptr) return *k1 == key;
                else return false; };
            
            i = linear_search<K, V, decltype(fun), SIZE>(i, fun, values);
            
            return &values[i];
        }
        
        throw std::invalid_argument("Error: key not found");
    }
    
private:
    template <typename K, typename V, typename C, size_t SIZE>
    size_t linear_search(size_t i, C f, HashNode<K, V>(&values)[SIZE]) {
        
        for (int j=0; ;j++) {
            auto b = i;
            
            i += j*j;
            b -= j*j;
            
            if (i < SIZE && f(values[i].key)) return i;
            if (b < SIZE && f(values[b].key)) return b;
            
            if (b >= SIZE && i >= SIZE)
                throw std::out_of_range("Error: key not found");
        }
    }
    
};

template <typename K, typename V, size_t SIZE,
          class TYPE = Linear,
          class H = STLHasher<K>>
class HashMap {
    
public:
    explicit HashMap() {};
    
    void put(const K&& key, V&& value) {
        static_assert(std::is_base_of<Hasher<K>, H>::value, "Invalid Hasher");
        type.template put<K,V,H,SIZE>(std::move(key), std::move(value), values);
    };
    
    V& get(const K&& key) {
        static_assert(std::is_base_of<Hasher<K>, H>::value, "Invalid Hasher");
        return *type.template find<K,V,H,SIZE>(std::move(key), values)->value;
    }
    
    void remove(const K& key) {
        auto node = type.template find<K,V,H,SIZE>(std::move(key), values);
        node->key = nullptr;
        node->value = nullptr;
    }
    
private:
    HashNode<K,V> values[SIZE];
    TYPE type;
    
};

#endif /* defined(__SGL__HashMap__) */

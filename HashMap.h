//
//  HashMap.h
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__HashMap__
#define __SGL__HashMap__

#include <iostream>
#include <stdio.h>
#include <string>
#include <functional>

template <typename K, typename V>
class HashNode {
public:
    
    explicit HashNode(): key(nullptr), value(nullptr) {};
    explicit HashNode(const K* key, V* value): key(key), value(value) {}
    
    const K* key;
    V* value;
};

template <typename K, typename V, size_t SIZE>
class HashMap {
    
public:
    explicit HashMap() {};
    
    void put(const K& key, V& value) {
        std::hash<K> h_fun;
        auto h = h_fun(key);
       
        size_t i = h % SIZE;
        
        if (values[i].key == nullptr || *values[i].key == key) {
            values[i] = HashNode<K,V>(&key, &value);
        } else {
            i = linear_search(i, nullptr, values,
                              [](const K* k1, const K* k2)
                                { return k1 == k2; });
            
            values[i] = HashNode<K,V>(&key, &value);
        }
    };
    
    V* get(const K& key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;

        if (values[i].key == nullptr)
            throw std::out_of_range("Error: key not found");
        
        if (*values[i].key == key)
            return values[i].value;
        
        if (values[i].key != nullptr) {
            i = linear_search(i, &key, values,
                              [](const K* k1, const K* k2)
                                { return *k1 == *k2; });
            return values[i].value;
        }
        
        throw std::out_of_range("Error: key not found");
    }
    
private:
    HashNode<K,V> values[SIZE];
    
    size_t linear_search(size_t i,
                         const K* key,
                         HashNode<K, V> (&values)[SIZE],
                         bool (*f)(const K* k1, const K* k2)) {
        
        for (int j=0; ;j++) {
            auto b = i;
            
            i += j*j;
            b -= j*j;
            
            if (i < SIZE && f(values[i].key, key)) return i;
            if (b < SIZE && f(values[i].key, key)) return b;
            
            if (b >= SIZE && i >= SIZE)
                throw std::out_of_range("Error: key not found");
        }
    }
    
};

#endif /* defined(__SGL__HashMap__) */

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
    explicit HashNode(const K* key, const V* value): key(key), value(value) {}
    
    const K* key;
    const V* value;
};

template <typename K>
size_t f(K& k) {
    std::hash<K> h_fun;
    if (k % 2 == 0) return 3669149634153089213;
    return h_fun(k);
}

template <typename K, typename V, size_t SIZE>
class HashMap {
    
public:
    explicit HashMap() {};
    
    void put(const K& key, const V& value) {
        std::hash<K> h_fun;
        auto h = h_fun(key);
       
        size_t i = h % SIZE;
        
        if (values[i].key == nullptr || *values[i].key == key) {
            values[i] = HashNode<K,V>(&key, &value);
        } else {
            for (int j=1; ;j++) {
                auto b = i;
                
                i += j*j;
                b -= j*j;
                
                if (b < SIZE && values[b].key == nullptr) break;
                if (i < SIZE && values[i].key == nullptr) break;
                
                if (b >= SIZE && i >= SIZE)
                    throw std::out_of_range("Error: no space avaliable");
                
            }
            values[i] = HashNode<K,V>(&key, &value);
        }
    };
    
    const V* get(const K& key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;

        if (values[i].key == nullptr)
            throw std::out_of_range("Error: key not found");
        
        if (*values[i].key == key)
            return values[i].value;
        
        if (values[i].key != nullptr) {
            
            for (int j=0; ;j++) {
                auto b = i;
                
                i += j*j;
                b -= j*j;
                
                if (b < SIZE && *values[b].key == key) break;
                if (i < SIZE && *values[i].key == key) break;
                
                if (b >= SIZE && i >= SIZE)
                    throw std::out_of_range("Error: key not found");
            }
            
            return values[i].value;
        }
        
        throw std::out_of_range("Error: key not found");
    }
    
private:
    HashNode<K,V> values[SIZE];
    
};

#endif /* defined(__SGL__HashMap__) */

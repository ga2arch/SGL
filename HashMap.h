//
//  HashMap.h
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__HashMap__
#define __SGL__HashMap__

#include <stdio.h>
#include <string>
#include <functional>

template <typename K, typename V>
class HashNode {
public:
    
    explicit HashNode(): key(nullptr), value(nullptr) {};
    explicit HashNode(K* key, V* value): key(key), value(value) {}
    
    K* key;
    V* value;
};

template <typename K, typename V, size_t SIZE>
class HashMap {
    
public:
    explicit HashMap() {};
    
    void put(K& key, V& value) {
        std::hash<K> h_fun;
        auto h = h_fun(key);
        auto i = h % SIZE;
        
        if (values[i].key == nullptr || *values[i].key == key) {
            values[i] = HashNode<K,V>(&key, &value);
        } else {
            for (int j=1; ;j++) {
                auto b = i;
                
                i += j;
                b -= j;
                
                if (values[i].key == nullptr) break;
                if (values[b].key == nullptr) break;
                
                if (i >= SIZE)
                    throw std::out_of_range("Error: no space avaliable");
            }
            values[i] = HashNode<K,V>(&key, &value);
        }
    };
    
    V* get(K& key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;

        if (*values[i].key == key) {
            return values[i].value;
            
        }
        
        if (values[i].key != nullptr) {
            for (int j=0; ;j++) {
                auto b = i;
                
                i += j;
                b -= j;
                
                if (*values[i].key == key) break;
                if (*values[b].key == key) break;
                
                if (i >= SIZE)
                    throw std::out_of_range("Error: no key found");
            }
            
            return values[i].value;
        }
        
        throw std::out_of_range("Error: no key found");
    }
    
private:
    HashNode<K,V> values[SIZE];
    
};

#endif /* defined(__SGL__HashMap__) */

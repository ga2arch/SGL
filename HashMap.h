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
            int k = 1;
            for (int j=1; values[i].key != nullptr; j++) {
                i += k * j;
                k = -k;
                
                if (i >= SIZE)
                    throw std::out_of_range("Error: no space avaliable");
            }
            values[i] = HashNode<K,V>(&key, &value);
        }
    };
    
    V* get(K& key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;

        int k = 1;
        for (int j=1; values[i].key != nullptr; j++) {
            i += k * j;
            k = -k;
            
            if (i >= SIZE)
                throw std::out_of_range("Error: no space avaliable");
        }
        
        return values[i].value;
    }
    
private:
    HashNode<K,V> values[SIZE];
    
};

#endif /* defined(__SGL__HashMap__) */

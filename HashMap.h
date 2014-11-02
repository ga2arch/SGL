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

template <typename K, typename V, size_t SIZE>
class HashMap {
    
public:
    explicit HashMap() {};
    
    void put(K key, V value) {
        std::hash<K> h_fun;
        auto h = h_fun(key);
        auto i = h % SIZE;
        values[i] = value;
    };
    
    V get(K key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;
        return values[i];
    }
    
private:
    V values[SIZE];
    
};

#endif /* defined(__SGL__HashMap__) */

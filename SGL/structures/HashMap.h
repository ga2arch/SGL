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


template <typename K, typename V, size_t SIZE>
class Linear {
    
public:
    explicit Linear(HashNode<K, V>(&values)[SIZE]): values(values) {};
    
    void put(const K&& key, V&& value) {
        std::hash<K> h_fun;
        auto h = h_fun(key);
        
        size_t i = h % SIZE;
        
        if (values[i].key == nullptr || *values[i].key == key) {
            values[i] = HashNode<K,V>(&key, &value);
        } else {
            
            auto fun =  [](const K* k1)
            { return k1 == nullptr; };
            
            i = linear_search<decltype(fun)>(i, fun);
            
            values[i] = HashNode<K,V>(&key, &value);
        }

    }
    
    HashNode<K, V>* find(const K& key) {
        std::hash<K> h_fun;
        auto i = h_fun(key) % SIZE;
        
        if (values[i].key == nullptr)
            throw std::invalid_argument("Error: key not found");
        
        if (*values[i].key == key)
            return &values[i];
        
        if (values[i].key != nullptr) {
            auto fun = [&key](const K* k1)
            { if (k1 != nullptr) return *k1 == key;
                else return false; };
            
            i = linear_search<decltype(fun)>(i, fun);
            
            return &values[i];
        }
        
        throw std::invalid_argument("Error: key not found");
    }
    
    template <typename C>
    size_t linear_search(size_t i, C f) {
        
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
    
private:
    HashNode<K, V>(&values)[SIZE];

};

template <typename K, typename V, size_t SIZE,
         template <typename,typename,size_t> class TYPE = Linear>

class HashMap {
    
public:
    explicit HashMap(): type(values) {};
    
    void put(const K&& key, V&& value) {
        type.put(std::move(key), std::move(value));
    };
    
    V& get(const K& key) {
        return *type.find(key)->value;
    }
    
    void remove(const K& key) {
        auto node = find(key);
        node->key = nullptr;
        node->value = nullptr;
    }
    
private:
    HashNode<K,V> values[SIZE];
    TYPE<K, V, SIZE> type;
    
};

#endif /* defined(__SGL__HashMap__) */

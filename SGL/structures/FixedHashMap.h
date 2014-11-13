//
//  HashMap.h
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__HashMap__
#define __SGL__HashMap__

#include <memory>
#include <string>
#include <utility>
#include <exception>
#include "Functions.h"

//TODO: Handle collision

namespace sgl { namespace structures {

    template <typename K, typename V>
    struct HashNode {
        
        K key;
        V value;
        
        HashNode() {};
        HashNode(K key_, V value_): key(key_), value(value_) {};
        HashNode(K&& key_, V&& value_): key(std::move(key_)), value(std::move(value_)) {};

        HashNode(HashNode<K,V>&& o): key(std::move(o.key)), value(std::move(o.value)) {};
        HashNode(const HashNode<K,V>& o): key(o.key), value(o.value) {};
        
        HashNode<K,V>& operator=(HashNode<K,V>&& o) {
            key = std::move(o.key);
            value = std::move(o.value);
            
            return *this;
        }
        
        HashNode<K,V>& operator=(const HashNode<K,V>& o) {
            key = o.key;
            value = o.value;
            
            return *this;
        }
        
    };
    
    template <typename K, typename V, size_t SIZE>
    class FixedHashMap {
        
    public:
        FixedHashMap() {};
        
        void put(const K key, const V value) {
            auto node = make_unique<HashNode<K,V>>(std::move(key), std::move(value));

            auto h = h_fun(key);
            size_t i = h % SIZE;
            
            if (data_[i] == nullptr || data_[i]->key == key)
                data_[i] = std::move(node);
            
            else {
                for (int j=0; ;j++) {
                    auto b = i;
                    
                    i += j*j;
                    b -= j*j;
                    
                    if (i < SIZE && !data_[i]) data_[i] = std::move(node);
                    if (b < SIZE && !data_[b]) data_[b] = std::move(node);
                    
                    if (b >= SIZE && i >= SIZE)
                        throw std::out_of_range("Error: key not found");
                }
            }
        }
        
        V& get(const K& key) {
            auto h = h_fun(key);
            size_t i = h % SIZE;
            
            if (data_[i] == nullptr)
                throw std::invalid_argument("Error: Key not found");
            
            if (data_[i]->key == key)
                return data_[i]->value;
            
            for (int j=0; ;j++) {
                auto b = i;
                
                i += j*j;
                b -= j*j;
                
                if (i < SIZE && data_[i] && data_[i]->key == key) return data_[i]->value;
                if (b < SIZE && data_[b] && data_[b]->key == key) return data_[b]->value;
                
                if (b >= SIZE && i >= SIZE)
                    throw std::out_of_range("Error: key not found");
            }
            
            throw std::invalid_argument("ERROR");
        }
        
        V&& remove(const K& key) {
            auto h = h_fun(key);
            size_t i = h % SIZE;
            
            if (data_[i] == nullptr)
                throw std::invalid_argument("Error: Key not found");
            
            if (data_[i]->key == key) {
                V&& v = std::move(data_[i]->value);
                data_[i].reset();
                return std::move(v);
            }
            
            throw std::invalid_argument("ERROR");
            
        }
        
    private:
        std::hash<K> h_fun;
        std::unique_ptr<HashNode<K, V>> data_[SIZE];
    };
    
}}

#endif /* defined(__SGL__HashMap__) */

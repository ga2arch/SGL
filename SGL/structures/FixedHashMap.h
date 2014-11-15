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
#include "Allocator.h"
#include <cassert>

using namespace sgl::memory;

namespace sgl { namespace structures {

    template <typename K, typename V >
    struct HashNode {
        
        K key;
        V value;
        
        HashNode() {};
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
     
    template <typename K,
              typename V,
              size_t SIZE,
              class Allocator = Linear<HashNode<K, V>>>
    class FixedHashMap {
        
    public:
        FixedHashMap() {};
        ~FixedHashMap() {
            for (auto& node: data_) {
                if (!node) continue;
                reinterpret_cast<HashNode<K, V>*>(node)->~HashNode<K, V>();
                auto ptr = reinterpret_cast<void*>(node);
                allocator.dealloc(ptr);
            }
        }
        
        void put(K key, V value) {
            void* mem;
            assert(allocator.alloc(mem));
            
            auto node = new (mem) HashNode<K,V>(std::move(key),std::move(value));
            
            auto h = h_fun(key);
            size_t i = h % SIZE;
            
            if (!data_[i] || data_[i]->key == key)
                data_[i] = std::move(node);
            else {
                for (int j=0; ;j++) {
                    size_t b = i;
                    
                    i += j*j;
                    b -= j*j;
                    
                    if (i < SIZE && !data_[i]) { data_[i] = std::move(node); return; }
                    if (b < SIZE && !data_[b]) { data_[b] = std::move(node); return; }
                    
                    if (b >= SIZE && i >= SIZE)
                        throw std::out_of_range("Error: not enough space");
                }
            }
        }
        
        V& get(const K& key) {
            auto i = find(key);
            return data_[i]->value;
        }
        
        V pop(const K& key) {
            auto i = find(key);
            
            auto v = std::forward<V>(data_[i]->value);
            data_[i].reset();
            return v;
        }
        
        void remove(const K& key) {
            auto i = find(key);
            
            data_[i].reset();
        }
        
    private:
        Allocator allocator;
        std::hash<K> h_fun;
        HashNode<K, V>* data_[SIZE] = {nullptr};
        
        size_t find(const K& key) {
            auto h = h_fun(key);
            size_t i = h % SIZE;
            
            if (data_[i] == nullptr)
                throw std::invalid_argument("Error: Key not found");
            
            if (data_[i]->key == key)
                return i;
            
            for (int j=0; ;j++) {
                auto b = i;
                
                i += j*j;
                b -= j*j;
                
                if (i < SIZE && data_[i] && data_[i]->key == key) return i;
                if (b < SIZE && data_[b] && data_[b]->key == key) return b;
                
                if (b >= SIZE && i >= SIZE)
                    throw std::out_of_range("Error: Key not found");
            }
        }
    };
    
}}

#endif /* defined(__SGL__HashMap__) */

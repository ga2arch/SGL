//
//  Allocator.h
//  SGL
//
//  Created by Gabriele Carrettoni on 15/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__Allocator__
#define __SGL__Allocator__

#include <stdio.h>
#include "Memory.h"

namespace sgl { namespace memory {
    
    template <size_t NUM, size_t SIZE>
    class Pool {
        
    public:
        Pool(): mem(allocate_aligned(NUM*SIZE, 16)) {};
        ~Pool() { free_aligned(mem); };
        
        bool alloc(void*& ptr) {
            if (used == NUM) return false;
            
            auto address = reinterpret_cast<uintptr_t>(mem) + used*SIZE;
            ptr = std::move(reinterpret_cast<void*>(address));
            used++;
            return true;
        }
        
    private:
        void* mem;
        size_t used = 0;
        
    };
    
    template <typename T = unsigned char>
    class List {
        
    public:
        ~List() {
            auto node = list.head.next;
            while(node) {
                auto temp = node->next;
                reinterpret_cast<T*>(node)->~T();
                auto ptr = reinterpret_cast<void*>(node);
                free_aligned(ptr);
                node = temp;
            }
        }
        
        bool alloc(void*& ptr) {
            auto node = new Node(allocate_aligned(sizeof(T), 16));
            list.push_back(node);
            
            ptr = node->ptr;
            current++;
            return true;
        }
        
    private:
        struct Node: public structures::Link<Node> {
            void* ptr;
            
            Node(void* ptr): ptr(ptr) {};
        };
        
        structures::LinkedList<Node> list;
        
        size_t current = 0;
        
    };
    
    template <class Type>
    class Allocator: public Type {
        
    public:
        Allocator(): Type() {};
        
        // Pool
        bool alloc(size_t bytes, void*& mem) {
            Type& allocator = *this;
            return allocator.alloc(bytes, mem);
        };
        
        // Stack
        bool alloc(void*& mem) {
            Type& allocator = *this;
            return allocator.alloc(mem);
        };
        
    };
    
}}

#endif /* defined(__SGL__Allocator__) */

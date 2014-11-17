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
#include "LinkedList.h"

using namespace sgl::structures;

namespace sgl { namespace memory {
    
    template <size_t NUM, size_t SIZE>
    class Pool {
        
    public:
        Pool(): mem(allocate_aligned(NUM*SIZE, 16)) {};
        ~Pool() { free_aligned(mem); };
        
        void* alloc() {
            if (used == NUM) return nullptr;
            
            auto address = reinterpret_cast<uintptr_t>(mem) + used*SIZE;
            used++;
            return reinterpret_cast<void*>(address);
        }
        
    private:
        void* mem;
        size_t used = 0;
        
    };
    
    template <typename T = unsigned char>
    class List {
        
    public:
        ~List() {
            auto lk = list.head.next;
            while(lk) {
                auto temp = lk->next;
                auto node = reinterpret_cast<Node*>(lk);
                node->ptr->~T();
                auto ptr = reinterpret_cast<void*>(node->ptr);
                free_aligned(ptr);
                lk = temp;
            }
        }
        
        void* alloc() {
            auto ptr = reinterpret_cast<T*>(allocate_aligned(sizeof(T), 16));
            auto node = new Node(std::move(ptr));
            list.push_back(node);
            
            current++;
            return node->ptr;
        }
        
    private:
        struct Node: public Link<Node> {
            T* ptr;
            
            Node(T*&& ptr): ptr(std::move(ptr)) {};
        };
        
        LinkedList<Node> list;
        
        size_t current = 0;
        
    };
    
    template <class Type>
    class Allocator: public Type {
        
    public:
        Allocator(): Type() {};
        ~Allocator() { ~Type(); };
        
        // Pool
        void* alloc(size_t bytes) {
            Type& allocator = *this;
            return allocator.alloc(bytes);
        };
        
        // Stack
        void* alloc() {
            Type& allocator = *this;
            return allocator.alloc();
        };
        
    };
    
}}

#endif /* defined(__SGL__Allocator__) */

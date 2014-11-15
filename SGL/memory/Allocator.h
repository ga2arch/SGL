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

        bool alloc(void*& output) {
            if (used == SIZE) return false;
            
            auto ptr = reinterpret_cast<uintptr_t>(mem) + used*SIZE;
            output = std::move(reinterpret_cast<void*>(ptr));
            used++;
            return true;
        }
        
    private:
        void* mem;
        size_t used = 0;
        
    };
    
    template <size_t SIZE>
    class Stack {
        
    public:
        ~Stack() {
            for (int i=0; i < current; i++)
                free_aligned(mem[i]);
        }
        
        bool alloc(size_t bytes, void*& ptr) {
            if (current == SIZE) return false;
            
            ptr = mem[current++] = allocate_aligned(bytes, 16);
            return true;
        }
        
        bool free_to_marker(size_t pos) {
            if (pos >= SIZE) return false;
            
            current = pos;
            for (int i=0; i < current; i++)
                free_aligned(mem[i]);
            
            return true;
        }
        
        size_t get_marker() {
            return current;
        }
        
    private:
        void* mem[SIZE];
        
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
        
        size_t get_marker() {
            Type& allocator = *this;
            return allocator.get_marker();
        };
            
        bool free_to_marker(size_t m) {
            Type& allocator = *this;
            return allocator.free_to_marker(m);
        }
        
    };
    
}}

#endif /* defined(__SGL__Allocator__) */

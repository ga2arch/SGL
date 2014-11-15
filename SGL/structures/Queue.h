//
//  Queue.h
//  SGL
//
//  Created by Gabriele Carrettoni on 10/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__Queue__
#define __SGL__Queue__

#include <stdio.h>
#include <LinkedList.h>
#include "Allocator.h"

using namespace sgl::memory;

namespace sgl { namespace structures {

    template <typename T, size_t SIZE, class Allocator = Allocator<Pool<SIZE, sizeof(T)>>>
    class Queue {
        
    public:
        explicit Queue() {}
        
        template <typename...Args>
        bool enqueue(Args&&...args) {
            void* mem;
            if (allocator.alloc(mem)) {
                auto lk = new (mem) T(std::forward<Args>(args)...);
                list.push_back(reinterpret_cast<Link<T>*>(lk));
                
                return true;
            } else
                return false;
        }
        
        T&& dequeue() {
            return list.remove_last();
        };
        
    private:
        Allocator allocator;
        LinkedList<T> list;
        
    };
    
}}

#endif /* defined(__SGL__Queue__) */

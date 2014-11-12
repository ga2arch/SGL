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
#include <PoolAllocator.h>

template <typename T>
class Queue {
    
public:
    explicit Queue(PoolAllocator& pool): pool(pool) {}
    
    void enqueue(const T& t) {
        auto lk = new (pool.get_block()) T(t);
        list.push_back(reinterpret_cast<Link<T>*>(lk));
    }
    
    void enqueue(T&& t) {
        auto lk = new (pool.get_block()) T(std::forward<T>(t));
        list.push_back(reinterpret_cast<Link<T>*>(lk));
    };
    
    template <typename ...Args>
    void emplace(Args&&... args) {
        auto lk = new (pool.get_block()) T(std::forward<T>(args)...);
        list.push_back(reinterpret_cast<Link<T>*>(lk));
    }
    
    T&& dequeue() {
        return list.remove_last();
    };
    
private:
    PoolAllocator& pool;
    LinkedList<T> list;
    
};

#endif /* defined(__SGL__Queue__) */

//
//  ProducerConsumerQueue.h
//  SGL
//
//  Created by Gabriele Carrettoni on 14/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef SGL_ProducerConsumerQueue_h
#define SGL_ProducerConsumerQueue_h

template <typename T>
class ProducerConsumerQueue {
    
public:
    ProducerConsumerQueue(size_t num): mem(static_cast<T*>(malloc(sizeof(T) * num))), size(num) {
        prod_index = cons_index = 0;
    }
    
    template <typename...Args>
    bool enqueue(Args&&... args) {
        
        auto write_index = prod_index.load(std::memory_order_relaxed);
        
        if (write_index == size) return false;
        
        new (&mem[prod_index]) T(std::forward<Args>(args)...);
        prod_index.store(write_index+1, std::memory_order_release);

        return true;
    }
    
    bool try_dequeue(T& output) {
        
        auto read_index = cons_index.load(std::memory_order_relaxed);
        auto write_index = prod_index.load(std::memory_order_acquire);
        
        if (read_index == write_index) return false;
        
        output = std::move(mem[read_index]);
        cons_index.store(read_index+1, std::memory_order_relaxed);
        
        return true;
    }
    
    ~ProducerConsumerQueue() {
        free(mem);
    }
    
private:
    T* mem;
    
    alignas(64) std::atomic<int> prod_index;
    alignas(64) std::atomic<int> cons_index;
    
    alignas(64) size_t size = 0;
};


#endif

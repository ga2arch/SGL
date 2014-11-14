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
    ProducerConsumerQueue() {
        first = last = new Node(nullptr);
        producer_lock = consumer_lock = false;
    }

    bool enqueue(T* t) {
        auto node = new Node(t);
        
        while (producer_lock.exchange(true)) {}
        
        last->next = node;
        last = node;
        
        producer_lock = false;
        return true;
    }
    
    bool dequeue(T& out) {
        while (consumer_lock.exchange(true)) {}

        if (first->next != nullptr) {
            auto old = first;
            first = first->next;
            auto value = first->value;
            first->value = nullptr;
            consumer_lock = false;
            
            out = *value;
            delete value;
            delete old;
            
            return true;
        } else
            return false;
    }
    
    ~ProducerConsumerQueue() {
        auto node = first->next;
        while (node) {
            auto temp = node->next;
            free(node);
            node = temp;
        }
    }
    
private:
    struct Node {
        Node* next;
        Node* prev;
        T* value;
        
        Node(T* value): value(value) {};
    };
    
    Node* first;
    Node* last;
    
    std::atomic<bool> producer_lock;
    std::atomic<bool> consumer_lock;
    
    size_t size = 0;
};

#endif

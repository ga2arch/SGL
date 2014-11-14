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
        producer_lock = consumer_lock = false;
    }

    void enqueue(T t) {
        auto node = new Node(t);
        
        while (consumer_lock.exchange(true)) {}
        
        if (head.next) {
            auto s = head.next;
            head.next = node;
            node->next = s;
            s->prev = node;
            
        } else {
            head.next = node;
            tail.prev = node;
        }
        
        consumer_lock = false;

    }
    
    T dequeue() {
        while (producer_lock.exchange(true)) {}

        if (tail.prev) {
            auto node = tail.prev;
            auto val = node->elem;
            
            tail.prev = node->prev;
            if (tail.prev)
                tail.prev->next = nullptr;
            else
                head.next = nullptr;
            
            producer_lock = false;
            free(node);
            
            return val;
        }
        throw ("Error");
    }
    
    ~ProducerConsumerQueue() {
        auto node = head.next;
        
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
        T elem;
        
        Node(): next(nullptr) {};
        Node(T elem): elem(elem) {};
    };
    
    Node head;
    Node tail;
    
    std::atomic<bool> producer_lock;
    std::atomic<bool> consumer_lock;
    
    size_t size = 0;
};

#endif

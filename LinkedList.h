//
//  LinkedList.h
//  SGL
//
//  Created by Gabriele Carrettoni on 31/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__LinkedList__
#define __SGL__LinkedList__

#include <stdio.h>

template <typename T>
struct Link {
    Link<T>* prev;
    Link<T>* next;
    
    T elem;
};

template <typename T>
class LinkedList {
    
public:
    Link<T> head;
    Link<T> tail;
    size_t size;
    
    ~LinkedList() {
        auto n = head.next;
        while (n) {
            auto next = n->next;
            free(n);
            n = next;
        }
    }
    
    void add_first(const T& elem) {
        auto lk = new Link<T>();
        lk->elem = elem;
        head.next = lk;
        tail.prev = lk;
        
        size++;
    }
    
    void push_front(const T& elem) {
        auto lk = new Link<T>();
        lk->elem = elem;
        
        auto s = head.next;
        head.next = lk;
        lk->next = s;
        s->prev = lk;
        
        size++;
    }
    
    void push_back(const T& elem) {
        auto lk = new Link<T>();
        lk->elem = elem;
        
        auto s = tail.prev;
        tail.prev = lk;
        lk->prev = s;
        s->next = lk;
        
        size++;
    }
    
};

#endif /* defined(__SGL__LinkedList__) */

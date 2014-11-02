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
};

template <typename T>
class LinkedList {
    
public:
    Link<T> head;
    Link<T> tail;
    size_t size;
    
    explicit LinkedList() {
        head.next = nullptr;
        tail.prev = nullptr;
    }
    
    void push_front(Link<T>* lk) {
        if (head.next) {
            auto s = head.next;
            head.next = lk;
            lk->next = s;
            s->prev = lk;
        } else {
            head.next = lk;
            tail.prev = lk;
        }
        
        size++;
    }
    
    void push_back(Link<T>* lk) {
        if (tail.prev) {
            auto p = tail.prev;
            tail.prev = lk;
            lk->prev = p;
            p->next = lk;
        } else {
            head.next = lk;
            tail.prev = lk;
        }
        
        size++;
    }
    
    void remove_last() {
        if (size > 0) {
            auto p = tail.prev->prev;
            tail.prev->prev->next = nullptr;
            tail.prev = p;
            
            size--;
            
        } else
            throw("Error: The list is empty.");
    }
    
    void remove(Link<T>* lk) {
        if (lk->next) {
            lk->next->prev = lk->prev;
        } else
            tail.prev = lk->prev;
        
        if (lk->prev) {
            lk->prev->next = lk->next;
        }
        else
            head.next = lk->prev;
        
        lk->prev = lk->next = nullptr;
    }
    
};

#endif /* defined(__SGL__LinkedList__) */

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
#include <ostream>
#include <utility>

namespace sgl { namespace structures {

    template <typename T>
    struct Link {
        Link<T>* prev = nullptr;
        Link<T>* next = nullptr;
        
        Link() {};
        Link(const Link<T>& t): prev(t.prev), next(t.next) {};
        Link(Link<T>&& t): prev(std::move(t.prev)), next(std::move(t.next)) {};
    };

    template <typename T>
    class LinkedList {
        
    public:
        Link<T> head;
        Link<T> tail;
        size_t size;
        
        explicit LinkedList(): size(0) {
            head.next = tail.prev = nullptr;
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
        
        T&& pop() {
            if (head.next) {
                auto lk = head.next;
                head.next = lk->next;
                head.prev = nullptr;
                
                size--;
                return std::move(*reinterpret_cast<T*>(lk));
            } else {
                throw std::out_of_range("Error: The list is empty");
            }
        }
        
        T&& remove_last() {
            if (tail.prev) {
                auto lk = tail.prev;
                tail.prev = lk->prev;
                
                size--;
                return std::move(*reinterpret_cast<T*>(lk));
            } else {
                throw std::out_of_range("Error: The list is empty");
            }
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
            
            size--;
        }
        
        //TODO remove_at(size_t pos)
    };
    
}}

#endif /* defined(__SGL__LinkedList__) */

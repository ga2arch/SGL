//
//  LinkedListTest.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "LinkedListTest.h"

TEST(LinkedList, PushBack) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);

    ls.push_back(&e1);
    ls.push_back(&e2);
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e2.value);
}

TEST(LinkedList, PushFront) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_front(&e2);
    
    ASSERT_EQ(((Elem*)ls.head.next)->value, e2.value);
}

TEST(LinkedList, Pop) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    
    Elem* e = ls.pop();
    
    ASSERT_EQ(e->value, e1.value);
}

TEST(LinkedList, RemoveLast) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    ls.remove_last();
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e1.value);
}

TEST(LinkedList, ThrowOnRemoveLastEmpty) {
    LinkedList<Elem> ls;

    ASSERT_THROW(ls.remove_last(), std::out_of_range);
}

TEST(LinkedList, Remove) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    ls.remove(&e2);
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e1.value);
}

TEST(LinkedList, RemoveAt) {
    LinkedList<Elem> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    ls.remove_at(0);
    
    ASSERT_EQ(((Elem*)ls.head.next)->value, e2.value);
}
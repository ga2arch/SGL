//
//  LinkedListTest.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "LinkedListTest.h"
#include "LinkedList.h"
#include <gtest/gtest.h>

using namespace sgl::structures;

class Elem: public Link<int> {
public:
    explicit Elem(int v): value(v) {};
    int value;
};

TEST(LinkedList, PushBack) {
    LinkedList<int> ls;
    
    Elem e1(10);
    Elem e2(2);

    ls.push_back(&e1);
    ls.push_back(&e2);
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e2.value);
}

TEST(LinkedList, PushFront) {
    LinkedList<int> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_front(&e2);
    
    ASSERT_EQ(((Elem*)ls.head.next)->value, e2.value);
}

TEST(LinkedList, RemoveLast) {
    LinkedList<int> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    ls.remove_last();
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e1.value);
}

TEST(LinkedList, ThrowOnRemoveLastEmpty) {
    LinkedList<int> ls;

    ASSERT_THROW(ls.remove_last(), std::out_of_range);
}

TEST(LinkedList, Remove) {
    LinkedList<int> ls;
    
    Elem e1(10);
    Elem e2(2);
    
    ls.push_back(&e1);
    ls.push_back(&e2);
    ls.remove(&e2);
    
    ASSERT_EQ(((Elem*)ls.tail.prev)->value, e1.value);
}
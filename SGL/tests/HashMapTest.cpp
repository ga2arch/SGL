//
//  HashMapTest.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "HashMap.h"
#include "HashMapTest.h"
#include <gtest/gtest.h>

TEST(HashMapTest, ThrowsOnNotFoundKey) {
    HashMap<int, std::string, 10> m;
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
}

TEST(HashMapTest, PutGetKeyByValue) {
    HashMap<int, std::string, 10> m;
    std::string v("ciao");
    m.put(10, v);
    
    ASSERT_EQ(m.get(10), v);
}

TEST(HashMapTest, PutGetKeyByPointer) {
    HashMap<int, std::string*, 10> m;
    auto v = new std::string("ciao");
    
    m.put(10, v);

    ASSERT_EQ(*m.get(10), *v);
    delete v;
}

TEST(HashMapTest, RemoveKeyByValue) {
    HashMap<int, std::string, 10> m;
    std::string v("ciao");
    m.put(10, v);
    m.remove(10);
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
}

TEST(HashMapTest, RemoveKeyByPointer) {
    HashMap<int, std::string*, 10> m;
    std::string* v = new std::string("ciao");
    
    m.put(10, v);
    m.remove(10);
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
    
    delete v;
}





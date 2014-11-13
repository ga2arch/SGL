//
//  FixedHashMapTest.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 02/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "FixedHashMap.h"
#include "FixedHashMapTest.h"
#include <gtest/gtest.h>

using namespace sgl::structures;

TEST(FixedHashMapTest, ThrowsOnNotFoundKey) {
    FixedHashMap<int, std::string, 10> m;
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
}

TEST(FixedHashMapTest, PutGetKeyByValue) {
    FixedHashMap<int, std::string, 10> m;
    std::string v("ciao");
    m.put(10, std::move(v));
    
    ASSERT_EQ(m.get(10), std::string("ciao"));
}

TEST(FixedHashMapTest, PutGetKeyByPointer) {
    FixedHashMap<int, std::string*, 10> m;
    auto v = new std::string("ciao");
    
    m.put(10, std::move(v));

    ASSERT_EQ(*m.get(10), *v);
    delete v;
}

TEST(FixedHashMapTest, RemoveKeyByValue) {
    FixedHashMap<int, std::string, 10> m;
    std::string v("ciao");
    m.put(10, std::move(v));
    m.remove(10);
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
}

TEST(FixedHashMapTest, RemoveKeyByPointer) {
    FixedHashMap<int, std::string*, 10> m;
    std::string* v = new std::string("ciao");
    
    m.put(10, std::move(v));
    m.remove(10);
    
    ASSERT_THROW(m.get(10), std::invalid_argument);
    
    delete v;
}





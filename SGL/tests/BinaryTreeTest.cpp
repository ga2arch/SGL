//
//  BinaryTreeTest.cpp
//  SGL
//
//  Created by Gabriele Carrettoni on 17/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "BinaryTreeTest.h"

TEST(BinaryTreeTest, Insert) {
    BinaryTree<int> btree;
    
    auto i = new int(10);
    btree.insert(i);
    
    auto f = btree.find(10);
    ASSERT_EQ(*f->elem, *i);
}

TEST(BinaryTreeTest, Emplace) {
    BinaryTree<int> btree;
    
    btree.emplace(10);
    
    auto f = btree.find(10);
    ASSERT_EQ(*f->elem, 10);
}

TEST(BinaryTreeTest, Find) {
    BinaryTree<int> btree;
    
    btree.emplace(10);
    
    auto f = btree.find(10);
    
    ASSERT_EQ(*f->elem, 10);
}
//
//  BinaryTree.h
//  SGL
//
//  Created by Gabriele Carrettoni on 17/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef SGL_BinaryTree_h
#define SGL_BinaryTree_h

#include "Functions.h"

namespace sgl { namespace structures {
    
    template <typename T>
    struct Node {
    
        std::shared_ptr<Node<T>> root  = nullptr;
        std::shared_ptr<Node<T>> right = nullptr;
        std::shared_ptr<Node<T>> left  = nullptr;
        
        std::unique_ptr<T> elem;
        
        Node(): elem(nullptr) {};
        Node(std::unique_ptr<T> elem): elem(std::move(elem)) {};
    };
    
    template <typename T>
    class BinaryTree {
        
    public:
        std::shared_ptr<Node<T>> root;
        
        void insert(std::unique_ptr<T> elem) {
            if (!root) {
                root = std::make_shared<Node<T>>(std::move(elem));
            } else {
                if (*elem >= *root->elem) {
                    auto node = root->right;
                    while (node) {
                        node = node->right;
                    }
                    
                    auto ptr = std::make_shared<Node<T>>(std::move(elem));
                    node = std::move(ptr);
                }
                
                if (*elem < *root->elem) {
                    auto node = root->left;
                    while (node) {
                        node = node->left;
                    }
                    
                    auto ptr = std::make_shared<Node<T>>(std::move(elem));
                    node = std::move(ptr);
                }
            }
        }
        
        void insert(const T* t) {
            auto e = const_cast<T*>(t);
            insert(e);
        }

        void insert(T*& t) {
            auto elem = std::unique_ptr<T>(t);
            insert(std::move(elem));
        }

        
        template <typename... Args>
        void emplace(Args&&... args) {
            auto elem = make_unique<T>(args...);
            insert(std::move(elem));
        }
        
        std::shared_ptr<Node<T>> find(T elem) {
            if (*root->elem.get() == elem) return root;
            
            if (elem >= *root->elem) {
                auto node = root->right;
                while (node && *node->elem != elem) {
                    node = node->right;
                }
                
                if (node) return node;
            }
            
            if (elem < *root->elem) {
                auto node = root->left;
                while (node && *node->elem != elem) {
                    node = node->left;
                }
                
                if (node) return node;
            }
            throw std::runtime_error("");
        }
        
    };
}}

#endif

//
//  FixedArray.h
//  SGL
//
//  Created by Gabriele Carrettoni on 13/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef __SGL__FixedArray__
#define __SGL__FixedArray__

#include <stdio.h>
#include <memory>
#include "Templates.h"
#include "Functions.h"

namespace sgl { namespace structures {

    template <typename T, size_t SIZE>
    class FixedArray {
        
    public:
        template <typename...Args,
        typename = typename std::enable_if<(sizeof...(Args) <= SIZE)
                                            && are_same<T, Args...>::value,T>::type>
        FixedArray(Args... args) {
            data_ = std::unique_ptr<T[]>(new T[SIZE]{std::forward<Args>(args)...});
        };
        
        FixedArray() {}
        
        template <size_t n>
        typename std::enable_if<(n < SIZE), T>::type&
        get() {
            return data_[n];
        }
        
        template <size_t n>
        typename std::enable_if<(n < SIZE), T>::type&&
        remove() {
            return std::move(data_[n]);
        }
        
        template <size_t n, typename E>
        void_t<typename std::enable_if<(n < SIZE), T>::type>
        insert(E&& elem) {
            data_[n] = std::forward<E>(elem);
        }
        
        template <size_t n, typename...Args>
        void_t<typename std::enable_if<(n < SIZE), T>::type>
        emplace(Args&&... args) {
            auto ptr = make_unique<T>(args...);
            data_[n] = std::move(ptr);
        }
        
    private:
        std::unique_ptr<T[]> data_;
    };

}}

#endif /* defined(__SGL__FixedArray__) */

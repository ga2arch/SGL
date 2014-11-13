//
//  Utils.h
//  SGL
//
//  Created by Gabriele Carrettoni on 13/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef SGL_Utils_h
#define SGL_Utils_h

#include <chrono>

namespace sgl {

    template <typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
    
    template<typename TimeT = std::chrono::milliseconds>
    struct measure {
        template<typename F, typename ...Args>
        static typename TimeT::rep execution(F func, Args&&... args) {
            auto start = std::chrono::system_clock::now();
            
            // Now call the function with all the parameters you need.
            func(std::forward<Args>(args)...);
            
            auto duration =
            std::chrono::
            duration_cast<TimeT>(std::chrono::
                                 system_clock::now() - start);
            
            return duration.count();
        }
    };

}


#endif

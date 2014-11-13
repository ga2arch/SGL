//
//  Templates.h
//  SGL
//
//  Created by Gabriele Carrettoni on 13/11/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#ifndef SGL_Templates_h
#define SGL_Templates_h

namespace sgl {
    
    using true_type = std::true_type;
    using false_type = std::false_type;
    
    // is_void
    
    template <typename T>
    struct is_void: false_type {};
    
    template <>
    struct is_void<void>: true_type {};
    
    // is_same
    
    template <typename A, typename B>
    struct is_same: false_type {};
    
    template <typename A>
    struct is_same<A,A>: true_type {};
    
    template <class ...>
    using void_t = void;
    
#define has_member(name) \
template <class T, class = void> \
struct has_##name##_member: false_type {}; \
\
template <class T> \
struct has_##name##_member<T, void_t< typename T::name >>: true_type {};
    
    //
    
    template <typename T>
    struct type_is {
        using type = T;
    };
    
    template<bool q, class A, class B>
    struct if_t: type_is<B> {};
    
    template<class A, class B>
    struct if_t<true, A, B>: type_is<A> {};
    
    //
    
    template <typename... List>
    struct are_same;
    
    template <typename X, typename Y, typename...XS>
    struct are_same<X, Y, XS...>: false_type {};
    
    template <typename X, typename...XS>
    struct are_same<X, X, XS...>: are_same<X, XS...> {};
    
    template <typename X>
    struct are_same<X, X>: true_type {};
    
    //
    
    template <class T>
    using move_assignable_t =
    decltype( std::declval<T&>() = std::declval<T&&>() );
    
    template <class T, class = void>
    struct is_move_assignable: false_type {};
    
    template <class T>
    struct is_move_assignable<T, void_t<move_assignable_t<T>>>: is_same<move_assignable_t<T>, T&> {};
    
    //
    
    template <class...List>
    struct are_move_assignable;
    
    template <class X, class Y, class...XS>
    struct are_move_assignable<X, Y, XS...>: if_t<is_move_assignable<X>::value,
    typename are_move_assignable<Y, XS...>::type, false_type>::type {};
    
    template <class X>
    struct are_move_assignable<X>: if_t<is_move_assignable<X>::value, true_type, false_type>::type {};
    
    //
    
    template <class T>
    using copy_assignable_t =
    decltype( std::declval<T&>() = std::declval<const T&>() );
    
    template <class T, class = void>
    struct is_copy_assignable: false_type {};
    
    template <class T>
    struct is_copy_assignable<T, void_t<copy_assignable_t<T>>>: is_same<copy_assignable_t<T>, T&> {};
    
    //
    
    template <class...List>
    struct are_copy_assignable;
    
    template <class X, class Y, class...XS>
    struct are_copy_assignable<X, Y, XS...>: if_t<is_copy_assignable<X>::value,
    typename are_move_assignable<Y, XS...>::type, false_type>::type {};
    
    template <class X>
    struct are_copy_assignable<X>: if_t<is_copy_assignable<X>::value, true_type, false_type>::type {};
    
}

#endif

//
//  jjmemory.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/16.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//


template <class T1, class T2>
inline void construct(T1 * p,const T2& value){
    new (p)T1(value);
}
template <class T>
inline void destroy(T* pointer){
    pointer->~T();
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first ,InputIterator last, ForwardIterator result);

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
    ForwardIterator cur =first;
    for (; n > 0; --n, ++cur) {
        construct(&*cur, x);
    }
    return cur;
}
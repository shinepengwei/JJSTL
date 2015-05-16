//
//  jjmemory.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/16.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#include "jjmemory.h"

#include <new.h>

template <class T1, classT2>
inline void construct(T1 * p,const T2& value){
    new (p)T1(value);
}
template <class T>
inline void destroy(T* pointer){
    point->~T();
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first ,InputIterator last, ForwardIterator result);

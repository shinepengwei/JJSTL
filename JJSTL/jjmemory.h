//
//  jjmemory.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/16.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//
#pragma once
#include <new>
namespace JJ {

template <class T1, class T2>
inline void construct(T1 * p,const T2& value){
    new (p)T1(value);//在已经分配好的内存指针p上,构造T1::T1(value)
    //也就是说placement new允许你在一个已经分配好的内存中（栈或堆中）构造一个新的对象。
    //原型中void*p实际上就是指向一个已经分配好的内存缓冲区的的首地址。
}
template <class T>
inline void destroy(T* pointer){
    pointer->~T();
}

template<class T>
inline void destroy(T* begin, T* end){
	while (begin < end){
		begin->~T();
		++begin;
	}
}

template <class InputIterator, class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first ,InputIterator last, ForwardIterator result){
        ForwardIterator cur = result;
        for (; first != last; ++first, ++cur) {
            construct(&*cur, *first);
        }
        return cur;
        
    }
template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x){
    ForwardIterator cur =first;
    for (; n > 0; --n, ++cur) {
        JJ::construct(cur, x);//在已经分配好的内存中cur，构造一个新的对象x
    }
    return cur;
}

}
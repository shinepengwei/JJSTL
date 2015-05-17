//
//  jjvector.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/17.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//
#include "jjalloc.h"
#include "jjmemory.h"
namespace JJ
{
    
    template <class T, class Allocator = allocator<T> >
    class vector
    {
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef T*          iterator;
        typedef T&          reference;
        typedef size_t     size_type;
        typedef ptrdiff_t   difference_type;
        
    protected:
        
        iterator start;
        iterator finish;
        iterator end_of_storage;

        iterator allocate_and_fill(size_type n, const T&x){
            iterator result =Allocator::allocate(n);
            uninitialized_fill_n(result, n, x);
            return result;
            
        }
        
        void fill_initialize(size_type n,const T& value){
            start = allocate_and_fill(n, value);
            finish = start + n;
            end_of_storage = finish;
            
        }
        
    public:
        
        vector ():start(0),finish(0),end_of_storage(0){}
        vector(size_type n, const T& value){fill_initialize(n,value);}
        
        size_type size() const {return size_type(finish - start);}
        reference operator[](size_type n){return *(start + n);}
    };
    
}

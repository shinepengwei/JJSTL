//
//  jjalloc.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/15.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef _JJALLOC_
#define _JJALLOC_

#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
#include "jjmemory.h"

namespace JJ {
    template <class T>
    inline T* _allocate(ptrdiff_t size, T*){
        std::set_new_handler(0);
        T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
        if (tmp == 0){
            std::cerr<<"out of memory"<<std::endl;
            exit(1);
        }
        return tmp;
    }
    
    template <class T>
    inline void _deallocate(T* buffer){
        std::cout<<"destory:"<<buffer<<std::endl;
        ::operator delete(buffer);
    }
    
    template<class T>
    class allocator{
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t     size_type;
        typedef ptrdiff_t   difference_type;
        
        template <class U>
        struct rebind{
            typedef allocator<U> other;
            
        };
        static pointer allocate(size_type n, const void * hint = 0){
            return _allocate((difference_type)n, (pointer) 0 );
        }
        
        static void deallocate(pointer p , size_type n){
            _deallocate(p);
        }
        
        static pointer address(reference x){return (pointer) &x;}
        
        static const_pointer const_address(const_reference x){return (const_pointer) &x;}
        
        static size_type max_size(){
            return size_type(UINT_MAX/sizeof(T));
        }
        
        
    };

}
#endif

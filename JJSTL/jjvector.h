//
//  jjvector.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/17.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//
#include "jjalloc.h"
#include "jjmemory.h"
#include "jj_iterator.h"
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

        void insert_aux(iterator position, const T& x){
            const size_type old_size = size();
            const size_type len = old_size != 0 ? 2*old_size : 1;

            iterator new_start = Allocator::allocate(len);
            iterator new_finish = new_start;

            new_finish = uninitialized_copy(start, position, new_start);
            construct(new_finish,x);
            ++new_finish;


            destroy(begin(),end());
            deallocate();

            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }

        void deallocate(){
            if(start)
                Allocator::deallocate(start);
        }
        
    public:
        
        vector ():start(0),finish(0),end_of_storage(0){}
        vector(size_type n, const T& value){fill_initialize(n,value);}
        


        size_type size() const {return size_type(finish - start);}
        size_type capacity() const{
            return size_type(end_of_storage - begin());
        }
        bool empty() const{
            return finish == start;
        }

        iterator begin() const {return start;}
        iterator end() const {return finish;}

        reference operator[](size_type n){return *(start + n);}

        void push_back(const T& x){
            if (finish != end_of_storage){
                construct(finish,x);
                ++finish;
            }else
                insert_aux(end(),x);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

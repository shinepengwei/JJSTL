//
//  jj_list.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/19.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__jj_list__
#define __JJSTL__jj_list__

#include <stdio.h>
#include "jj_iterator.h"
#include "jjalloc.h"
namespace JJ{
    template<class T>
    struct __list_iterator;
    
    template <class T>
    struct __list_node{
        typedef __list_node * void_pointer;
        
        void_pointer prev;
        void_pointer next;
        T data;
    };
    
    template<class T>
    struct __list_iterator:public iterator<bidirectional_iterator_tag,T>{
        typedef __list_node<T> * link_type;
        typedef iterator<bidirectional_iterator_tag, T> super_type;
        typedef __list_iterator<T> self_type;

        link_type node;//指向listnode
        __list_iterator(link_type x):node(x){}
        __list_iterator(const super_type& x):node(x.node){}

        typename super_type::reference operator*() const {return (*node).data;}
        
        self_type & operator++(){
            node = (link_type)((*node).next);
            return *this;
        }
    };
    
    template <class T, class Allocator = JJ::allocator<__list_node<T>>>
    class list{
    protected:
        typedef __list_node<T> list_node;
    public:
        typedef __list_iterator<T> iterator;
        typedef list_node* link_type;
        iterator begin(){return (link_type) ((*node).next);}
        iterator end(){return (link_type)(node);}
        list(){
            node = get_node();
            node->next = node;
            node->prev = node;
        }
        void push_back(const T& x){
            link_type newNode = create_node(x);
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev->next = newNode;
            node->prev = newNode;
        }
    protected:
        link_type node;
        
        
        
    protected:
        link_type get_node(){return Allocator::allocator();}
        link_type create_node(const T& x){
            link_type p = get_node();
            construct(&p->data,x);
            return p;
        }
    };
    

}

#endif /* defined(__JJSTL__jj_list__) */

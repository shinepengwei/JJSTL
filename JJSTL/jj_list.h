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
#include "jj_iterfunc.h"
namespace JJ{
    template<class T>
    struct __list_iterator;
    
    template <class T>
    struct __list_node{
        typedef __list_node * pointer;
        
        pointer prev;
        pointer next;
        T data;
    };
    
    template<class T>
    struct __list_iterator:public iterator<bidirectional_iterator_tag,T>{
        typedef __list_node<T> * link_type;
        typedef iterator<bidirectional_iterator_tag, T> super_type;
        typedef __list_iterator<T> self_type;

        link_type node_ptr;//指向的listnode
        __list_iterator(link_type x):node_ptr(x){}
        __list_iterator(const super_type& x):node_ptr(x.node_ptr){}


        bool operator==(const self_type&x) const{return node_ptr == x.node_ptr;}
        bool operator!=(const self_type&x) const{return node_ptr != x.node_ptr;}

        typename super_type::reference operator*() const {return (*node_ptr).data;}
        typename super_type::pointer operator->() const{return &(operator*());}

        self_type & operator++(){
            node_ptr = (link_type)((*node_ptr).next);
            return *this;
        }
        self_type & operator--(){
            node_ptr = (link_type)((*node_ptr).prev);
            return *this;
        }

    };
    
    template <class T, class Alloc = JJ::allocator<__list_node<T>>>
    class list{
    protected:
        typedef __list_node<T> list_node;
        typedef list_node* link_type;
        typedef list_node& reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;
    protected:
        link_type node_end;
        
    protected:
        link_type get_node(){return Alloc::allocate(1);}
        link_type create_node(const T& x){
            link_type p = get_node();
            JJ::construct(&(p->data),x);//TODO 为何只需要construct data？？
            return p;
        }

        void put_node(link_type p){Alloc::deallocate(p,1);};
        void destory_node(link_type p ){
            std::cout<<"destory:"<<p->data<<std::endl;
            JJ::destroy(&p->data);
            put_node(p);
        }

    
    public:
        typedef __list_iterator<T> iterator;
        iterator begin() const{return (link_type) ((*node_end).next);}
        iterator end() const{return (link_type)(node_end);}
        bool empty(){return node_end->next == node_end;}
        size_type size() const{
            return distance(begin(),end());
        }
        list(){
            node_end = get_node();
            node_end->next = node_end;
            node_end->prev = node_end;
        }

        void push_back(const T& x){
            link_type newNode = create_node(x);
            newNode->next = node_end;
            newNode->prev = node_end->prev;
            node_end->prev->next = newNode;
            node_end->prev = newNode;
        }

        iterator erase(iterator position){
            link_type next_node = (link_type)position.node_ptr->next;
            link_type prev_node = (link_type)position.node_ptr->prev;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destory_node(position.node_ptr);
            if (next_node == node_end){
                 return begin();
            }
            return iterator(next_node);

        }
        
        reference front(){return *begin();}
        reference back(){return *(--end());}
        
       };
    

}

#endif /* defined(__JJSTL__jj_list__) */

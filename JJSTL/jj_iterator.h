//
//  jj_iterator.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/18.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__jj_iterator__
#define __JJSTL__jj_iterator__

#include <stdio.h>
#include <cstddef>
namespace JJ{
    
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag : public input_iterator_tag{};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};
    
    
    //所有的iterator都需要继承的类
    template <class Category, class T,
    class Distance = ptrdiff_t,
    class Pointer = T*,
    class Reference = T&>
    struct iterator{
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
    };
    
    
    //榨汁机 traits
    template <class Iterator>
    struct iterator_traits{
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };
    
    //接着是两个特化
    template <class T>
    struct iterator_traits<T*>{
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };
    
    template <class T>
    struct iterator_traits<const T*>{
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };
    
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&){
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();//生成一个临时对象
    }
    
    template <class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator&){
        return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
    }
    
    //advance函数
    template <class InputIterator, class Distance>
    inline void __advance(InputIterator & i, Distance n, input_iterator_tag _){
        while(n--) ++i;
    }
    
    template <class BidirectionalIterator, class Distance>
    inline void __advance(BidirectionalIterator & i, Distance n, bidirectional_iterator_tag _){
        if(n >=0)
            while(n--) ++i;
        else
            while(n++) --i;
    }
    
    template <class RandomAccessIterator, class Distance>
    inline void __advance(RandomAccessIterator & i, Distance n, random_access_iterator_tag _){
        i +=n;
    }
    
    template <class InputIterator, class Distance>
    inline void advance(InputIterator &i, Distance n){
        __advance(i, n, iterator_category(i));
    }

    
}
#endif /* defined(__JJSTL__jj_iterator__) */

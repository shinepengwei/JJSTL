//
//  jj_iterfunc.h
//  JJSTL
//
//  Created by yangpengwei on 15/5/21.
//  Copyright (c) 2015年 yangpengwei. All rights reserved.
//

#ifndef __JJSTL__jj_iterfunc__
#define __JJSTL__jj_iterfunc__

#include <stdio.h>
#include "jj_iterator.h"

namespace JJ {
    
    
    
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    __distance(InputIterator first, InputIterator last, input_iterator_tag){
        typename iterator_traits<InputIterator>::difference_type n =0;
        while (first != last) {
            n++;
            ++first;
        }
        return n;
    }
    
    template<class RandomAccessIterator>
    inline typename iterator_traits<RandomAccessIterator>::difference_type
    __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
        return last - first;
    }
    
    
    template<class InputIterator>
    inline typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first,InputIterator end){
        return __distance(first,end,iterator_category(first));
    }
}


#endif /* defined(__JJSTL__jj_iterfunc__) */

#include "SortClass.h"
#include <random>
#include <algorithm>
#include <array>
#include <cassert>
#include <future>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <regex>

#define MIN_N 37


template<typename T>
bool lmr(const T& a, const T& b)
{
    return a > b;
}

template <typename T>
void shift(const T& el1, const T& el2)
{
    T tmp = *el1;
    *el1 = *el2;
    *el2 = *tmp;
}

///////////////////////////////////////////////////////////////////
template <typename T, typename Compare>                          //
void insertion_sort(T *first, T* last, Compare comp)             //
{                                                                //
    for (T* i = first; i < last; i++)                            //
    {                                                            //
        for (T* j = i+1; j < last; j++)                          //
        {                                                        //
            if (lmr(*i,*j)){shift(*i,*j);}                //
        }                                                        //
    }                                                            //
}                                                                //
///////////////////////////////////////////////////////////////////

template<typename T, typename Compare>
void sort (T *first, T *last, Compare comp)
{
    while(first < last)
    {
        if((last - first + 1) > MIN_N)
        {
            T* mid = last - (last - first)/2;
            T* pivot = (*first > *last ? (*mid > *first ? first : (*last > *mid ? last : mid)) : (*mid > *last ? last : (*first > *mid ? first : mid)));
            T key = *pivot;
            if (*pivot != *mid) shift(*pivot, *mid);
            T *i = first, *j = last;
            while (i <= j)
            {
                while(lmr(key, *i)) first++;
                while(lmr(*j, key)) last--;
                if(i <= j)
                {
                    shift(*i, *j);       
                    first++;
                    last--;
                }
            }
            if((j - first) >= (last - (j + 1)))
            {
                sort(j+1, last, comp);
                last = j;
            }
            else
            {
                sort(j, first, comp);
                first = j + 1;
            }
        }
        else
        {
            insertion_sort(first, last, comp);
            break;
        }
    }
}
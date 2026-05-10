#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    // Реализуйте слияние, используя компаратор.
    std::deque<T> out;
    auto iter_1 = half1.begin();
    auto iter_2 = half2.begin();

    while(true){
        if(iter_1 == half1.end()){
            while(iter_2 != half2.end()){
                out.push_back(*iter_2);
                iter_2++;
            }
            return out;
        }else if(iter_2 == half2.end()){
            while(iter_1 != half1.end()){
                out.push_back(*iter_1);
                iter_1++;
            }
            return out;
        }else if (comparator(*iter_1, *iter_2)){
            out.push_back(*iter_1);
            iter_1++;
        }else if(*iter_1 == *iter_2){
            out.push_back(*iter_1);
            iter_1++;
        }else {
            out.push_back(*iter_2);
            iter_2++;
        }
    }
}


template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if(src.size()<=1){
        return src;
    }

    size_t mid = src.size() / 2;
    std::deque<T> left (src.begin(), src.begin() + mid);
    std::deque<T> right (src.begin()+mid, src.end());
    std::deque<T> left_src = MergeSort(left, comparator);
    std::deque<T> right_src = MergeSort(right, comparator);

    return Merge(left_src, right_src, comparator);
}

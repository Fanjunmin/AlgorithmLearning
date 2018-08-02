// CopyRight 2018, FanJunmin.
// All rights reserved.
// Author: junminfan@126.com (FanJunmin)
// Update: 2018/7/29


#pragma once

#include <algorithm>

using std::swap;

//BubbleSort
//average:O(n^2);
//best:O(n^2);
//worst:O(n^2);
//space complication:O(1);
//stable sort
template <class RandomIt>
void BubbleSort(RandomIt first, RandomIt last) {
  if (last < first) throw "Interval is wrong";
  auto len = last - first;
  for (int i = 0; i < len - 1; ++i) {
    for (auto ite = first; ite < last - i - 1; ++ite) {
      if (*ite > *(ite + 1)) {
        swap(*ite, *(ite + 1));
      }
    }
  }
	return;
}
template <class RandomIt, class Compare>
void BubbleSort(RandomIt first, RandomIt last, Compare cmp) {
  if (last < first) throw "Interval is wrong";
  auto len = last - first;
  for (int i = 0; i < len - 1; ++i) {
    for (auto ite = first; ite < last - i - 1; ++ite) {
      if (!cmp(*ite, *(ite + 1))) {
        swap(*ite, *(ite + 1));
      }
    }
  }
	return;
}

//best O(n)
template <class RandomIt>
void BubbleSortWithFlag(RandomIt first, RandomIt last) {
  if (last < first) throw "Interval is wrong";
	bool flag = false;		//全局有序标志
  while (!flag) {
    flag = true;
    for (auto iter = first; iter < last - 1; ++iter) {
      if (*iter > *(iter + 1)) {
        swap(*iter, *(iter + 1));
        flag = false; //清楚全局有序标志
      }
    }
    --last;
  }
  return;
}
template <class RandomIt, class Compare>
void BubbleSortWithFlag(RandomIt first, RandomIt last, Compare cmp) {
  if (last < first) throw "Interval is wrong";
  bool flag = false;		//全局有序标志
  while (!flag) {
    flag = true;
    for (auto iter = first; iter < last - 1; ++iter) {
      if (!cmp(*iter, *(iter + 1))) {
        swap(*iter, *(iter + 1));
        flag = false; //清楚全局有序标志
      }
    }
    --last;
  }
  return;
}

//Selection sort
//average:O(n^2);
//best:O(n^2);
//worst:O(n^2);
//space complication:O(1);
//unstable sort
template <class RandomIt>
void SelectionSort(RandomIt first, RandomIt last) {
  if (last < first) throw "Interval is wrong";
  for (auto iter1 = first; iter1 < last - 1; ++iter1) {
    auto min_iter = iter1;
    for (auto iter2 = iter1 + 1; iter2 < last; ++iter2) {
      if (*iter2 < *min_iter) {
        min_iter = iter2;
      }
    }
    swap(*min_iter, *iter1);
  }
  return;
}
template <class RandomIt, class compare>
void SelectionSort(RandomIt first, RandomIt last, compare cmp) {
  if (last < first) throw "Interval is wrong";
  for (auto iter1 = first; iter1 < last - 1; ++iter1) {
    auto min_iter = iter1;
    for (auto iter2 = iter1; iter2 < last; ++iter2) {
      if (!cmp(*min_iter, *iter2)) {
        min_iter = iter2;
      }
    }
    swap(*min_iter, *iter1);
  }
  return;
}

// Insertion sort
// average:O(n^2);
// best:O(n);
// worst:O(n^2);
// space complication:O(1);
// stable sort
template <class RandomIt>
void InsertionSort(RandomIt first, RandomIt last) {
  if (last < first) throw "Interval is wrong";
  for (auto iter = first + 1; iter != last; ++iter) {
		auto value = *iter;
		auto iter_temp = iter - 1;
		while (iter_temp >= first && *iter_temp > value) {
			*(iter_temp + 1) = *iter_temp;
      if (iter_temp == first) break;
			--iter_temp;
		}
		(iter_temp == first) ? *(iter_temp) = value : *(iter_temp + 1) = value;
  }
	return;
}
template <class RandomIt, class compare>
void InsertionSort(RandomIt first, RandomIt last, compare comp) {
  if (last < first) throw "Interval is wrong";
  for (auto iter = first + 1; iter != last; ++iter) {
    auto value = *iter;
    auto iter_temp = iter - 1;
    while (iter_temp >= first && !comp(*iter_temp, value)) {
      *(iter_temp + 1) = *iter_temp;
      if (iter_temp == first) break;
      --iter_temp;
    }
    iter_temp == first ? *(iter_temp) = value : *(iter_temp + 1) = value;
  }
  return;
}

//CountSort
//Time: O(n + k)
template <typename RandomItWithTypeInt>
void CountSort(RandomItWithTypeInt first, RandomItWithTypeInt last) {
  if (last < first) throw "Interval is wrong";
  int maxElem = *max_element(first, last);
  int minElem = *min_element(first, last);
	vector<int> count_array(maxElem - minElem + 1, 0);
  for (auto iter = first; iter != last; ++iter) {
    ++count_array[*iter];
  }
	auto iter = first;
  for (int i = 0; i <= maxElem - minElem; ++i) {
		while (count_array[i]) {
			*first++ =  i + minElem;
			--count_array[i];
		}
  }
	return;
}

//RadixSort
//Time : O(k*n)
template <typename RandomItWithTypeUnsigned> 
void RadixSort(RandomItWithTypeUnsigned first, RandomItWithTypeUnsigned last) {
  if (last < first) throw "Interval is wrong";
	int max_digits = 1;
	int digit = 10;
  for (auto iter = first; iter != last; ++iter) {
		if (*iter >= digit) {
			digit *= 10;
			++max_digits;
		}
  }
	int radix = 1, max_index = last - first;
  vector<int> temp(first, last);
  for (int i = 0; i < 10; ++i) {
    vector<int> count(10);
    for (auto iter = first; iter != last; ++iter) {
			int k = (*iter / radix) % 10;
      ++count[k];
    }
    for (int j = 1; j < 10; ++j) {
      count[j] += count[j - 1];
    }
    for (int n = max_index - 1; n >= 0; --n) {
      int k = (*(first + n) / radix) % 10;
      temp[count[k] - 1] = *(first + n);
      --count[k];
    }
    for (auto i = 0; i < max_index; ++i) {
      *(first + i) = temp[i];
		}
		radix *= 10;
  }
	return;
}


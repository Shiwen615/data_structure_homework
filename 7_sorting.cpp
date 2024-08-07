#include <iostream>
using std::cout;
using std::endl;
#include <array>
#include <algorithm>
using std::swap;
#include <cmath>
#include <functional>
#include <vector>
#include <unordered_map>
#include <chrono>
using namespace std::chrono;


template <size_t N>
void print_arr(const std::array<int, N> &arr){
    for (auto &&i : arr)
    {
        cout << i << ", ";
    }
    cout << endl;
}

template <size_t N>
std::array<int, N> selection(std::array<int, N> &arr)
{
    std::array<int, N> ret = arr;
    for (auto i = ret.begin(); i < ret.end() - 1; i++)
    {
        int *min = i;
        for (auto j = i + 1; j < ret.end(); j++)
        {
            if (*j < *min)
            {
                min = j;
            }
        }
        swap(*i, *min);
    }
    return ret;
}

template <size_t N>
std::array<int, N> insertion(std::array<int, N> &arr)
{
    std::array<int, N> ret = arr;
    for (auto i = ret.begin() + 1; i < ret.end(); i++)
    {
        for (auto j = i; j > ret.begin() && *j < *(j - 1) ; j--)
        {
            swap(*j, *(j - 1));
        }
    }
    return ret;
}

template <size_t N>
void merge_sort(std::array<int, N> &arr, size_t left , size_t right ) {
    if (left < right) {
        size_t mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        auto merge = [](std::array<int, N> &arr, size_t left, size_t mid, size_t right) -> void {
            size_t id_left = left;
            size_t id_right = mid + 1;
            std::vector<int> tmp;
            tmp.reserve(right - left + 1);
            while (id_left <= mid || id_right <= right) {
                if (arr.at(id_left) <= arr.at(id_right)) {
                    tmp.emplace_back(arr.at(id_left));
                    id_left++;
                }
                else {
                    tmp.emplace_back(arr.at(id_right));
                    id_right++;
                }

                if (id_left > mid) {
                    tmp.insert(tmp.end(), arr.begin() + id_right, arr.begin() + right + 1);
                    break;
                }
                if (id_right > right) {
                    tmp.insert(tmp.end(), arr.begin() + id_left, arr.begin() + mid + 1);
                    break;
                }
            }
            std::move(tmp.begin(), tmp.end(), arr.begin() + left);
        };

        merge(arr, left, mid, right);
    }
}
template <size_t N>
std::array<int, N> merge_sort(std::array<int, N> &arr) {
    std::array<int, N> ret = arr;
    size_t left = 0;
    size_t right = N - 1;
    merge_sort(ret, left, right);
    return ret;
}
template <size_t N>
std::array<int, N> heap_sort(std::array<int, N> &arr)
{
    std::function<void(std::array<int, N+1> &, size_t, size_t)> heapify;
    heapify = [&heapify](std::array<int, N+1> &arr, size_t root, size_t size) -> void {
        size_t left_child = 2 * root;
        size_t right_child = 2 * root + 1;
        size_t largest = root;
        if (left_child < size && arr.at(left_child) > arr.at(largest)) {
            largest = left_child;
        }
        if (right_child < size && arr.at(right_child) > arr.at(largest)) {
            largest = right_child;
        }

        if (largest != root) {
            swap(arr.at(root), arr.at(largest));
            heapify(arr, largest, size);
        }
    };

    auto build_max_heap = [&heapify](const std::array<int, N> &arr) -> std::array<int, N+1> {
        std::array<int, N+1> ret_arr;
        std::copy(arr.begin(), arr.end(), ret_arr.begin() + 1);
        for (int i = (ret_arr.size()-1) / 2; i > 0; i--)
        {
            heapify(ret_arr, i, ret_arr.size());
        }
        return ret_arr;
    };

    std::array<int, N+1> arr2 = build_max_heap(arr);
    for (size_t i = N; i > 1; i--)
    {
        swap(arr2.at(i), arr2.at(1));
        heapify(arr2, 1, i);
    }

    std::array<int, N> ret;
    std::copy(arr2.begin() + 1, arr2.end(), ret.begin());
    return ret;
}



template <size_t N>
void quick_sort(std::array<int, N> &arr, int left, int right) {
    if (left < right) {
        int i = left;
        int j = right+1;
        int pivot = left;

        while (i < j) {
            do i++; while (i < right && arr.at(i) < arr.at(pivot));
            do j--; while (j > left && arr.at(j) > arr.at(pivot));

            if (i < j) {
                swap(arr.at(i), arr.at(j));
            }
        }
        swap(arr.at(j), arr.at(pivot));

        quick_sort(arr, left, j-1);
        quick_sort(arr, j+1, right);
    }
}
template <size_t N>
std::array<int, N> quick_sort(std::array<int, N> &arr) {
    std::array<int, N> ret = arr;
    int left = 0;
    int right = N - 1;
    quick_sort(ret, left, right);
    return ret;
}

// int get_digit(int num, int digit) {
//     return num / (int)std::pow(10, digit) % 10;
// };

template <size_t N>
std::array<int, N> radix_sort(std::array<int, N> &arr) {
    auto get_digit = [](int num, int digit) -> int {
        return num / (int)std::pow(10, digit) % 10;
    };

    auto count_digit = [](int num) -> int {
        return std::log10(num) + 1;
    };
    auto max_digits_count = [&arr, &count_digit]() -> int {
        int ret;
        for (auto &&i : arr) {
            int digit = count_digit(i);
            if (digit > ret) {
                ret = digit;
            }
        }
        return ret;
    };

    int max_digits = max_digits_count();

    std::array<int, N> ret;
    for (size_t i = 0; i < max_digits; i++)
    {
        std::vector<std::vector<int>> digit_buckets(10);
        for (auto &&n : arr)
        {
            digit_buckets.at(get_digit(n, i)).emplace_back(n);
        }

        // concat all vectors into returned arr
        size_t start = 0;
        for (auto v = digit_buckets.begin(); v < digit_buckets.end(); v++)
        {
            std::move(v->begin(), v->end(), ret.begin() + start);
            start += v->size();
        }
    }
    return ret;
}
int main()
{
    const int size = 50000;

    using sorter_ptr = std::array<int, size> (*)(std::array<int, size> &);
    std::unordered_map<std::string, sorter_ptr> sorters_map = {
        {"selection", selection},
        {"insertion", insertion},
        {"heap_sort", heap_sort},
        {"merge_sort", merge_sort},
        {"quick_sort", quick_sort},
        {"radix_sort", radix_sort},
    };

    std::array<int, size> arr;

    // fill random numbers in array
    for (auto &&i : arr)
    {
        i = rand() % size;
    }

    for (auto &&s : sorters_map)
    {
        cout << s.first << ": ";
        auto startTime = high_resolution_clock::now();
        // print_arr(s.second(arr));
        s.second(arr);
        auto endTime = high_resolution_clock::now();
        std::cout << duration_cast<microseconds>(endTime - startTime).count() << " microseconds" << endl;
    }

    return 0;
}

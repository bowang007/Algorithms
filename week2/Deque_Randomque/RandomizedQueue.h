//
// Created by brayden on 2019-08-31.
//

#ifndef DEQUE_RANDOMQUE_RANDOMIZEDQUEUE_H
#define DEQUE_RANDOMQUE_RANDOMIZEDQUEUE_H

#include <random>
#include <memory>
#include <string>

int get_random(int t) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> distribution(0, t);
    int dice_roll = distribution(rng);
    return dice_roll;
}

template <typename T>
class RandomizedQueue {
public:
    RandomizedQueue() : first(nullptr), first_free(nullptr), cap(nullptr) { }
    bool isEmpty() const { return !size(); }
    int size() const { return first_free - first;}
    int capacity() const { return cap - first; }
    void enque(const T &);
    T dequeue();
    ~ RandomizedQueue();
private:
    static std::allocator<T> alloc;
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    void alloc_n_move(size_t new_cap);
    void free();
    void reallocate();
    T *first;
    T *first_free;
    T *cap;
};

template <typename T>
std::allocator<T> RandomizedQueue<T>::alloc;

template <typename T>
void RandomizedQueue<T>::free() {
    if (first) {
        for (auto p = first_free; p >= first; )
            alloc.destroy(--p);
        alloc.deallocate(first, cap - first);
    }
}

template <typename T>
RandomizedQueue<T>::~RandomizedQueue() {
    free();
}

template <typename T>
void RandomizedQueue<T>::alloc_n_move(size_t new_cap) {
    auto new_data = alloc.allocate(new_cap);
    auto dest = new_data;
    auto first_val_inc = first;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*first_val_inc++));
    free();
    first = new_data;
    first_free = dest;
    cap = first + new_cap;
}

template <typename T>
void RandomizedQueue<T>::reallocate() {
    int new_cap = size() ? 2 * size() : 1;
    alloc_n_move(new_cap);
}

template <typename T>
void RandomizedQueue<T>::enque(const T &val) {
    chk_n_alloc();
    alloc.construct(first_free++, val);
}

template <typename T>
T RandomizedQueue<T>::dequeue() {
    if (size() == 0)
        throw std::out_of_range("Cannot dequeue on empty queue");
    int range = size() - 1;
    int del_idx = get_random(range);
    int pop_val = *(first + del_idx);
    auto old_first_free = first_free;
    *(first + del_idx) = *(--first_free);
    alloc.destroy(old_first_free);
    return pop_val;
}


#endif //DEQUE_RANDOMQUE_RANDOMIZEDQUEUE_H

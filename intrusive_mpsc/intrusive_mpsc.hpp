#pragma once

#include <atomic>

template <class T>
struct IntrusiveForwardNode { // CRTP
    IntrusiveForwardNode* next;

    T* AsItem() {
        return static_cast<T*>(this);
    }

};

template <typename T>
class MPSCIntrusiveQuque {
    using Node = IntrusiveForwardNode<T>;
public:

private:
    std::atomic<Node*> top_;
};
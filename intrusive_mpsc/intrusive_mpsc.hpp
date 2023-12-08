#pragma once

#include <atomic>

template <class T>
struct IntrusiveForwardNode { // use CRTP
    IntrusiveForwardNode* next;

    T* AsItem() {
        return static_cast<T*>(this);
    }

};

template <typename T>
class MPSCIntrusiveQuque {
    using Node = IntrusiveForwardNode<T>;
public:
    void Push(Node* node) {
        node->next = top_.load();

        while (!top_.compare_exchange_weak(node->next, node)) {}
    }

    T* TryPop() {
        auto* top = top_.load();

        while (top && !top_.compare_exchange_weak(top, top->next)) {}

        return top->AsItem();
    }

private:
    std::atomic<Node*> top_;
};
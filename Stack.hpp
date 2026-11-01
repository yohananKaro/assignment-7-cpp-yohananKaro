#ifndef STACK_HPP
#define STACK_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

// Generic LIFO stack backed by Container<T>
template <typename T>
class Stack {
private:
    Container<T> container_;

public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack& operator=(const Stack& other) = default;
    ~Stack() = default;

    // Push element onto stack
    void push(const T& value) {
        container_.add(value);
    }

    // Pop and return top element
    T pop() {
        if (container_.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        int topIndex = container_.getCount() - 1;
        T value = container_.get(topIndex);
        container_.removeAt(topIndex);
        return value;
    }

    // Peek top element
    T& top() {
        if (container_.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return container_.get(container_.getCount() - 1);
    }

    const T& top() const {
        if (container_.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return container_.get(container_.getCount() - 1);
    }

    int size() const {
        return container_.getCount();
    }

    bool isEmpty() const {
        return container_.isEmpty();
    }

    // Iterator support (bottom to top)
    using Iterator = typename Container<T>::Iterator;

    Iterator begin() {
        return container_.begin();
    }

    Iterator end() {
        return container_.end();
    }

    Iterator begin() const {
        return container_.begin();
    }

    Iterator end() const {
        return container_.end();
    }
};

}  // namespace containers

#endif  // STACK_HPP

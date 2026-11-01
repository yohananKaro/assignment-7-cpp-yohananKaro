#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Container.hpp"
#include <stdexcept>

namespace containers {

// Generic FIFO queue backed by Container<T>
template <typename T>
class Queue {
private:
    Container<T> container_;

public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue& operator=(const Queue& other) = default;
    ~Queue() = default;

    // Add element to back of queue
    void enqueue(const T& value) {
        container_.add(value);
    }

    // Remove and return front element
    T dequeue() {
        if (container_.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        T value = container_.get(0);
        container_.removeAt(0);
        return value;
    }

    // Peek front element
    T& front() {
        if (container_.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return container_.get(0);
    }

    const T& front() const {
        if (container_.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return container_.get(0);
    }

    // Peek back element
    T& back() {
        if (container_.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return container_.get(container_.getCount() - 1);
    }

    const T& back() const {
        if (container_.isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return container_.get(container_.getCount() - 1);
    }

    int size() const {
        return container_.getCount();
    }

    bool isEmpty() const {
        return container_.isEmpty();
    }

    // Iterator support (front to back)
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

#endif  // QUEUE_HPP

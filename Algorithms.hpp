#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace containers {

// Returns the index of the first occurrence of value, or -1 if not found.
template <typename T>
int find(const Container<T>& container, const T& value) {
    for (int i = 0; i < container.getCount(); i++) {
        if (container.get(i) == value) {
            return i;
        }
    }
    return -1;
}

// Counts how many times value appears in the container.
template <typename T>
int count(const Container<T>& container, const T& value) {
    int total = 0;
    for (int i = 0; i < container.getCount(); i++) {
        if (container.get(i) == value) {
            total++;
        }
    }
    return total;
}

// Checks if the container contains value.
template <typename T>
bool contains(const Container<T>& container, const T& value) {
    return find(container, value) != -1;
}

// Computes the sum of all elements (or concatenation for strings).
template <typename T>
T sum(const Container<T>& container) {
    T result = T();
    for (int i = 0; i < container.getCount(); i++) {
        result = result + container.get(i);
    }
    return result;
}

// Returns the minimum element. Throws std::underflow_error if container is empty.
template <typename T>
T min(const Container<T>& container) {
    if (container.isEmpty()) {
        throw std::underflow_error("Container is empty");
    }
    T minVal = container.get(0);
    for (int i = 1; i < container.getCount(); i++) {
        if (container.get(i) < minVal) {
            minVal = container.get(i);
        }
    }
    return minVal;
}

// Returns the maximum element. Throws std::underflow_error if container is empty.
template <typename T>
T max(const Container<T>& container) {
    if (container.isEmpty()) {
        throw std::underflow_error("Container is empty");
    }
    T maxVal = container.get(0);
    for (int i = 1; i < container.getCount(); i++) {
        if (container.get(i) > maxVal) {
            maxVal = container.get(i);
        }
    }
    return maxVal;
}

// Prints a container to an output stream.
template <typename T>
void print(const Container<T>& container, std::ostream& outStream = std::cout) {
    outStream << "[";
    for (int i = 0; i < container.getCount(); i++) {
        if (i > 0) {
            outStream << ", ";
        }
        outStream << container.get(i);
    }
    outStream << "]";
}

// Prints a stack from bottom to top.
template <typename T>
void print(const Stack<T>& stack, std::ostream& outStream = std::cout) {
    outStream << "Stack(bottom -> top): [";
    bool first = true;
    for (const T& val : stack) {
        if (!first) {
            outStream << ", ";
        }
        outStream << val;
        first = false;
    }
    outStream << "]";
}

// Prints a queue from front to back.
template <typename T>
void print(const Queue<T>& queue, std::ostream& outStream = std::cout) {
    outStream << "Queue(front -> back): [";
    bool first = true;
    for (const T& val : queue) {
        if (!first) {
            outStream << ", ";
        }
        outStream << val;
        first = false;
    }
    outStream << "]";
}

// Applies a function to modify each element in-place.
template <typename T, typename Func>
void transform(Container<T>& container, Func func) {
    for (int i = 0; i < container.getCount(); i++) {
        func(container.get(i));
    }
}

// Returns a new container with elements that satisfy the predicate.
template <typename T, typename Pred>
Container<T> filter(const Container<T>& container, Pred predicate) {
    Container<T> result;
    for (int i = 0; i < container.getCount(); i++) {
        if (predicate(container.get(i))) {
            result.add(container.get(i));
        }
    }
    return result;
}

// Reverses the elements of the container in-place.
template <typename T>
void reverse(Container<T>& container) {
    int left = 0;
    int right = container.getCount() - 1;
    while (left < right) {
        T temp = container.get(left);
        container.get(left) = container.get(right);
        container.get(right) = temp;
        left++;
        right--;
    }
}

// Returns a string representation of the container.
template <typename T>
std::string toString(const Container<T>& container) {
    std::ostringstream oss;
    print(container, oss);
    return oss.str();
}

}  // namespace containers

#endif  // ALGORITHMS_HPP

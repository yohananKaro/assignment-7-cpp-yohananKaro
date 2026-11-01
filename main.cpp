/**
 * @file main.cpp
 * @brief Demo for Generic Container Library
 *
 * This file demonstrates the expected behavior of the templated
 * Container, Stack, Queue, and Algorithm functions.
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"

using namespace containers;

namespace {
constexpr int kTen = 10;
constexpr int kTwenty = 20;
constexpr int kThirty = 30;
constexpr int kForty = 40;
constexpr int kFifty = 50;
constexpr int kSixty = 60;
constexpr int kSeventy = 70;
constexpr int kNinetyNine = 99;
constexpr int kOneHundred = 100;
constexpr int kTwoHundred = 200;
constexpr int kThreeHundred = 300;
constexpr int kFive = 5;

constexpr double kPiApprox = 3.14;
constexpr double kEulerApprox = 2.71;
constexpr double kSqrtTwoApprox = 1.41;
}

int main() {
    try {
    std::cout << "===== Generic Container Library Demo =====\n\n";

    // ---- Section 1: Container basics ----
    std::cout << "--- Container<int> Basics ---\n";

    Container<int> nums;
    nums.add(kTen);
    nums.add(kTwenty);
    nums.add(kThirty);
    nums.add(kForty);
    nums.add(kFifty);   // triggers resize (default capacity is 4)

    std::cout << "Count: " << nums.getCount() << "\n";
    // Expected: Count: 5

    std::cout << "Capacity: " << nums.getCapacity() << "\n";
    // Expected: Capacity: 8

    std::cout << "Element at 0: " << nums.get(0) << "\n";
    // Expected: Element at 0: 10

    std::cout << "Element at 4: " << nums.get(4) << "\n";
    // Expected: Element at 4: 50

    // ---- Section 2: Container iterator ----
    std::cout << "\n--- Container Iterator ---\n";

    std::cout << "Elements: ";
    for (Container<int>::Iterator it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    // Expected: Elements: 10 20 30 40 50

    // Range-based for loop (uses begin/end)
    std::cout << "Range-for: ";
    for (const int& val : nums) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    // Expected: Range-for: 10 20 30 40 50

    // ---- Section 3: Container<string> ----
    std::cout << "\n--- Container<string> ---\n";

    Container<std::string> words;
    words.add("hello");
    words.add("world");
    words.add("templates");
    words.add("are");
    words.add("great");

    std::cout << "Words: ";
    for (const std::string& wordValue : words) {
        std::cout << wordValue << " ";
    }
    std::cout << "\n";
    // Expected: Words: hello world templates are great

    // ---- Section 4: Print function ----
    std::cout << "\n--- Print Function ---\n";

    print(nums);
    std::cout << "\n";
    // Expected: [10, 20, 30, 40, 50]

    print(words);
    std::cout << "\n";
    // Expected: [hello, world, templates, are, great]

    Container<int> empty;
    print(empty);
    std::cout << "\n";
    // Expected: []

    // ---- Section 5: Search & Count ----
    std::cout << "\n--- Search & Count ---\n";

    std::cout << "find(nums, 30): " << find(nums, kThirty) << "\n";
    // Expected: find(nums, 30): 2

    std::cout << "find(nums, 99): " << find(nums, kNinetyNine) << "\n";
    // Expected: find(nums, 99): -1

    Container<int> repeated;
    repeated.add(1);
    repeated.add(2);
    repeated.add(3);
    repeated.add(2);
    repeated.add(2);

    std::cout << "count(repeated, 2): " << count(repeated, 2) << "\n";
    // Expected: count(repeated, 2): 3

    std::cout << "contains(nums, 20): " << contains(nums, kTwenty) << "\n";
    // Expected: contains(nums, 20): 1

    std::cout << "contains(nums, 99): " << contains(nums, kNinetyNine) << "\n";
    // Expected: contains(nums, 99): 0

    // ---- Section 6: Aggregates ----
    std::cout << "\n--- Aggregate Functions ---\n";

    std::cout << "sum(nums): " << sum(nums) << "\n";
    // Expected: sum(nums): 150

    std::cout << "min(nums): " << min(nums) << "\n";
    // Expected: min(nums): 10

    std::cout << "max(nums): " << max(nums) << "\n";
    // Expected: max(nums): 50

    Container<double> doubles;
    doubles.add(kPiApprox);
    doubles.add(kEulerApprox);
    doubles.add(kSqrtTwoApprox);

    std::cout << "sum(doubles): " << sum(doubles) << "\n";
    // Expected: sum(doubles): 7.26

    std::cout << "min(doubles): " << min(doubles) << "\n";
    // Expected: min(doubles): 1.41

    // ---- Section 7: Transform & Filter ----
    std::cout << "\n--- Transform & Filter ---\n";

    Container<int> vals;
    vals.add(1);
    vals.add(2);
    vals.add(3);
    vals.add(4);
    vals.add(kFive);

    transform(vals, [](int& valueRef) { valueRef *= 2; });
    print(vals);
    std::cout << "\n";
    // Expected: [2, 4, 6, 8, 10]

    Container<int> evens = filter(vals, [](const int& valueRef) { return valueRef % 4 == 0; });
    print(evens);
    std::cout << "\n";
    // Expected: [4, 8]

    // ---- Section 8: Reverse ----
    std::cout << "\n--- Reverse ---\n";

    Container<int> rev;
    rev.add(1);
    rev.add(2);
    rev.add(3);
    rev.add(4);

    reverse(rev);
    print(rev);
    std::cout << "\n";
    // Expected: [4, 3, 2, 1]

    // ---- Section 9: toString ----
    std::cout << "\n--- toString ---\n";

    std::string numsStr = toString(nums);
    std::cout << "toString: " << numsStr << "\n";
    // Expected: toString: [10, 20, 30, 40, 50]

    // ---- Section 10: Copy constructor & assignment ----
    std::cout << "\n--- Copy & Assignment ---\n";

    Container<int> numsCopy(nums);
    numsCopy.add(kSixty);
    std::cout << "Original count: " << nums.getCount()
              << ", Copy count: " << numsCopy.getCount() << "\n";
    // Expected: Original count: 5, Copy count: 6

    Container<int> numsAssign;
    numsAssign = nums;
    numsAssign.add(kSeventy);
    std::cout << "Original count: " << nums.getCount()
              << ", Assigned count: " << numsAssign.getCount() << "\n";
    // Expected: Original count: 5, Assigned count: 6

    // ---- Section 11: Stack ----
    std::cout << "\n--- Stack<int> ---\n";

    Stack<int> stack;
    stack.push(kOneHundred);
    stack.push(kTwoHundred);
    stack.push(kThreeHundred);

    std::cout << "Stack size: " << stack.size() << "\n";
    // Expected: Stack size: 3

    std::cout << "Top: " << stack.top() << "\n";
    // Expected: Top: 300

    print(stack);
    std::cout << "\n";
    // Expected: Stack(bottom -> top): [100, 200, 300]

    int popped = stack.pop();
    std::cout << "Popped: " << popped << "\n";
    // Expected: Popped: 300

    std::cout << "Top after pop: " << stack.top() << "\n";
    // Expected: Top after pop: 200

    std::cout << "Stack size after pop: " << stack.size() << "\n";
    // Expected: Stack size after pop: 2

    // Iterate over stack (bottom to top)
    std::cout << "Stack iterate: ";
    for (const int& val : stack) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    // Expected: Stack iterate: 100 200

    // ---- Section 12: Stack<string> ----
    std::cout << "\n--- Stack<string> ---\n";

    Stack<std::string> strStack;
    strStack.push("first");
    strStack.push("second");
    strStack.push("third");

    print(strStack);
    std::cout << "\n";
    // Expected: Stack(bottom -> top): [first, second, third]

    std::cout << "Top: " << strStack.top() << "\n";
    // Expected: Top: third

    // ---- Section 13: Queue ----
    std::cout << "\n--- Queue<int> ---\n";

    Queue<int> queue;
    queue.enqueue(kTen);
    queue.enqueue(kTwenty);
    queue.enqueue(kThirty);

    std::cout << "Queue size: " << queue.size() << "\n";
    // Expected: Queue size: 3

    std::cout << "Front: " << queue.front() << "\n";
    // Expected: Front: 10

    std::cout << "Back: " << queue.back() << "\n";
    // Expected: Back: 30

    print(queue);
    std::cout << "\n";
    // Expected: Queue(front -> back): [10, 20, 30]

    int dequeued = queue.dequeue();
    std::cout << "Dequeued: " << dequeued << "\n";
    // Expected: Dequeued: 10

    std::cout << "Front after dequeue: " << queue.front() << "\n";
    // Expected: Front after dequeue: 20

    // Iterate over queue (front to back)
    std::cout << "Queue iterate: ";
    for (const int& val : queue) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    // Expected: Queue iterate: 20 30

    // ---- Section 14: Exception handling ----
    std::cout << "\n--- Exception Handling ---\n";

    Stack<int> emptyStack;
    try {
        emptyStack.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Stack pop error: " << e.what() << "\n";
        // Expected: Stack pop error: Stack is empty
    }

    Queue<int> emptyQueue;
    try {
        emptyQueue.dequeue();
    } catch (const std::underflow_error& e) {
        std::cout << "Queue dequeue error: " << e.what() << "\n";
        // Expected: Queue dequeue error: Queue is empty
    }

    try {
        nums.get(kOneHundred);
    } catch (const std::out_of_range& e) {
        std::cout << "Container get error: " << e.what() << "\n";
        // Expected: Container get error: Index out of range
    }

    std::cout << "\n===== Demo Complete =====\n";

    return 0;
    } catch (const std::exception& exceptionValue) {
        std::cerr << "Unhandled exception: " << exceptionValue.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Unhandled non-standard exception\n";
        return 1;
    }
}

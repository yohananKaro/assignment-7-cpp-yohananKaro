/**
 * @file test.cpp
 * @brief Unit tests for Generic Container Library using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>

using namespace containers;

// ==================== CONTAINER<INT> TESTS ====================

TEST_CASE("Container<int> - Default Constructor") {
    Container<int> c;
    CHECK(c.getCount() == 0);
    CHECK(c.getCapacity() == 4);
    CHECK(c.isEmpty());
}

TEST_CASE("Container<int> - Parameterized Constructor") {
    Container<int> c(8);
    CHECK(c.getCapacity() == 8);
    CHECK(c.isEmpty());
}

TEST_CASE("Container<int> - Invalid Capacity Throws") {
    CHECK_THROWS_AS(Container<int>(0), std::invalid_argument);
    CHECK_THROWS_AS(Container<int>(-5), std::invalid_argument);
}

TEST_CASE("Container<int> - Add and Get") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    CHECK(c.getCount() == 3);
    CHECK(c.get(0) == 10);
    CHECK(c.get(1) == 20);
    CHECK(c.get(2) == 30);
}

TEST_CASE("Container<int> - Get Out of Bounds Throws") {
    Container<int> c;
    c.add(10);

    CHECK_THROWS_AS(c.get(1), std::out_of_range);
    CHECK_THROWS_AS(c.get(-1), std::out_of_range);
}

TEST_CASE("Container<int> - Resize on Overflow") {
    Container<int> c(2);
    c.add(1);
    c.add(2);
    CHECK(c.getCapacity() == 2);

    c.add(3);  // triggers resize
    CHECK(c.getCapacity() == 4);
    CHECK(c.getCount() == 3);
    CHECK(c.get(0) == 1);
    CHECK(c.get(1) == 2);
    CHECK(c.get(2) == 3);
}

TEST_CASE("Container<int> - RemoveAt") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    c.removeAt(1);  // remove 20
    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 10);
    CHECK(c.get(1) == 30);
}

TEST_CASE("Container<int> - RemoveAt First") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    c.removeAt(0);
    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 20);
    CHECK(c.get(1) == 30);
}

TEST_CASE("Container<int> - RemoveAt Last") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    c.removeAt(2);
    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 10);
    CHECK(c.get(1) == 20);
}

TEST_CASE("Container<int> - RemoveAt Out of Bounds Throws") {
    Container<int> c;
    c.add(10);

    CHECK_THROWS_AS(c.removeAt(1), std::out_of_range);
    CHECK_THROWS_AS(c.removeAt(-1), std::out_of_range);
}

TEST_CASE("Container<int> - Clear") {
    Container<int> c;
    c.add(10);
    c.add(20);

    c.clear();
    CHECK(c.getCount() == 0);
    CHECK(c.isEmpty());
    CHECK(c.getCapacity() == 4);  // capacity unchanged
}

TEST_CASE("Container<int> - Copy Constructor") {
    Container<int> c1;
    c1.add(10);
    c1.add(20);
    c1.add(30);

    Container<int> c2(c1);
    CHECK(c2.getCount() == 3);
    CHECK(c2.get(0) == 10);
    CHECK(c2.get(1) == 20);
    CHECK(c2.get(2) == 30);

    // Ensure deep copy
    c2.add(40);
    CHECK(c1.getCount() == 3);
    CHECK(c2.getCount() == 4);
}

TEST_CASE("Container<int> - Copy Assignment") {
    Container<int> c1;
    c1.add(10);
    c1.add(20);

    Container<int> c2;
    c2.add(99);
    c2 = c1;

    CHECK(c2.getCount() == 2);
    CHECK(c2.get(0) == 10);
    CHECK(c2.get(1) == 20);

    // Deep copy check
    c2.add(30);
    CHECK(c1.getCount() == 2);
}

TEST_CASE("Container<int> - Self Assignment") {
    Container<int> c;
    c.add(10);
    c.add(20);

    c = c;  // self-assignment
    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == 10);
    CHECK(c.get(1) == 20);
}

// ==================== CONTAINER ITERATOR TESTS ====================

TEST_CASE("Container<int> - Iterator Forward Traversal") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    int expected = 1;
    for (Container<int>::Iterator it = c.begin(); it != c.end(); ++it) {
        CHECK(*it == expected);
        expected++;
    }
}

TEST_CASE("Container<int> - Range-based For Loop") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    int total = 0;
    for (const int& val : c) {
        total += val;
    }
    CHECK(total == 60);
}

TEST_CASE("Container<string> - Range-based For Loop") {
    Container<std::string> c;
    c.add("hello");
    c.add("world");

    std::string result;
    for (const std::string& s : c) {
        result += s + " ";
    }
    CHECK(result == "hello world ");
}

TEST_CASE("Container - Empty Iterator") {
    Container<int> c;
    CHECK(c.begin() == c.end());
}

TEST_CASE("Container - Iterator Equality") {
    Container<int> c;
    c.add(1);
    auto it1 = c.begin();
    auto it2 = c.begin();
    CHECK(it1 == it2);
    CHECK_FALSE(it1 != it2);
}

// ==================== CONTAINER<STRING> TESTS ====================

TEST_CASE("Container<string> - Basic Operations") {
    Container<std::string> c;
    c.add("alpha");
    c.add("beta");
    c.add("gamma");

    CHECK(c.getCount() == 3);
    CHECK(c.get(0) == "alpha");
    CHECK(c.get(1) == "beta");
    CHECK(c.get(2) == "gamma");
}

TEST_CASE("Container<double> - Basic Operations") {
    Container<double> c;
    c.add(3.14);
    c.add(2.71);

    CHECK(c.getCount() == 2);
    CHECK(c.get(0) == doctest::Approx(3.14));
    CHECK(c.get(1) == doctest::Approx(2.71));
}

// ==================== STACK TESTS ====================

TEST_CASE("Stack<int> - Push and Top") {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    CHECK(s.size() == 3);
    CHECK(s.top() == 30);
}

TEST_CASE("Stack<int> - Pop") {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    CHECK(s.pop() == 30);
    CHECK(s.top() == 20);
    CHECK(s.size() == 2);

    CHECK(s.pop() == 20);
    CHECK(s.pop() == 10);
    CHECK(s.isEmpty());
}

TEST_CASE("Stack<int> - Pop Empty Throws") {
    Stack<int> s;
    CHECK_THROWS_AS(s.pop(), std::underflow_error);
}

TEST_CASE("Stack<int> - Top Empty Throws") {
    Stack<int> s;
    CHECK_THROWS_AS(s.top(), std::underflow_error);
}

TEST_CASE("Stack<int> - Iterator (Bottom to Top)") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    int expected = 1;
    for (const int& val : s) {
        CHECK(val == expected);
        expected++;
    }
}

TEST_CASE("Stack<string> - Push and Pop") {
    Stack<std::string> s;
    s.push("first");
    s.push("second");

    CHECK(s.top() == "second");
    CHECK(s.pop() == "second");
    CHECK(s.top() == "first");
}

TEST_CASE("Stack<int> - Copy Constructor") {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);

    Stack<int> s2(s1);
    CHECK(s2.size() == 2);
    CHECK(s2.top() == 20);

    // Deep copy
    s2.push(30);
    CHECK(s1.size() == 2);
    CHECK(s2.size() == 3);
}

TEST_CASE("Stack<int> - Copy Assignment") {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);

    Stack<int> s2;
    s2.push(99);
    s2 = s1;

    CHECK(s2.size() == 2);
    CHECK(s2.top() == 20);
}

TEST_CASE("Stack<int> - Mutable Top") {
    Stack<int> s;
    s.push(10);
    s.top() = 42;
    CHECK(s.top() == 42);
}

// ==================== QUEUE TESTS ====================

TEST_CASE("Queue<int> - Enqueue and Front/Back") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    CHECK(q.size() == 3);
    CHECK(q.front() == 10);
    CHECK(q.back() == 30);
}

TEST_CASE("Queue<int> - Dequeue") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    CHECK(q.dequeue() == 10);
    CHECK(q.front() == 20);
    CHECK(q.size() == 2);

    CHECK(q.dequeue() == 20);
    CHECK(q.dequeue() == 30);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue<int> - Dequeue Empty Throws") {
    Queue<int> q;
    CHECK_THROWS_AS(q.dequeue(), std::underflow_error);
}

TEST_CASE("Queue<int> - Front Empty Throws") {
    Queue<int> q;
    CHECK_THROWS_AS(q.front(), std::underflow_error);
}

TEST_CASE("Queue<int> - Back Empty Throws") {
    Queue<int> q;
    CHECK_THROWS_AS(q.back(), std::underflow_error);
}

TEST_CASE("Queue<int> - Iterator (Front to Back)") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    int expected = 10;
    for (const int& val : q) {
        CHECK(val == expected);
        expected += 10;
    }
}

TEST_CASE("Queue<string> - Enqueue and Dequeue") {
    Queue<std::string> q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");

    CHECK(q.front() == "first");
    CHECK(q.dequeue() == "first");
    CHECK(q.front() == "second");
}

TEST_CASE("Queue<int> - Copy Constructor") {
    Queue<int> q1;
    q1.enqueue(10);
    q1.enqueue(20);

    Queue<int> q2(q1);
    CHECK(q2.size() == 2);
    CHECK(q2.front() == 10);

    // Deep copy
    q2.enqueue(30);
    CHECK(q1.size() == 2);
    CHECK(q2.size() == 3);
}

TEST_CASE("Queue<int> - Copy Assignment") {
    Queue<int> q1;
    q1.enqueue(10);
    q1.enqueue(20);

    Queue<int> q2;
    q2.enqueue(99);
    q2 = q1;

    CHECK(q2.size() == 2);
    CHECK(q2.front() == 10);
}

// ==================== ALGORITHM: FIND / COUNT / CONTAINS TESTS ====================

TEST_CASE("find - Element Found") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    CHECK(find(c, 10) == 0);
    CHECK(find(c, 20) == 1);
    CHECK(find(c, 30) == 2);
}

TEST_CASE("find - Element Not Found") {
    Container<int> c;
    c.add(10);
    c.add(20);

    CHECK(find(c, 99) == -1);
}

TEST_CASE("find - Empty Container") {
    Container<int> c;
    CHECK(find(c, 1) == -1);
}

TEST_CASE("find - String") {
    Container<std::string> c;
    c.add("apple");
    c.add("banana");
    c.add("cherry");

    CHECK(find(c, std::string("banana")) == 1);
    CHECK(find(c, std::string("grape")) == -1);
}

TEST_CASE("count - Multiple Occurrences") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(2);
    c.add(3);
    c.add(2);

    CHECK(count(c, 2) == 3);
    CHECK(count(c, 1) == 1);
    CHECK(count(c, 5) == 0);
}

TEST_CASE("contains - Found and Not Found") {
    Container<int> c;
    c.add(10);
    c.add(20);

    CHECK(contains(c, 10) == true);
    CHECK(contains(c, 30) == false);
}

// ==================== ALGORITHM: PRINT TESTS ====================

TEST_CASE("print - Container<int> to stream") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    std::ostringstream oss;
    print(c, oss);
    CHECK(oss.str() == "[1, 2, 3]");
}

TEST_CASE("print - Empty Container") {
    Container<int> c;
    std::ostringstream oss;
    print(c, oss);
    CHECK(oss.str() == "[]");
}

TEST_CASE("print - Container<string>") {
    Container<std::string> c;
    c.add("a");
    c.add("b");

    std::ostringstream oss;
    print(c, oss);
    CHECK(oss.str() == "[a, b]");
}

TEST_CASE("print - Stack<int>") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    std::ostringstream oss;
    print(s, oss);
    CHECK(oss.str() == "Stack(bottom -> top): [1, 2, 3]");
}

TEST_CASE("print - Empty Stack") {
    Stack<int> s;
    std::ostringstream oss;
    print(s, oss);
    CHECK(oss.str() == "Stack(bottom -> top): []");
}

TEST_CASE("print - Queue<int>") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::ostringstream oss;
    print(q, oss);
    CHECK(oss.str() == "Queue(front -> back): [10, 20, 30]");
}

TEST_CASE("print - Empty Queue") {
    Queue<int> q;
    std::ostringstream oss;
    print(q, oss);
    CHECK(oss.str() == "Queue(front -> back): []");
}

// ==================== ALGORITHM: TRANSFORM & FILTER TESTS ====================

TEST_CASE("transform - Double values") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    transform(c, [](int& x) { x *= 2; });
    CHECK(c.get(0) == 2);
    CHECK(c.get(1) == 4);
    CHECK(c.get(2) == 6);
}

TEST_CASE("transform - String to uppercase first char") {
    Container<std::string> c;
    c.add("hello");
    c.add("world");

    transform(c, [](std::string& s) {
        if (!s.empty()) {
            s[0] = static_cast<char>(toupper(s[0]));
        }
    });
    CHECK(c.get(0) == "Hello");
    CHECK(c.get(1) == "World");
}

TEST_CASE("filter - Even numbers") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    c.add(4);
    c.add(5);

    Container<int> evens = filter(c, [](const int& x) { return x % 2 == 0; });
    CHECK(evens.getCount() == 2);
    CHECK(evens.get(0) == 2);
    CHECK(evens.get(1) == 4);
}

TEST_CASE("filter - No matches") {
    Container<int> c;
    c.add(1);
    c.add(3);
    c.add(5);

    Container<int> evens = filter(c, [](const int& x) { return x % 2 == 0; });
    CHECK(evens.getCount() == 0);
    CHECK(evens.isEmpty());
}

TEST_CASE("filter - All match") {
    Container<int> c;
    c.add(2);
    c.add(4);

    Container<int> evens = filter(c, [](const int& x) { return x % 2 == 0; });
    CHECK(evens.getCount() == 2);
}

TEST_CASE("filter - Strings by length") {
    Container<std::string> c;
    c.add("hi");
    c.add("hello");
    c.add("hey");
    c.add("wonderful");

    Container<std::string> long_words = filter(c, [](const std::string& s) {
        return s.length() > 3;
    });
    CHECK(long_words.getCount() == 2);
    CHECK(long_words.get(0) == "hello");
    CHECK(long_words.get(1) == "wonderful");
}

// ==================== ALGORITHM: AGGREGATE TESTS ====================

TEST_CASE("sum - int") {
    Container<int> c;
    c.add(10);
    c.add(20);
    c.add(30);

    CHECK(sum(c) == 60);
}

TEST_CASE("sum - double") {
    Container<double> c;
    c.add(1.5);
    c.add(2.5);
    c.add(3.0);

    CHECK(sum(c) == doctest::Approx(7.0));
}

TEST_CASE("sum - empty container") {
    Container<int> c;
    CHECK(sum(c) == 0);
}

TEST_CASE("sum - string concatenation") {
    Container<std::string> c;
    c.add("hello");
    c.add(" ");
    c.add("world");

    CHECK(sum(c) == "hello world");
}

TEST_CASE("min - int") {
    Container<int> c;
    c.add(30);
    c.add(10);
    c.add(20);

    CHECK(min(c) == 10);
}

TEST_CASE("min - empty throws") {
    Container<int> c;
    CHECK_THROWS_AS(min(c), std::underflow_error);
}

TEST_CASE("max - int") {
    Container<int> c;
    c.add(30);
    c.add(10);
    c.add(50);
    c.add(20);

    CHECK(max(c) == 50);
}

TEST_CASE("max - empty throws") {
    Container<int> c;
    CHECK_THROWS_AS(max(c), std::underflow_error);
}

TEST_CASE("min/max - single element") {
    Container<int> c;
    c.add(42);

    CHECK(min(c) == 42);
    CHECK(max(c) == 42);
}

TEST_CASE("min/max - strings") {
    Container<std::string> c;
    c.add("banana");
    c.add("apple");
    c.add("cherry");

    CHECK(min(c) == "apple");
    CHECK(max(c) == "cherry");
}

// ==================== ALGORITHM: TOSTRING & REVERSE TESTS ====================

TEST_CASE("toString - int") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    CHECK(toString(c) == "[1, 2, 3]");
}

TEST_CASE("toString - empty") {
    Container<int> c;
    CHECK(toString(c) == "[]");
}

TEST_CASE("reverse - int") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    c.add(4);

    reverse(c);
    CHECK(c.get(0) == 4);
    CHECK(c.get(1) == 3);
    CHECK(c.get(2) == 2);
    CHECK(c.get(3) == 1);
}

TEST_CASE("reverse - odd count") {
    Container<int> c;
    c.add(1);
    c.add(2);
    c.add(3);

    reverse(c);
    CHECK(c.get(0) == 3);
    CHECK(c.get(1) == 2);
    CHECK(c.get(2) == 1);
}

TEST_CASE("reverse - single element") {
    Container<int> c;
    c.add(42);

    reverse(c);
    CHECK(c.get(0) == 42);
}

TEST_CASE("reverse - empty") {
    Container<int> c;
    reverse(c);  // should not crash
    CHECK(c.isEmpty());
}

TEST_CASE("reverse - strings") {
    Container<std::string> c;
    c.add("a");
    c.add("b");
    c.add("c");

    reverse(c);
    CHECK(c.get(0) == "c");
    CHECK(c.get(1) == "b");
    CHECK(c.get(2) == "a");
}

// ==================== EDGE-CASE TESTS ====================

TEST_CASE("Container<int> - RemoveAt Single Element") {
    Container<int> c;
    c.add(42);

    c.removeAt(0);
    CHECK(c.getCount() == 0);
    CHECK(c.isEmpty());
}

TEST_CASE("Container<int> - Multiple Resizes") {
    Container<int> c(2);
    for (int i = 0; i < 10; i++) {
        c.add(i);
    }
    CHECK(c.getCount() == 10);
    CHECK(c.getCapacity() >= 10);
    for (int i = 0; i < 10; i++) {
        CHECK(c.get(i) == i);
    }
}

TEST_CASE("Stack<int> - Self Assignment") {
    Stack<int> s;
    s.push(10);
    s.push(20);

    s = s;  // self-assignment
    CHECK(s.size() == 2);
    CHECK(s.top() == 20);
}

TEST_CASE("Queue<int> - Self Assignment") {
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);

    q = q;  // self-assignment
    CHECK(q.size() == 2);
    CHECK(q.front() == 10);
}

TEST_CASE("transform - Empty Container") {
    Container<int> c;
    transform(c, [](int& x) { x *= 2; });
    CHECK(c.isEmpty());
}

TEST_CASE("filter - Empty Container") {
    Container<int> c;
    Container<int> result = filter(c, [](const int& x) { return x % 2 == 0; });
    CHECK(result.isEmpty());
}

TEST_CASE("Stack<int> - Const Top") {
    Stack<int> s;
    s.push(10);
    s.push(20);

    const Stack<int>& cs = s;
    CHECK(cs.top() == 20);
}

// ==================== STUDENT TEST FILE CHECK ====================

TEST_CASE("StudentTest - File exists") {
    std::ifstream f("StudentTest.cpp");
    CHECK_MESSAGE(f.good(), "StudentTest.cpp not found. You must create StudentTest.cpp with at least 20 test cases.");
}
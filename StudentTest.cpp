/**
 * @file StudentTest.cpp
 * @brief Student-authored unit tests for Generic Container Library
 *
 * Contains at least 20 additional test cases covering edge cases,
 * error scenarios, and various type combinations.
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Container.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include <string>
#include <sstream>

using namespace containers;

// Container tests

TEST_CASE("Container<int> - Add after clear retains capacity") {
    Container<int> c(2);
    c.add(1);
    c.add(2);
    c.clear();
    CHECK(c.getCapacity() == 2);
    c.add(10);
    CHECK(c.getCount() == 1);
    CHECK(c.get(0) == 10);
}

TEST_CASE("Container<int> - Multiple resizes grow capacity correctly") {
    Container<int> c(1);
    CHECK(c.getCapacity() == 1);
    c.add(1);
    c.add(2);  // resize → 2
    CHECK(c.getCapacity() == 2);
    c.add(3);  // resize → 4
    CHECK(c.getCapacity() == 4);
    c.add(4);
    c.add(5);  // resize → 8
    CHECK(c.getCapacity() == 8);
}

TEST_CASE("Container<int> - RemoveAt preserves remaining order") {
    Container<int> c;
    for (int i = 0; i < 5; i++) {
        c.add(i * 10);
    }
    c.removeAt(2);  // remove 20
    CHECK(c.getCount() == 4);
    CHECK(c.get(0) == 0);
    CHECK(c.get(1) == 10);
    CHECK(c.get(2) == 30);
    CHECK(c.get(3) == 40);
}

TEST_CASE("Container<int> - Get out of range with empty container") {
    Container<int> c;
    CHECK_THROWS_AS(c.get(0), std::out_of_range);
}

TEST_CASE("Container<int> - Copy assignment replaces old data") {
    Container<int> c1;
    c1.add(1);
    c1.add(2);

    Container<int> c2;
    c2.add(100);
    c2.add(200);
    c2.add(300);

    c2 = c1;
    CHECK(c2.getCount() == 2);
    CHECK(c2.get(0) == 1);
    CHECK(c2.get(1) == 2);
}

TEST_CASE("Container<double> - Resize preserves double values") {
    Container<double> c(2);
    c.add(1.1);
    c.add(2.2);
    c.add(3.3);  // resize
    CHECK(c.get(0) == doctest::Approx(1.1));
    CHECK(c.get(1) == doctest::Approx(2.2));
    CHECK(c.get(2) == doctest::Approx(3.3));
}

// Iterator tests

TEST_CASE("Container<int> - Iterator with single element") {
    Container<int> c;
    c.add(42);
    auto it = c.begin();
    CHECK(*it == 42);
    ++it;
    CHECK(it == c.end());
}

TEST_CASE("Container<string> - Iterator concatenation") {
    Container<std::string> c;
    c.add("a");
    c.add("b");
    c.add("c");

    std::string result;
    for (const auto& s : c) {
        result += s;
    }
    CHECK(result == "abc");
}

// Stack tests

TEST_CASE("Stack<int> - Push pop push cycle") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    CHECK(s.pop() == 2);
    s.push(3);
    CHECK(s.top() == 3);
    CHECK(s.size() == 2);
}

TEST_CASE("Stack<int> - Pop all elements then throw") {
    Stack<int> s;
    s.push(10);
    s.push(20);
    CHECK(s.pop() == 20);
    CHECK(s.pop() == 10);
    CHECK(s.isEmpty());
    CHECK_THROWS_AS(s.pop(), std::underflow_error);
}

TEST_CASE("Stack<string> - Copy preserves independence") {
    Stack<std::string> s1;
    s1.push("hello");
    s1.push("world");

    Stack<std::string> s2(s1);
    s2.push("extra");
    CHECK(s1.size() == 2);
    CHECK(s2.size() == 3);
}

// Queue tests

TEST_CASE("Queue<int> - Enqueue dequeue interleaved") {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    CHECK(q.dequeue() == 1);
    q.enqueue(3);
    CHECK(q.front() == 2);
    CHECK(q.back() == 3);
    CHECK(q.size() == 2);
}

TEST_CASE("Queue<int> - Dequeue all then throw") {
    Queue<int> q;
    q.enqueue(5);
    CHECK(q.dequeue() == 5);
    CHECK(q.isEmpty());
    CHECK_THROWS_AS(q.dequeue(), std::underflow_error);
    CHECK_THROWS_AS(q.front(), std::underflow_error);
    CHECK_THROWS_AS(q.back(), std::underflow_error);
}

TEST_CASE("Queue<string> - FIFO order verified") {
    Queue<std::string> q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");

    CHECK(q.dequeue() == "first");
    CHECK(q.dequeue() == "second");
    CHECK(q.dequeue() == "third");
}

// Algorithm tests

TEST_CASE("find - First occurrence returned") {
    Container<int> c;
    c.add(5);
    c.add(3);
    c.add(5);
    c.add(3);

    CHECK(find(c, 3) == 1);
    CHECK(find(c, 5) == 0);
}

TEST_CASE("count - Zero for empty container") {
    Container<int> c;
    CHECK(count(c, 42) == 0);
}

TEST_CASE("contains - String container") {
    Container<std::string> c;
    c.add("cat");
    c.add("dog");

    CHECK(contains(c, std::string("cat")) == true);
    CHECK(contains(c, std::string("bird")) == false);
}

TEST_CASE("sum - Single element") {
    Container<int> c;
    c.add(99);
    CHECK(sum(c) == 99);
}

TEST_CASE("transform - Negate values") {
    Container<int> c;
    c.add(1);
    c.add(-2);
    c.add(3);

    transform(c, [](int& x) { x = -x; });
    CHECK(c.get(0) == -1);
    CHECK(c.get(1) == 2);
    CHECK(c.get(2) == -3);
}

TEST_CASE("filter - String filter by first letter") {
    Container<std::string> c;
    c.add("apple");
    c.add("banana");
    c.add("avocado");
    c.add("blueberry");

    Container<std::string> aWords = filter(c, [](const std::string& s) {
        return !s.empty() && s[0] == 'a';
    });
    CHECK(aWords.getCount() == 2);
    CHECK(aWords.get(0) == "apple");
    CHECK(aWords.get(1) == "avocado");
}

TEST_CASE("reverse - Two elements") {
    Container<int> c;
    c.add(1);
    c.add(2);

    reverse(c);
    CHECK(c.get(0) == 2);
    CHECK(c.get(1) == 1);
}

TEST_CASE("toString - String container") {
    Container<std::string> c;
    c.add("x");
    c.add("y");

    CHECK(toString(c) == "[x, y]");
}

TEST_CASE("toString - Single element") {
    Container<int> c;
    c.add(42);
    CHECK(toString(c) == "[42]");
}

TEST_CASE("print - Stack<string> to stream") {
    Stack<std::string> s;
    s.push("a");
    s.push("b");

    std::ostringstream oss;
    print(s, oss);
    CHECK(oss.str() == "Stack(bottom -> top): [a, b]");
}

TEST_CASE("print - Queue<string> to stream") {
    Queue<std::string> q;
    q.enqueue("x");
    q.enqueue("y");

    std::ostringstream oss;
    print(q, oss);
    CHECK(oss.str() == "Queue(front -> back): [x, y]");
}

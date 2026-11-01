#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstddef>
#include <stdexcept>

namespace containers {

// Default initial capacity
constexpr int DEFAULT_CAPACITY = 4;

// Generic dynamic array container
template <typename T>
class Container {
private:
    T* data_;
    int count_;
    int capacity_;

    // Doubles the capacity when full
    void resize() {
        int newCapacity = capacity_ * 2;
        T* newData = new T[static_cast<size_t>(newCapacity)];  // NOLINT(cppcoreguidelines-owning-memory)
        for (int i = 0; i < count_; i++) {
            newData[i] = data_[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
        delete[] data_;
        data_ = newData;  // NOLINT(cppcoreguidelines-owning-memory)
        capacity_ = newCapacity;
    }

public:
    // Forward iterator
    class Iterator {
    private:
        T* ptr_;

    public:
        explicit Iterator(T* ptr) : ptr_(ptr) {}

        T& operator*() const {
            return *ptr_;
        }

        Iterator& operator++() {
            ++ptr_;  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }
    };

    // Default constructor
    Container() : data_(new T[DEFAULT_CAPACITY]), count_(0), capacity_(DEFAULT_CAPACITY) {}  // NOLINT(cppcoreguidelines-owning-memory)

    // Parameterized constructor
    explicit Container(int capacity) : data_(nullptr), count_(0), capacity_(capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Invalid capacity");
        }
        data_ = new T[static_cast<size_t>(capacity)];  // NOLINT(cppcoreguidelines-owning-memory)
    }

    // Copy constructor (deep copy)
    Container(const Container& other)
        : data_(new T[static_cast<size_t>(other.capacity_)]),  // NOLINT(cppcoreguidelines-owning-memory)
          count_(other.count_),
          capacity_(other.capacity_) {
        for (int i = 0; i < count_; i++) {
            data_[i] = other.data_[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
    }

    // Copy assignment
    Container& operator=(const Container& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.capacity_;
            count_ = other.count_;
            data_ = new T[static_cast<size_t>(capacity_)];  // NOLINT(cppcoreguidelines-owning-memory)
            for (int i = 0; i < count_; i++) {
                data_[i] = other.data_[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            }
        }
        return *this;
    }

    // Destructor
    ~Container() {
        delete[] data_;
    }

    // Add element to end
    void add(const T& value) {
        if (count_ == capacity_) {
            resize();
        }
        data_[count_] = value;  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        count_++;
    }

    // Element access by index
    T& get(int index) {
        if (index < 0 || index >= count_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    const T& get(int index) const {
        if (index < 0 || index >= count_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    // Remove element at index and shift remaining
    void removeAt(int index) {
        if (index < 0 || index >= count_) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < count_ - 1; i++) {
            data_[i] = data_[i + 1];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        }
        count_--;
    }

    // Reset container count
    void clear() {
        count_ = 0;
    }

    int getCount() const {
        return count_;
    }

    int getCapacity() const {
        return capacity_;
    }

    bool isEmpty() const {
        return count_ == 0;
    }

    // Iterator support
    Iterator begin() {
        return Iterator(data_);
    }

    Iterator end() {
        return Iterator(data_ + count_);  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }

    Iterator begin() const {
        return Iterator(data_);
    }

    Iterator end() const {
        return Iterator(data_ + count_);  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
};

}  // namespace containers

#endif  // CONTAINER_HPP

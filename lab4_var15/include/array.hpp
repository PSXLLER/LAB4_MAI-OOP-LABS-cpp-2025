#pragma once
#include <memory>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Array 
{
private:
    size_t size_{0};
    size_t capacity_{0};
    std::shared_ptr<std::shared_ptr<T>[]> data_;

    void reallocate(size_t new_capacity);

public:
    Array() = default;
    explicit Array(size_t n);

    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    void push_back(const std::shared_ptr<T>& value);
    void erase(size_t index);
    void clear();

    std::shared_ptr<T>& operator[](size_t index);
    const std::shared_ptr<T>& operator[](size_t index) const;

    double total_area() const;
    void print_centers() const;
};

#include "array.hpp"
#include "figure.hpp"

template <typename T>
void Array<T>::reallocate(size_t new_capacity)
{
    std::unique_ptr<std::shared_ptr<T>[]> new_data(
        new std::shared_ptr<T>[new_capacity]
    );

    for (size_t i = 0; i < size_; ++i)
        new_data[i] = std::move(data_[i]);

    data_ = std::move(new_data);
    capacity_ = new_capacity;
}

template <typename T>
Array<T>::Array(size_t n) : size_(0), capacity_(n)
{
    data_ = std::unique_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[n]);
}

template <typename T>
Array<T>::Array(const Array& other)
    : size_(other.size_), capacity_(other.capacity_)
{
    data_ = std::unique_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity_]);
    for (size_t i = 0; i < size_; ++i)
        data_[i] = other.data_[i];
}

template <typename T>
Array<T>::Array(Array&& other) noexcept
    : size_(other.size_)
    , capacity_(other.capacity_)
    , data_(std::move(other.data_))
{
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;

        data_ = std::unique_ptr<std::shared_ptr<T>[]>(new std::shared_ptr<T>[capacity_]);
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }
    return *this;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept
{
    if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::move(other.data_);
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
void Array<T>::push_back(const std::shared_ptr<T>& value)
{
    if (size_ == capacity_) 
    {
        size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
        reallocate(new_cap);
    }
    data_[size_++] = value;
}

template <typename T>
void Array<T>::erase(size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");

    for (size_t i = index; i < size_ - 1; ++i)
        data_[i] = std::move(data_[i + 1]);

    --size_;
}

template <typename T>
void Array<T>::clear()
{
    data_.reset();
    size_ = 0;
    capacity_ = 0;
}

template <typename T>
std::shared_ptr<T>& Array<T>::operator[](size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
const std::shared_ptr<T>& Array<T>::operator[](size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Index out of range");
    return data_[index];
}

template <typename T>
double Array<T>::total_area() const
{
    double sum = 0.0;
    for (size_t i = 0; i < size_; ++i)
        if (data_[i])
            sum += data_[i]->area();
    return sum;
}

template <typename T>
void Array<T>::print_centers() const
{
    for (size_t i = 0; i < size_; ++i) 
    {
        if (data_[i]) {
            auto c = data_[i]->center();
            std::cout << "Figure " << i << " center: (" << c.x << ", " << c.y << ")\n";
        }
    }
}

template class Array<Figure<int>>;
template class Array<Figure<double>>;

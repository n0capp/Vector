#include <algorithm>
#include "vector.h"

Vector::Iterator::Iterator() {
    ptr_ = nullptr;
}

Vector::Iterator::Iterator(ValueType *pointer) {
    ptr_ = pointer;
}

Vector::ValueType *Vector::Iterator::operator->() const {
    return ptr_;
}

Vector::ValueType &Vector::Iterator::operator*() const {
    return *ptr_;
}

Vector::Iterator &Vector::Iterator::operator=(Vector::Iterator other) {
    ptr_ = other.ptr_;
    return *this;
}

Vector::Iterator &Vector::Iterator::operator++() {
    ++ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    auto postfix_increment = Vector::Iterator(ptr_++);
    return postfix_increment;
}

Vector::Iterator &Vector::Iterator::operator--() {
    --ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    auto postfix_decrement = Vector::Iterator(ptr_--);
    return postfix_decrement;
}

Vector::Iterator Vector::Iterator::operator+(DifferenceType shift) {
    return Vector::Iterator(ptr_ + shift);
}

Vector::DifferenceType Vector::Iterator::operator-(Iterator other) {
    return ptr_ - other.ptr_;
}

Vector::Iterator &Vector::Iterator::operator+=(DifferenceType shift) {
    ptr_ += shift;
    return *this;
}

Vector::Iterator &Vector::Iterator::operator-=(DifferenceType shift) {
    ptr_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Iterator &other) const {
    return ptr_ == other.ptr_;
}

bool Vector::Iterator::operator!=(const Iterator &other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Iterator &other) const {
    return ptr_ <=> other.ptr_;
}

Vector::Vector() {
    size_ = 0;
    cap_ = 0;
    buf_ = nullptr;
}

Vector::Vector(size_t size) {
    size_ = size;
    cap_ = size;
    buf_ = new Vector::ValueType[size];
    for (size_t i = 0; i < size_; ++i) {
        buf_[i] = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    size_ = list.size();
    cap_ = size_;
    buf_ = new Vector::ValueType[size_];
    auto it = list.begin();
    for (size_t i = 0; i < size_; ++i) {
        buf_[i] = *it;
        ++it;
    }
}

Vector::Vector(const Vector &other) {
    size_ = other.size_;
    cap_ = other.cap_;
    buf_ = other.buf_;
}

Vector &Vector::operator=(const Vector &other) {
    size_ = other.size_;
    cap_ = other.cap_;
    if (buf_) {
        delete[] buf_;
    }
    buf_ = new int[size_];
    for (size_t i = 0; i < other.size_; ++i) {
        buf_[i] = other.buf_[i];
    }
    return *this;
}

Vector::~Vector() {
    if (buf_) {
        delete[] buf_;
    }
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return cap_;
}

const Vector::ValueType *Vector::Data() const {
    return buf_;
}

Vector::ValueType &Vector::operator[](size_t position) {
    return buf_[position];
}

Vector::ValueType Vector::operator[](size_t position) const {
    return buf_[position];
}

std::strong_ordering Vector::operator<=>(const Vector &other) const {
    for (size_t i = 0; i < std::min(size_, other.size_); ++i) {
        auto equality = buf_[i] <=> other.buf_[i];
        if (equality != std::strong_ordering::equal) {
            return equality;
        }
    }
    return size_ <=> other.size_;
}

bool Vector::operator==(const Vector &other) const {
    auto equality = (*this <=> other);
    return equality == std::strong_ordering::equal;
}

bool Vector::operator!=(const Vector &other) const {
    return !(*this == other);
}

void Vector::Reserve(SizeType new_capacity) {
    if (new_capacity <= cap_) {
        return;
    }
    cap_ = new_capacity;
    ValueType *buf2 = new ValueType[cap_];
    for (size_t i = 0; i < size_; ++i) {
        buf2[i] = buf_[i];
    }
    if (buf_) {
        delete[] buf_;
    }
    buf_ = buf2;
}

void Vector::Clear() {
    size_ = 0;
}

void Vector::PushBack(const Vector::ValueType &new_element) {
    if (size_ == cap_) {
        Reserve(std::max(size_ * 2, static_cast<size_t>(1)));
    }
    buf_[size_++] = new_element;
}

void Vector::PopBack() {
    --size_;
}

void Vector::Swap(Vector &other) {
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
    std::swap(buf_, other.buf_);
}

Vector::Iterator Vector::Begin() {
    return Vector::Iterator(buf_);
}

Vector::Iterator Vector::begin() {
    return Begin();
}

Vector::Iterator Vector::End() {
    return Vector::Iterator(buf_ + size_);
}

Vector::Iterator Vector::end() {
    return End();
}
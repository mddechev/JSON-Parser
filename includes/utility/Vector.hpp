#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <stdexcept>
#include <exception>
#include <utility>
#include <cstddef>
#include <new>

template<typename T>
class Vector {
public:
    Vector();
    Vector(size_t capacity);
    Vector(size_t capacity, const T& defaultValue);
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector<T>&& other) noexcept;

    T& operator[](size_t position);
    const T& operator[](size_t position) const;

    size_t Capacity() const { return capacity; }
    size_t Size() const { return size; }
    T& Begin() { return data[0]; }
    const T& Begin() const { return data[0]; }
    T& Back() { return data[size - 1]; }
    const T& Back() const { return data[size - 1]; }

    void PushBack(const T& value);
    void PushBack(T&& value);

    const T& At(size_t index) const;
    T& At(size_t index);

    void PopBack();
    void PopFront();
    void EraseAt(size_t position);
    void Insert(size_t position, const T& value);
    void Clear();
    void Print(std::ostream& outputStream = std::cout, const char delimiter = ' ') const;

    bool Contains(const T& value) const;
    bool IsEmpty() const;

    void Reserve(size_t newCapacity);

private:
    void Resize(size_t step = INCREMENT_STEP);
    void Copy(const Vector<T>& other);
    void Move(Vector<T>&& other) noexcept;
    void Free();

private:
    static const size_t INITIAL_CAPACITY = 4;
    static const size_t INITIAL_SIZE = 0;
    static const size_t INCREMENT_STEP = 2;

private:
    size_t capacity;
    size_t size;
    T* data;
};

template<typename T>
Vector<T>::Vector()
    :capacity(INITIAL_CAPACITY), size(INITIAL_SIZE), data(new T[capacity])
{
    // data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(size_t capacity)
    : capacity(capacity), size(INITIAL_SIZE), data(new T[capacity])
{
    // this->data = new T[capacity];
    // this->capacity = capacity;
}

template<typename T>
Vector<T>::Vector(size_t size, const T& defaultVal)
   : capacity(size* INCREMENT_STEP), size(size), data(new T[capacity])
{
    
    // this->size = size;
    // this->capacity = size * INCREMENT_STEP;
    // this->data= new T[this->capacity];
    
    for (size_t i = 0; i < size; i++) {
        this->data[i] = defaultVal;
    }
}
 
template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
    Copy(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept {
    Move(std::move(other));
}

template <typename T>
Vector<T>::~Vector<T>() {
    Free();
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        Free();
        Copy(other);
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
    if (this != &other) {
        Free();
        Move(std::move(other));
    }
    return *this;
}

template<typename T>
T& Vector<T>::operator[](size_t position) {
    return At(position);
}

template<typename T>
const T& Vector<T>::operator[](size_t position) const {
    return At(position);
}

template<typename T>
void Vector<T>::PushBack(const T& value) {
    if (size == capacity) {
        Resize();
    }
    data[size++] = value;
}

template<typename T>
void Vector<T>::PushBack(T&& value) {
    if (size == capacity) {
        Resize();
    }
    data[size++] = std::move(value);
}

template<typename T>
const T& Vector<T>::At(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Position out of range!");
    }
    return data[index];
}

template<typename T>
T& Vector<T>::At(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Position out of range!");
    }
    return data[index];
}

template<typename T>
void Vector<T>::PopBack() {
    if (IsEmpty()) {
        return;
    }
    size--;
}

template<typename T>
void Vector<T>::PopFront() {
    if (IsEmpty()) {
        return;
    }
    for (size_t i = 0; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
void Vector<T>::EraseAt(size_t position) {
    if (position > size) {
        throw std::out_of_range("Position argument is out of range!");
    }
    for (size_t i = position; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template<typename T>
void Vector<T>::Insert(size_t position, const T& value) {
    if (position >= size) {
        throw std::out_of_range("Positon argument is out of range!");
    }
    if (size == capacity) {
        Resize();
    }
    for (size_t i = size; i > position; i--) {
        data[i] = data[i - 1];
    }
    data[position] = value;
    size++;
}

template<typename T>
void Vector<T>::Clear() {
    Free();
    size = 0;
    capacity = 0;
}

template<typename T>
void Vector<T>::Print(std::ostream& outputStream, const char delimeter) const {
    for (size_t i = 0; i < size; i++) {
        outputStream << data[i] << delimeter;
    }
}

template<typename T>
bool Vector<T>::Contains(const T& value) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool Vector<T>::IsEmpty() const {
    return size == 0;
}

template <typename T>
void Vector<T>::Reserve(size_t newCapacity) {
    if (newCapacity > capacity) {
        T* newData = new T[newCapacity];

        for (size_t i = 0; i < size; i++) {
            newData[i] = std::move(data[i]);
        }

        Free();
        data = newData;
        capacity = newCapacity;
    }
}

template<typename T>
void Vector<T>::Resize(size_t step) {
    size_t newCap = capacity * step;
    T* newData = new T[newCap];
    
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    Free();

    data = newData;
    capacity = newCap;
}

template<typename T>
void Vector<T>::Copy(const Vector<T>& other) {
    this->data = new T[other.capacity];
    if (!this->data) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < other.size; i++) {
        this->data[i] = other.data[i];
    }
    this->capacity = other.capacity;
    this->size = other.size;
}

template<typename T>
void Vector<T>::Move(Vector<T>&& other) noexcept {
    this->data = other.data;
    this->capacity = other.capacity;
    this->size = other.size;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
void Vector<T>::Free() {
    delete[] data;
    this->data = nullptr;
}


#endif //_MY_VECTOR_HPP_
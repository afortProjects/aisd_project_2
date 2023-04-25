#pragma once
#include "consts.h"
#include <iostream>
template<typename T> class myVector {
private:
	T* arr;
	size_t size;
	size_t capacity;
public:
	myVector() : size(0), capacity(VECTOR_BUFFER) {
		arr = new T[capacity];
	}

	myVector(const myVector& other) : size(other.size), capacity(other.capacity), arr(new T[other.capacity]) {
		for (size_t i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
	}

	myVector(myVector&& other) : size(other.size), capacity(other.capacity), arr(other.arr) {
		other.size = 0;
		other.capacity = 0;
		other.arr = nullptr;
	}

	~myVector() {
		delete[] this->arr;
	}
		
	myVector& operator=(const myVector& other) {
		if (this != &other) { // check for self-assignment
			size = other.size;
			capacity = other.capacity;
			delete[] arr;
			arr = new T[capacity];
			for (size_t i = 0; i < size; i++) {
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}

	myVector& operator=(myVector&& other) noexcept {
		if (this != &other) { // check for self-assignment
			size = other.size;
			capacity = other.capacity;
			delete[] arr;
			arr = other.arr;
			other.size = 0;
			other.capacity = 0;
			other.arr = nullptr;
		}
		return *this;
	}

	void reserveNewCapacity(size_t newCapacity) {
		if (newCapacity <= this->capacity) {
			return;
		}
		T* newArr = new T[newCapacity];
		for (size_t i = 0; i < this->size; i++) {
			newArr[i] = this->arr[i];
		}
		delete[] arr;
		this->arr = newArr;
		this->capacity = newCapacity;
	}

	void push_front(T value) {
		if (size == capacity) {
			reserveNewCapacity(capacity + VECTOR_BUFFER);
		}
		for (size_t i = size; i > 0; i--) {
			arr[i] = arr[i - 1];
		}
		this->arr[0] = value;
		this->size++;
	}

	void push_back(T value) {
		if (this->size == this->capacity) {
			reserveNewCapacity(this->capacity + VECTOR_BUFFER);
		}
		this->arr[this->size] = value;
		this->size++;
	}

	void pop_front() {
		if (size == 0) {
			return;
		}
		for (size_t i = 1; i < size; i++) {
			arr[i - 1] = arr[i];
		}
		size--;
	}

	void pop_back() {
		if (this->size == 0) {
			return;
		}
		this->arr[this->size - 1].~T();
		this->size--;
	}

	T& operator[](int index) {
		return this->arr[index];
	}

	size_t getSize() const {
		return this->size;
	}

	friend std::ostream& operator<<(std::ostream& os, const myVector<T>& obj) {
		for (size_t i = 0; i < obj.size; i++) {
			os << obj.arr[i] << ' ';
		}
		return os;
	}
};
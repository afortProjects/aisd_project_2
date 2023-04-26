#include "my_vector.h"
template<typename T> class myQueue {
private:
	myVector<T> data;
public:
	myQueue() {}

	void addElementToQueue(T value) {
		data.push_back(value);
	}

	T getElementFromQueue() {
		T firstElement = this->data[0];
		this->data.pop_front();
		return firstElement;
	}

	size_t getSize() {
		return this->data.getSize();
	}

	bool isEmpty() {
		return this->data.getSize() == 0 ? true : false;
	}

	friend std::ostream& operator<<(std::ostream& os, const myQueue& obj) {
		os << obj.data;
		return os;
	}

	~myQueue() {

	}
};
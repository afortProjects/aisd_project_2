#pragma once
#include "my_string.h"
#include "consts.h"

template<typename T, typename K> struct Pair {
	T firstValue;
	K secondValue;

	Pair() {
		this->firstValue = 0;
		this->secondValue = 0;
	}

	Pair(T _firstValue, K _secondValue) {
		this->firstValue = _firstValue;
		this->secondValue = _secondValue;
	}

	bool operator!=(const Pair& obj) {
		if (this->firstValue == obj.firstValue && this->secondValue == obj.secondValue) {
			return true;
		}
		else {
			return false;
		}
	}

	void operator=(const Pair& obj) {
		this->firstValue = obj.firstValue;
		this->secondValue = obj.secondValue;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pair& obj) {
		os << obj.firstValue << " " << obj.secondValue;
		return os;
	}
};

struct City {
	Pair<int, int> index;
	int cost = 0;

	City() {

	}

	City(int i, int j) : index(Pair<int, int>{i, j}) {
	}

	City(int i, int j, int cost) : index(Pair<int, int>{i, j}), cost(cost) {
	}


	friend std::ostream& operator<<(std::ostream& os, const City& obj) {
		os << obj.index << " " << obj.cost;
		return os;
	}
};
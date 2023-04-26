#pragma once
#include "my_string.h"
struct Index {
	int i;
	int j;

	Index() {
		i = 0;
		j = 0;
	}

	Index(int newI, int newJ) {
		i = newI;
		j = newJ;
	}
};

struct City {
	Index index;
	myString name = "";

	City() {

	}

	City(int i, int j, myString newName) {
		index = Index(i, j);
		name = newName;
	}

	friend std::ostream& operator<<(std::ostream& os, const City& obj) {
		os << obj.name << " " << obj.index.i<< " " << obj.index.j;
		return os;
	}
};

struct CityNode {
	CityNode* prev;
	CityNode* next;
	City city;
	int cost;
};

template<typename T> struct Pair {
	T firstValue;
	T secondValue;

	Pair() {
		this->firstValue = 0;
		this->secondValue = 0;
	}

	Pair(T _firstValue, T _secondValue) {
		this->firstValue = _firstValue;
		this->secondValue = _secondValue;
	}
};
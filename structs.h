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

	bool operator!=(const Pair& obj) {
		if (this->firstValue == obj.firstValue && this->secondValue == obj.secondValue) {
			return true;
		}
		else {
			return false;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Pair& obj) {
		os << obj.firstValue << " " << obj.secondValue;
		return os;
	}
};

struct Flight {
	myString source = "";
	myString destination = "";
	int cost;

	Flight() {
		this->cost = 0;
	}

	Flight(myString _source, myString _destination, int _cost) {
		this->source = _source;
		this->destination = _destination;
		this->cost = _cost;
	}

	friend std::ostream& operator<<(std::ostream& os, const Flight& obj) {
		os << obj.source << " " << obj.destination << " " << obj.cost;
		return os;
	}
};

struct Node {
	int x, y, distance;

	Node() {
		this->x = 0;
		this->y = 0;
		this->distance = 0;
	}

	Node(int _x, int _y, int _distance) {
		this->x = _x;
		this->y = _y;
		this->distance = _distance;
	}
};
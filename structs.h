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

	City(int i, int j) : index(Pair<int, int>(i, j)) {
	}


	City(int i, int j, int cost) : index(Pair<int, int>(i, j)), cost(cost) {
	}


	friend std::ostream& operator<<(std::ostream& os, const City& obj) {
		os << obj.index << " " << obj.cost;
		return os;
	}
};

struct Flight {
	char* source;
	char* destination;
	int cost;

	Flight() {
		this->cost = 0;
	}

	Flight(char* _source, char* _destination, int& _cost) : source(_source), destination(_destination), cost(_cost) {
		//size_t length = strlen(_source) + 1;
		//char* source_dest = new char[length];
		//strcpy_s(source_dest, length, _source);
		//this->source = source_dest;

		//size_t length_d = strlen(_destination) + 1;
		//char* destination_dest = new char[length_d];
		//strcpy_s(destination_dest, length_d, _destination);
		//this->destination = destination_dest;
	}

	friend std::ostream& operator<<(std::ostream& os, const Flight& obj) {
		os << obj.source << " " << obj.destination << " " << obj.cost;
		return os;
	}
};

struct Query {
	myString source = "";
	myString destination = "";
	int choice;

	Query() {
		this->choice = 0;
	}

	Query(myString& _source, myString& _destination, int& _choice) : source(_source), destination(_destination), choice(_choice) {
	}

	friend std::ostream& operator<<(std::ostream& os, const Query& obj) {
		os << obj.source << " " << obj.destination << " " << obj.choice;
		return os;
	}
};

//struct CityNode {
//	CityNode* prev;
//	CityNode* next;
//	City city;
//	int cost;
//
//	CityNode() {
//		prev = nullptr;
//		next = nullptr;
//		cost = 0;
//	}
//
//	CityNode(City city, CityNode* next, int cost) : city(city), next(next), cost(cost) {}
//};
//
//struct Node {
//	int x, y, distance;
//
//	Node() {
//		this->x = 0;
//		this->y = 0;
//		this->distance = 0;
//	}
//
//	Node(int _x, int _y, int _distance) : x(_x), y(_y), distance(_distance) {
//	}
//};
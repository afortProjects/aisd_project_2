#pragma once
#include "my_string.h"
#include "consts.h"
struct Index {
	int i;
	int j;

	Index() {
		i = 0;
		j = 0;
	}

	Index(int& newI, int& newJ) : i(newI), j(newJ) {
	}
};

struct City {
	size_t indexInCityVector=0;
	Index index;
	const char* name;
	City* next = nullptr;
	City* prev = nullptr;
	int cost = 0;

	City() {

	}

	City(int i, int j, const char*& newName, size_t newIndexInCityVector) : index(Index(i,j)), name(newName), indexInCityVector(newIndexInCityVector) {
		//size_t length = strlen(newName) + 1;
		//size_t size = STRING_BUFFER;

		//char* destination = new char[length];
		//strcpy_s(destination, length, newName);
		//this->name = destination;
	}

	friend std::ostream& operator<<(std::ostream& os, const City& obj) {
		os << obj.name << " " << obj.index.i<< " " << obj.index.j << " " << obj.indexInCityVector << " ";
		return os;
	}
};

struct CityNode {
	CityNode* prev;
	CityNode* next;
	City city;
	int cost;

	CityNode() {
		prev = nullptr;
		next = nullptr;
		cost = 0;
	}

	CityNode(City city, CityNode* next, int cost) : city(city), next(next), cost(cost) {}
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


struct Node {
	int x, y, distance;

	Node() {
		this->x = 0;
		this->y = 0;
		this->distance = 0;
	}

	Node(int _x, int _y, int _distance) : x(_x), y(_y), distance(_distance) {
	}
};
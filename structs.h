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

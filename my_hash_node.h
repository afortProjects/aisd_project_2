#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include "structs.h"
template <typename Key, typename Value>
class myHashNode {
private:
	Key key;
	Value value;
	myHashNode* next;
public:

	myHashNode(const Key& _key, const Value& _value) : key(_key), value(_value), next(NULL) {};

	//Getters
	Key getKey() {
		return this->key;
	}

	Value getValue() {
		return this->value;
	}

	myHashNode* getNext() const {
		return this->next;
	}

	//Setters

	void setValue(const Value& _value) {
		this->value = _value;
	}

	void setNext(myHashNode* _next) {
		this->next = _next;
	}

	friend std::ostream& operator<<(std::ostream& os, const myHashNode& obj) {
		std::cout << obj.getKey() << " " << obj.getValue();
	}
};
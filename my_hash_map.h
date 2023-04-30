#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "my_hash_node.h"
#include <iostream>
#include <cstring>
#define TABLE_SIZE 10000

template <typename Key, typename Value>
class myHashMap {
public:
	myHashNode<Key, Value>** table;
public:
	myHashMap() {
		this->table = new myHashNode<Key, Value>*[TABLE_SIZE]();
	}
	//myHashMap(const myHashMap& other) {
	//	this->table = new myHashNode<Key, Value>*[TABLE_SIZE]();
	//	for (size_t i = 0; i < TABLE_SIZE; ++i) {
	//			myHashNode<Key, Value>* current = other.table[i];
	//			while (current != NULL) {
	//				this->add(current->getKey(), current->getValue());
	//				current = current->getNext();
	//			}
	//	}
	//}
	//myHashMap<Key, Value>& operator=(const myHashMap<Key, Value>& other) {
	//	if (this == &other) {
	//		return *this; // self-assignment check
	//	}

	//	// clear the existing data
	//	// copy the new data from other
	//	table = new myHashNode<Key, Value>*[TABLE_SIZE](); // allocate memory for the new table

	//	for (size_t i = 0; i < TABLE_SIZE; ++i) {
	//		myHashNode<Key, Value>* entry = other.table[i];
	//		if (entry != nullptr) {
	//			table[i] = new myHashNode<Key, Value>(entry->getKey(), entry->getValue());
	//			myHashNode<Key, Value>* curr = entry->getNext();
	//			while (curr != nullptr) {
	//				table[i]->setNext(new myHashNode<Key, Value>(curr->getKey(), curr->getValue()));
	//				curr = curr->getNext();
	//			}
	//		}
	//	}

	//	return *this;
	//}
	~myHashMap() {
		for (int i = 0; i < TABLE_SIZE; ++i) {
			myHashNode<Key, Value>* currentEntry = table[i];
			while (currentEntry != NULL) {
				myHashNode<Key, Value>* prev = currentEntry;
				currentEntry = currentEntry->getNext();
				delete prev;
			}
			this->table[i] = NULL;
		}
		if(table != NULL)
			delete[] this->table;
	}

	size_t hash_string(const char* str) {
		size_t precision = 2;
		return((*(size_t*)str) >> precision) % TABLE_SIZE;
	}

	void add(const Key& newKey, const Value& newValue) {
		size_t hashValue = hash_string(newKey);
		myHashNode<Key, Value>* prev = NULL;
		myHashNode<Key, Value>* entry = table[hashValue];

		while (entry != NULL && entry->getKey() != newKey) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new myHashNode<Key, Value>(newKey, newValue);
			if (prev == NULL) {
				table[hashValue] = entry;
			}
			else {
				prev->setNext(entry);
			}
		}
		else {
			entry->setValue(newValue);
		}
	}

	void remove(const Key& keyToRemove) {
		size_t hashValue = hash_string(keyToRemove);
		myHashNode<Key, Value>* prev = NULL;
		myHashNode<Key, Value>* entry = table[hashValue];

		while (entry != NULL && entry->getKey() != keyToRemove) {
			prev = entry;
			entry = entry->getNext();
		}
		
		//When key wasn't found
		if (entry == NULL) {
			return;
		}
		else {
			if (prev == NULL) {
				table[hashValue] = entry->getNext();
			}
			else {
				prev->setNext(entry->getNext());
			}
			delete entry;
		}
	}


 //   myHashNode<Key, Value>& operator[](int index) {
	//	return this->table[index];
	//}

	City operator[](const char* _key) {
		size_t hashValue = hash_string(_key);
		myHashNode<Key, Value>* entry = table[hashValue];

		while (entry != NULL) {
			const char* currentKey = entry->getKey();
			if (strcmp(currentKey, _key) == 0) {
				return entry->getValue();
			}
			entry = entry->getNext();
		}
		return City();
	}


	friend std::ostream& operator<<(std::ostream& os, const myHashMap& obj) {
		for (size_t i = 0; i < TABLE_SIZE; i++) {
				std::cout << obj.table[i] << std::endl;
		}
		return os;
	}
};
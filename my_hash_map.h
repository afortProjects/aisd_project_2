#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "consts.h"
#include "my_hash_node.h"
#include "my_double_linked_list.h"
#include <iostream>
#include <cstring>

template <typename Key, typename Value>
class myHashMap {
public:
	myHashNode<Key, Value>** table;
public:
	myHashMap() {
		this->table = new myHashNode<Key, Value>*[TABLE_SIZE]();
	}

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

	unsigned int hash_string(const char* str) {
		char* dest = new char[strlen(str) + 1];
		strcpy(dest, str);
		dest[strlen(str)] = '\0';

		unsigned int hash = HASH_STRING_VALUE;

		while (*dest) {
			hash = ((hash << HASH_STRING_PRECISION) + hash) + (*dest++);
		}
		return hash % TABLE_SIZE;
	}

	unsigned int hash_int(const int number) {
		unsigned int hash = HASH_INT_START_VALUE;
		for (unsigned int i = 0; i < sizeof(int); ++i) {
			hash ^= (unsigned int)(number >> (i * HASH_INT_PRECISION)) & SECOND_HASH_INT_VALUE;
			hash *= HASH_INT_VALUE;
		}
		return hash % TABLE_SIZE;
	}

	void add(const Pair<int, int>& newKey, const char*& newValue) {
		size_t hashValue = hash_int(newKey.firstValue) % TABLE_SIZE;
		myHashNode< Pair<int, int>, const char*>* prev = NULL;
		myHashNode<Pair<int, int>, const char*>* entry = table[hashValue];

		while (entry != NULL && (entry->getKey().firstValue != newKey.firstValue || entry->getKey().secondValue != newKey.secondValue)) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new myHashNode<Pair<int, int>, const char*>(newKey, newValue);
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

	void add(const char*& newKey, const Pair<int, DoubleLinkedList<City>*>& newValue) {
		size_t hashValue = hash_string(newKey);
		myHashNode<const char*, Pair<int, DoubleLinkedList<City>*>>* prev = NULL;
		myHashNode<const char*, Pair<int, DoubleLinkedList<City>*>>* entry = table[hashValue];

		while (entry != NULL && entry->getKey() != newKey) {
			prev = entry;
			entry = entry->getNext();
		}

		if (entry == NULL) {
			entry = new myHashNode<const char*, Pair<int, DoubleLinkedList<City>*>>(newKey, newValue);
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

	Pair<int, DoubleLinkedList<City>*>& operator[](const char* _key) {
		size_t hashValue = hash_string(_key);
		myHashNode<Key, Value>* entry = table[hashValue];

		while (entry != NULL) {
			const char* currentKey = entry->getKey();
			if (strcmp(currentKey, _key) == 0) {
				return entry->getValue();
			}
			entry = entry->getNext();
		}
		Pair<int, DoubleLinkedList<City>*> p{};
		return p;
	}

	const char* operator[](Pair<int, int>& _key) {
		size_t hashValue = hash_int(_key.firstValue) % TABLE_SIZE;

		myHashNode<Key, Value>* entry = table[hashValue];

		while (entry != NULL) {
			Pair<int, int> currentKey = entry->getKey();
			if (currentKey.firstValue == _key.firstValue && currentKey.secondValue == _key.secondValue) {
				return entry->getValue();
			}
			entry = entry->getNext();
		}
		return nullptr;
	}

	friend std::ostream& operator<<(std::ostream& os, const myHashMap& obj) {
		for (size_t i = 0; i < TABLE_SIZE; i++) {
				std::cout << obj.table[i] << std::endl;
		}
		return os;
	}
};
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "consts.h"
#include "string.h"
#include <cstdlib>
#include <cstring>

#include <iostream>

class myString {
private:
    char* buffer;
    size_t size;
    size_t capacity;
public:
    myString();
    myString(const char* str);
    myString(const myString& other);
    ~myString();

    myString& operator=(const myString& other);

    myString& operator=(const char* str);

    myString& operator+=(const myString& other);

    myString& operator+=(const char& character);
    
    myString& operator+=(const int& number);

    myString& operator+=(const char* str);

    bool operator!=(myString& stringObjectToCompare);

    bool operator==(const char* arr);

    bool operator==(myString& str);

    size_t length() const;

    const char* str() const;
    const char operator[](const int index);

    friend std::ostream& operator<<(std::ostream& cout, const myString& obj);

    void removeSpacesFromBeginningAndEndFromString();
    void reverse();

    bool checkIfListIsNotEmpty();

    int const amountOfComasInString();
};
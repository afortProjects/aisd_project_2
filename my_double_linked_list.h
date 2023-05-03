#pragma once
#include <iostream>
template<typename T>
class Node {
public:
    T value;
    Node<T>* prev;
    Node<T>* next;

    Node(T val) {
        value = val;
        prev = nullptr;
        next = nullptr;
    }
};

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoubleLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addFirst(T val) {
        Node<T>* node = new Node<T>(val);
        if (head == nullptr) {
            head = node;
            tail = node;
        }
        else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }

    void addLast(T val) {
        Node<T>* node = new Node<T>(val);
        if (tail == nullptr) {
            head = node;
            tail = node;
        }
        else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void removeFirst() {
        if (head == nullptr) {
            return;
        }
        else if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        size--;
    }

    void removeLast() {
        if (tail == nullptr) {
            return;
        }
        else if (head == tail) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else {
            Node<T>* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        size--;
    }

    void remove(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        else if (node == head) {
            removeFirst();
        }
        else if (node == tail) {
            removeLast();
        }
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            size--;
        }
    }

    Node<T>*& getHead() {
        return head;
    }

    Node<T>*& getTail() {
        return tail;
    }

    int getSize() {
        return size;
    }

    friend std::ostream& operator<<(std::ostream& os, const DoubleLinkedList<T>* list) {
        Node<T>* current = list->head;
        while (current != nullptr) {
            os << current->value << " ";
            current = current->next;
        }
        return os;
    }
};
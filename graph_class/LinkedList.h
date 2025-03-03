#pragma once

#include <iostream>
#include <vector>
#include <stdexcept> // ��� ����������
#include "AbsIterator.h"
#include <fstream>
// ����� ���� ������
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    // ����������� � ����������
    Node(const T& data1) {
        this->data = data1;
        next = nullptr;
    }
};

// ����� ������������ ������
template <typename T>
class LinkedList {
private:
    // ��������� �� ������ ������
    Node<T>* head;

public:
    // ����������� ��� ����������
    LinkedList() {
        head = nullptr;
    }

    // ����������
    // ��������� ��� ���� � ������
    ~LinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void ClearList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ���������� ���� � ����� ������
    void addNode(const T& data);
    // �������� ���� �� ��������
    void removeNode(const T& data);
    // ����� ���� �� ��������
    // true ���� ���� ������, ����� false
    bool searchNode(T& data) const;
    // ����� ������� ����, ���� �� ������, �� -1
    int searchNodeInd(const T& data) const;
    // �������� ���� �� �������
    T& dataByInd(int ind) const;
    // ����� ������ � �������
    void printList() const;
    // ����� ������ � ����
    void printListToFile(const std::string& filename) const;
    // ��������� ����� � ������
    int ListSize() const;
    std::vector<T> ListToVec() const;


    // ����� ��������� ��� Linked List
    template<typename T>
    class LinkedListIterator : public AbsIterator<T> {
    private:
        Node<T>* current;  // ������� ����

    public:
        // ����������� � ����������
        LinkedListIterator(Node<T>* x) {
            current = x;
        }

        // �������� ���������
        bool operator==(const AbsIterator<T>& o) const override {
            return current == dynamic_cast<const LinkedListIterator<T>&>(o).current;
        }

        bool operator!=(const AbsIterator<T>& o) const override {
            return !(current == dynamic_cast<const LinkedListIterator<T>&>(o).current);
        }

        // �������� ������� � ������
        T& operator*() const override {
            //���������� ������ �������� ����
            return current->data;
        }

        // �������� �������� �� ��������� ����
        LinkedListIterator& operator++() override {
            //���� ������� �� ����� nullptr
            if (current != nullptr) {
                //��������� � ���������� ����
                current = current->next;
            }
            //���������� ������ �� ������� ������
            return *this;
        }


    };


    LinkedListIterator<T> begin() const {
        return LinkedListIterator<T>(head);
    }

    LinkedListIterator<T> end() const {
        return LinkedListIterator<T>(nullptr);
    }

};


// ���������� ���� � ������
template<typename T>
void LinkedList<T>::addNode(const T& data) {
    Node<T>* newNode = new Node<T>(data);

    // ���� ������ ������, �� ������ ������ �������
    if (head == nullptr) {
        head = newNode;
    }
    // ������� ��������� ���� ������ � ��������� ����� ���� ����� ����
    else {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// �������� ���� �� ��������
template<typename T>
void LinkedList<T>::removeNode(const T& data) {
    // ���� ������ �� ������
    if (head != nullptr) {

        // ���� ����� ������� ���� �� ������
        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;

        }
        // ���� ��������� ���� �� � ������
        // ���� ���� �� ��������
        else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                // ���� ������ ���� ������
                // ������� ��� � ������ ���������
                if (current->next->data == data) {
                    Node<T>* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    return;
                }
                current = current->next;
            }
        }
    }
}

// ����� ����
// true, ���� ���� ����
// ����� false
template<typename T>
bool LinkedList<T>::searchNode(T& data) const {
    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// ����� ������� ����
// -1, ���� ��� ����
template<typename T>
int LinkedList<T>::searchNodeInd(const T& data) const {
    Node<T>* current = head;
    int ind = 0;
    while (current != nullptr) {
        if (current->data == data) {
            return ind;
        }
        current = current->next;
        ind++;
    }
    return -1;
}

// �������� ���� �� �������
template<typename T>
T& LinkedList<T>::dataByInd(int ind) const {
    if (ind < 0) {
        throw std::invalid_argument("������������ �������� �������");
    }
    else {
        int i = 0;
        //T res;

        Node<T>* current = head;

        while (i < ind) {
            if (current == nullptr || current->next == nullptr) {
                throw std::invalid_argument("������������ �������� �������");
            }
            else {
                current = current->next;
                i++;
            }
        }

        return current->data;

    }
}

// ����� ������ � �������
template<typename T>
void LinkedList<T>::printList() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// ����� ������ � ����
template<typename T>
void LinkedList<T>::printListToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    if (!fout.is_open()) // ���� ���� �� ��� ������
    {
        throw std::invalid_argument("���� �� ����� ���� ������");
    }

    Node<T>* current = head;
    while (current != nullptr) {
        fout << current->data << std::endl;
        current = current->next;
    }

    fout.close();
}

//����� ���������� ����� � ������
template<typename T>
int LinkedList<T>::ListSize() const {
    int res = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        res++;
        //std::cout << current->data << " ";
        current = current->next;
    }
    return res;
}


//�������������� ������ � ������
template<typename T>
std::vector<T> LinkedList<T>::ListToVec() const {
    std::vector<T> t;
    Node<T>* current = this->head;
    while (current != nullptr) {
        t.push_back(current->data);

        current = current->next;
    }
    return t;

}

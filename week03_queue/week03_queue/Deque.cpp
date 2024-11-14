#include <iostream>
using namespace std;

template <typename T>
class Deque {
	T* arr;
	int capacity;
	int size;
	int front;     
	int back;      
	
	void resize() {
		int newCapacity = capacity * 2;   
		T* newArr = new T[newCapacity];

		int j = 0;
		for (int i = front; j < size; i = (i + 1) % capacity) {
			newArr[j++] = arr[i];
		}

		delete[] arr;  
		arr = newArr;
		capacity = newCapacity;
		front = 0;
		back = size - 1;
	}
	void copy(const Deque& other) {
		capacity = other.capacity;
		size = other.size;
		front = other.front;
		back = other.back;
		arr = new T[capacity];
		for (int i = 0; i < capacity; i++) {
			arr[i] = other.arr[i];
		}
	}
public:
	Deque(int capacity = 10) :
		arr(new T[capacity]), capacity(capacity), front(-1), back(0), size(0){}
	
	Deque(const Deque& other) {
		copy(other);
	}
		
	Deque& operator=(const Deque & other) {
			if (this != &other) {
				delete[] arr;
				copy(other);
			}
			return *this;
	}

	~Deque() {
		delete[] arr;
	}
	bool isFull() const{
		return size == capacity;
	}
	bool isEmpty() const{
		return size == 0;
	}
	void pushFront(const T& data) {
		if (isFull()) {
			resize();
		}
		if (front == -1) {
			front = 0;
			back = 0;
		}
		else if (front == 0) {
			front = capacity - 1;
		}
		else {
			front--;
		}
		arr[front] = data;
		size++;
	}
	void pushBack(const T& data) {
		if (isFull()) {
			resize();
		}

		if (front == -1) { 
			front = 0;
			back = 0;
		}
		else if (back == capacity - 1) {
			back = 0;
		}
		else {
			back++;
		}

		arr[back] = data;
		size++;
	}
	void popFront() {
		if (isEmpty()) {
			cout << "Deque is empty\n";
			return;
		}
		if (front == back) {
			front = -1;
			back = -1;
		}
		else if (front == capacity - 1) {
			front = 0;
		}
		else {
			front++;
		}
		size--;
	}

	void popBack() {
		if (isEmpty()) {
			cout << "Deque is empty\n";
			return;
		}
		if (front == back) {
			front = -1;
			back = -1;
		}
		else if (back == 0) {
			back = capacity - 1;
		}
		else {
			back--;
		}
		size--;
	}

	T getFront() const {
		if (isEmpty()) {
			throw invalid_argument("Deque is empty, cannot pop from front.");
		}
		return arr[front];
	}

	T getBack() const {
		if (isEmpty()) {
			throw invalid_argument("Deque is empty, cannot pop from back.");
		}
		return arr[back];
	}
	int getSize() const {
		return size;
	}
};


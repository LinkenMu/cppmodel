#pragma once
#include <deque>
#include <cstdio>
#include <math.h>
#include <iostream>

#define LEFT_CHILD(A,p) A[2*p]
#define RIGHT_CHILD(A,p) A[2*p+1]

template <class T>
class MinStack{
public:
	MinStack() {
		size_ = 0;
	};
	MinStack(T v[], int size) {
		for (int i = 0; i < size; i++) {
			AddNode(v[i]);
		}
	};

	MinStack(T& s) {
		array_ = s.array_;
		size_ = s.size_;
	};

	MinStack& operator =(const MinStack& other) {
		if (!array_.empty()) {
			for (auto iter : array_) {
				T& tmp = iter;
				delete &tmp;
			}
			array_.clear();
		}

		array_ = other.array_;
		size_ = other.size_;
		return *this;
	};

	~MinStack() {
		if (!array_.empty()) {
			for (auto iter : array_) {
				T& tmp = iter;
				delete &tmp;
			}
			array_.clear();
			size_ = 0;
		}	
	};

	void AddNode(T n) {
		array_.push_back(n);
		size_ += 1;
		NewOneUpdate(size_ - 1);

	};

	//void AddNode(T& n) {
	//	array_.push_back(n);
	//	size_ += 1;
	//	NewOneUpdate(size_-1);
	//	
	//};

	T PopTopNode() {
		T tmp = array_.pop_front();
		ReSort(0);
	};

	T& PeerTopNode() {
		return &(array_.front());
	};

	void PrintStack() {
		for(int count = 0; count < size_; count++){
			printf(" %d ", array_[count]);
		}
		printf("\n");
	};

private:
	std::deque<T> array_;
	unsigned int size_;

	inline void SWAP(int a, int b) {
		T tmp = array_[a];
		array_[a] = array_[b];
		array_[b] = tmp;
	};

	void ReSort(int postion) {
		
		if ((postion + 1) * 2 > size_)
			return;

		PrintStack();
		int pos = postion + 1;
		int large = 1;
		if (array_[postion] < array_[2* pos-1]) {  // left child compare
			large = 2 * pos - 1;
		}
		
		if (array_[postion] < array_[2 * pos - 1]) {//right child compare
			large = 2 * pos -1;
		}

		if (large != postion) {
			SWAP(postion, large);
			ReSort(large);
		}
	};

	void NewOneUpdate(int postion) {
		int t_pos = postion+1;
		if (t_pos < 2)
			return;
		while(array_[t_pos - 1] < array_[(t_pos / 2)-1]) {
			SWAP(t_pos-1, (t_pos / 2)-1);
			t_pos = t_pos / 2;
			if (t_pos < 2)
				break;
		}

	}


};
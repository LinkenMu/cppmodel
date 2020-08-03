#pragma once
#include <mutex>
template <class T>
class Singleton {
public:
	static T* GetInctance() {
		if (ptr_ == nullptr)
		{
			lock_guard<std::mutex> lock(mutex_);
			if (ptr_ == nullptr) {
				ptr_ = new T;
			}
		}
		return ptr_;
	};

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	Singleton();
	static std::mutex mutex_;
	static T* ptr_;

}; 

template <class T> 
T* Singleton<T>::ptr_;

template <class T>
std::mutex Singleton<T>::mutex_;
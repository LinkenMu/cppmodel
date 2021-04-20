/*
 * ringbuf.h
 *
 *  Created on: Dec 24, 2019
 *      Author: mxw
 *  一个obj循环缓冲池，内存从malloc获取
 */

#ifndef SOURCE_RINGBUF_H_
#define SOURCE_RINGBUF_H_
#include <algorithm>
#include <atomic>
#include <memory>

template <class T>
class RingBuf {
public:
	RingBuf(unsigned int size);
	virtual ~RingBuf();
	int Put(T* data, unsigned int len);
	int Get(T* data, unsigned int len);
	int Peek(T* data, unsigned int length);
	int ValidSize(){return in_ - out_;};
	void Reset(){in_ = 0;out_ = 0;};
private:
	T* addr_;
	unsigned int size_;
	std::atomic<int> in_;//单个生产者，单个消费者，不需要加锁
	std::atomic<int> out_;
};

template <class T>
RingBuf<T>::RingBuf(unsigned int size){
	int capasity = 0;
	if(sizeof(T)*size%4096){
		capasity = (sizeof(T)*size%4096 +1)*4096;
	}
	else{
		capasity = sizeof(T)*size;
	}

	addr_ = (T*)malloc(capasity);
	in_ = 0;
	out_ = 0;
	size_ = capasity/sizeof(T);
};

template <class T>
RingBuf<T>::~RingBuf(){
	if(addr_)
		free(addr_);
};

template <class T>
int RingBuf<T>::Put(T* data, unsigned int length)
{
	// 当前缓冲区空闲空间
	unsigned int len = std::min(length, size_ - in_ + out_);

	// 当前in位置到buffer末尾的长度
	auto l = std::min(len, size_ - (in_ % size_));

	// 首先复制数据到[in，buffer的末尾]
	memcpy(addr_ + (in_ % size_), data, l*sizeof(T));

	// 复制剩余的数据（如果有）到[buffer的起始位置,...]
	memcpy(addr_, data + l, (len - l)*sizeof(T));

	in_ += len; // 直接加，不作模运算。当溢出时，从buffer的开始位置重新开始

	return len;
};

template <class T>
int RingBuf<T>::Get(T* data, unsigned int length)
{
	// 缓冲区中的数据长度
	unsigned int t = in_ - out_;
	unsigned int len = std::min(length, t);

	// 首先从[out,buffer end]读取数据
	auto l = std::min(len, size_ - (out_ % size_));
	memcpy(data, addr_ + (out_ % size_), l*sizeof(T));

	// 从[buffer start,...]读取数据
	memcpy(data + l, addr_, (len - l)*sizeof(T));

	out_ += len; // 直接加，不错模运算。溢出后，从buffer的起始位置重新开始

	return len;
};

template <class T>
int RingBuf<T>::Peek(T* data, unsigned int length)
{
	// 缓冲区中的数据长度
	unsigned int t = in_ - out_;
	unsigned int len = std::min(length, t);

	// 首先从[out,buffer end]读取数据
	auto l = std::min(len, size_ - (out_ % size_));
	memcpy(data, addr_ + (out_ % size_), l*sizeof(T));

	// 从[buffer start,...]读取数据
	memcpy(data + l, addr_, (len - l)*sizeof(T));

	return len;
};

#endif /* SOURCE_RINGBUF_H_ */

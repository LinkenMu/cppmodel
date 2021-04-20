/*
 * ringbuf.cpp
 *
 *  Created on: Dec 24, 2019
 *      Author: mxw
 */

#include "ringbuf.h"
RingBuf::RingBuf(char *start_addr, int raw_frame_size, unsigned long total_buf_size, int dma_head_size,int alignmet) {
	// suport one productor thread one consumer thread

	if((long long)start_addr % alignmet)
	{
		printf("ADDR not alignment with %d", alignmet);
	}
//做字节对其
	data_ = start_addr;
	dma_head_size_ = dma_head_size;
	if((raw_frame_size + dma_head_size_) % alignmet == 0)
	{
		single_buf_size_ = raw_frame_size + dma_head_size_;
	}
	else
	{
		single_buf_size_ = ((raw_frame_size + dma_head_size_)/alignmet +1)*alignmet;
	}

	capacity_ = total_buf_size/single_buf_size_;
	size_ = 0;
	product_index_ = 0;
	consume_index_ = 0;

}

RingBuf::~RingBuf() {
	// TODO Auto-generated destructor stub
}


int RingBuf::ProductorInc()
{
	if(size_ == capacity_)
	{
		return IS_FULL;
	}

	if(product_index_ + 1 < capacity_)
	{
		product_index_++;
	}
	else//线性地址到底了,需要回头模拟环形缓冲区
	{
		product_index_ = 0;
	}

	size_++;
	return OK;
}
int RingBuf::ConsumerInc()
{
	if(size_ == 0)
	{
		return IS_EMPUTY;
	}

	if(consume_index_ + 1 < capacity_)
	{
		consume_index_++;
	}
	else//线性地址到底了,需要回头模拟环形缓冲区
	{
		consume_index_=0;
	}
	size_--;
	return OK;
}

char* RingBuf::GetProductorAddr()
{
	return product_index_*single_buf_size_ + data_ + dma_head_size_;
}
char* RingBuf::GetConsumerAddr()
{
	return consume_index_*single_buf_size_ + data_ + dma_head_size_;
}

int RingBuf::GetRingBufSize()// return used counts
{
	return size_;
}
int RingBuf::GetRingBufCapasity()//return total counts
{
	return capacity_;
}

void RingBuf::Resize(int size)//把不能除与的内存舍弃掉
{
	printf("ringbuffers Resize from %d to %d",capacity_, size);
	capacity_ = size;
}
void RingBuf::ResetRingBuf()
{
	product_index_ = 0;
	consume_index_ = 0;
	size_ = 0;
}

}

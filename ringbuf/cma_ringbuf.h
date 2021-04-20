/*
 * ringbuf.h
 *
 *  Created on: Dec 24, 2018
 *      Author: mxw
 */

#ifndef SOURCE_RINGBUF_H_
#define SOURCE_RINGBUF_H_
namespace mode {
class RingBuf {// not suport multi-thread
public:
	enum{
		DMA_ALIGNMENT = 8,
		DMA_HEAD_SIZE =64,
		IS_FULL = 1,
		IS_EMPUTY = 2,
	};
	RingBuf(char *start_addr, int raw_frame_size, unsigned long total_buf_size, int dma_hand_size = RingBuf::DMA_HEAD_SIZE, int alignmet = RingBuf::DMA_ALIGNMENT);
	virtual ~RingBuf();
	int  ProductorInc();
	int ConsumerInc();
	char* GetProductorAddr();
	char* GetConsumerAddr();
	int GetRingBufSize();// return used counts
	int GetRingBufCapasity();//return total counts
	void ResetRingBuf();
	int GetOneBufSize(){return single_buf_size_;};
	void Resize(int size);
private:
	int product_index_, consume_index_, single_buf_size_, size_, capacity_, dma_head_size_;
	char *data_;
};
}
#endif /* SOURCE_RINGBUF_H_ */

#include "../inc/ringbuffer.h"



u8 initial_buffer(ringbuffer *ptr,u8 self_mem,u32 size)
{
	if (self_mem == NO)															//�ж��Ƿ����ṩ�õĿռ�
	{
		ptr->malloc_flag = NO;															//��¼�ǲ������з���Ŀռ�
	}
	else
	{
		ptr->start_ringbuffer_ptr = basic_malloc(size);									//�ڴ������ɹ������							
		if (ptr->start_ringbuffer_ptr == 0)
			return FAIL;
		ptr->malloc_flag = YES;															//��¼�����з���Ŀռ�
	}
	ptr->return_data_buffer = basic_malloc(size);										//�������ڷ��ض�ȡ�Ŀռ�
	ptr->end_ringbuffer_ptr = ptr->start_ringbuffer_ptr + size;
	ptr->write_location_ptr = ptr->start_ringbuffer_ptr;										//��ʼ�����ָ��
	ptr->read_location_ptr = ptr->start_ringbuffer_ptr;
	ptr->ringbuffer_size = size;															//�������Ŀռ��С
	ptr->leading_flag = NO;
	return SUCCESS;
}



u8 deinitial_buffer(ringbuffer *ptr)
{
	if (ptr->malloc_flag == YES)															//�ж��Ƿ������з���Ŀռ�
		basic_free(ptr->start_ringbuffer_ptr);											//�ͷſռ�
	ptr->ringbuffer_size = 0;
	basic_free(ptr->return_data_buffer);
	ptr->start_ringbuffer_ptr = NULL_PTR;												//��ֹҰָ��
	ptr->end_ringbuffer_ptr = NULL_PTR;
	ptr->write_location_ptr = NULL_PTR;
	ptr->read_location_ptr = NULL_PTR;
	ptr->return_data_buffer = NULL_PTR;
	return SUCCESS;
}




void write_buffer_len(ringbuffer *ptr,u32 datalen)
{
	u32 write_len;																	//д���ݴ�С											
	if (ptr->write_location_ptr + datalen < ptr->end_ringbuffer_ptr)							//��д���������� write �� end ֮��ʱ
	{
		ptr->write_location_ptr += datalen % ptr->ringbuffer_size;
		if (ptr->leading_flag == YES)
			ptr->read_location_ptr = ptr->write_location_ptr;
	}
	else if ((datalen - 1) / ptr->ringbuffer_size > 0)									//��д�����ݴ�������������ʱ
	{
		ptr->write_location_ptr = ptr->start_ringbuffer_ptr + (ptr->read_location_ptr - ptr->start_ringbuffer_ptr);
		ptr->leading_flag = YES;
	}
	else																			//��д���������ڻ�������С�� �� ����write �� end ֮��ʱ
	{
		write_len = datalen - (ptr->end_ringbuffer_ptr - ptr->write_location_ptr);
		ptr->write_location_ptr = ptr->start_ringbuffer_ptr;
		if (write_len + ptr->start_ringbuffer_ptr >= ptr->read_location_ptr)
		{
			ptr->leading_flag = YES;
			if (write_len == ptr->ringbuffer_size)
				ptr->read_location_ptr = ptr->start_ringbuffer_ptr;
			else
				ptr->read_location_ptr = ptr->write_location_ptr + write_len;
		}
		ptr->write_location_ptr += write_len;
		if (ptr->leading_flag == YES)
			ptr->read_location_ptr = ptr->write_location_ptr;
	}
}





void write_buffer_data(ringbuffer *ptr, u8* data, u32 datalen)
{
	u32 write_len;																	//д���ݴ�С
	u8* read_ptr;																	//������ָ��
	u32 _len;																		//��ʱ���ڱ����ϴζ����ݵĴ�С
	if (ptr->write_location_ptr + datalen < ptr->end_ringbuffer_ptr)							//��д���������� write �� end ֮��ʱ
	{
		write_len = datalen;
		read_ptr = data;
		while (write_len--)
			*(ptr->write_location_ptr++) = *(read_ptr++);
		if (ptr->write_location_ptr == ptr->end_ringbuffer_ptr)
			ptr->write_location_ptr = ptr->start_ringbuffer_ptr;
		if (ptr->leading_flag == YES)
			ptr->read_location_ptr = ptr->write_location_ptr;
	}
	else if ((datalen - 1) / ptr->ringbuffer_size > 0)									//��д�����ݴ�������������ʱ
	{
		write_len = ptr->end_ringbuffer_ptr - ptr->read_location_ptr;
		read_ptr = data + datalen - ptr->ringbuffer_size;
		ptr->write_location_ptr = ptr->read_location_ptr;
		while (write_len--)
			*(ptr->write_location_ptr++) = *(read_ptr++);
		ptr->write_location_ptr = ptr->start_ringbuffer_ptr;
		write_len = ptr->read_location_ptr - ptr->start_ringbuffer_ptr;
		while (write_len--)
			*(ptr->write_location_ptr++) = *(read_ptr++);
		ptr->leading_flag = YES;
	}
	else																			//��д���������ڻ�������С�� �� ����write �� end ֮��ʱ
	{
		write_len = ptr->end_ringbuffer_ptr - ptr->write_location_ptr;
		_len = write_len;
		read_ptr = data;
		while (write_len--)
			*(ptr->write_location_ptr++) = *(read_ptr++);
		ptr->write_location_ptr = ptr->start_ringbuffer_ptr;
		write_len = datalen - _len;



		if (write_len + ptr->start_ringbuffer_ptr >= ptr->read_location_ptr)
		{
			ptr->leading_flag = YES;
			if (write_len == ptr->ringbuffer_size)
				ptr->read_location_ptr = ptr->start_ringbuffer_ptr;
			else
				ptr->read_location_ptr = ptr->write_location_ptr + write_len;
		}
		while (write_len--)
			*(ptr->write_location_ptr++) = *(read_ptr++);
		if (ptr->leading_flag == YES)
			ptr->read_location_ptr = ptr->write_location_ptr;
	}

}



u8* get_unread_data(ringbuffer *ptr, u32 *len, u8 preview)										//��ȡ����δ������
{
	if (ptr->read_location_ptr < ptr->write_location_ptr)									//�ж�read�Ƿ�ǰwrite
	{
		basic_memcpy(ptr->return_data_buffer, ptr->read_location_ptr, ptr->write_location_ptr - ptr->read_location_ptr);
		*len = ptr->write_location_ptr - ptr->read_location_ptr;
	}
	else if (ptr->read_location_ptr == ptr->write_location_ptr && ptr->leading_flag == NO)		//û��δ������
	{
		*len = 0;
		return NULL_PTR;
	}
	else																		//�ֶδ��ڵ����ݣ�read  > write��
	{
		basic_memcpy(ptr->return_data_buffer, ptr->read_location_ptr, ptr->end_ringbuffer_ptr - ptr->read_location_ptr);
		basic_memcpy(ptr->return_data_buffer + (ptr->end_ringbuffer_ptr - ptr->read_location_ptr), ptr->start_ringbuffer_ptr, ptr->write_location_ptr - ptr->start_ringbuffer_ptr);
		*len = ptr->end_ringbuffer_ptr - ptr->read_location_ptr + ptr->write_location_ptr - ptr->start_ringbuffer_ptr;
	}
	if (preview == NO)															//�Ƿ���Ԥ��ģʽ��Ԥ��ģʽ�²��޸Ķ�ָ��
	{
		ptr->read_location_ptr = ptr->write_location_ptr;
		ptr->leading_flag = NO;
	}
	return ptr->return_data_buffer;
}


void get_unread_ptr(ringbuffer *ptr, u8** ptr_1,u8** ptr_2,u32* len_1,u32* len_2, u8 preview)	//��ȡδ���������ڵ�λ��
{
	if (ptr->read_location_ptr < ptr->write_location_ptr)									//�ж�read�Ƿ�ǰwrite
	{
		*ptr_1 = ptr->read_location_ptr;
		*len_1 = ptr->write_location_ptr - ptr->read_location_ptr;
		*ptr_2 = NULL_PTR;
		*len_2 = 0;
	}
	else if(ptr->read_location_ptr == ptr->write_location_ptr && ptr->leading_flag == NO)		//û��δ������
	{
		*ptr_1 = NULL_PTR;
		*len_1 = 0;
		*ptr_2 = NULL_PTR;
		*len_2 = 0;
	}
	else																		//�ֶδ��ڵ����ݣ�read  > write��
	{
		*ptr_1 = ptr->read_location_ptr;
		*len_1 = ptr->end_ringbuffer_ptr - ptr->read_location_ptr;
		*ptr_2 = ptr->start_ringbuffer_ptr;
		*len_2 = ptr->write_location_ptr - ptr->start_ringbuffer_ptr;
	}
	if (preview == NO)															//�Ƿ���Ԥ��ģʽ��Ԥ��ģʽ�²��޸Ķ�ָ��
	{
		ptr->read_location_ptr = ptr->write_location_ptr;
		ptr->leading_flag = NO;
	}
}



void update_readlocation(ringbuffer *ptr)
{
	ptr->read_location_ptr = ptr->write_location_ptr;
	ptr->leading_flag = NO;
}
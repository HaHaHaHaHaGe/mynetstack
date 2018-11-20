#include "ringbuffer.h"

#define WR_SEL (read_location_ptr < write_location_ptr)
#define SUR_SIZE ((WR_SEL)?(write_location_ptr - read_location_ptr)\
						:(end_ringbuffer_ptr - read_location_ptr + write_location_ptr - start_ringbuffer_ptr))

u8* start_ringbuffer_ptr;															//��������ʼλ��
u8* end_ringbuffer_ptr;																//��������ֹλ��
u8* write_location_ptr;																//д����λ��
u8* read_location_ptr;																//������λ��

u8* return_data_buffer;																//���ڷ��ص�������

u32 ringbuffer_size;																//��������С
u8 malloc_flag;																		//�Ļ������Ƿ������д�����

u8 leading_flag;																	//��ǰд�����Ƿ����ȶ�����һ������

u8 initial_buffer(u8* ptr,u32 size)
{
	if (ptr != NULL_PTR)															//�ж��Ƿ����ṩ�õĿռ�
	{
		start_ringbuffer_ptr = ptr;													//��¼�ṩ�Ŀռ�ָ��
		malloc_flag = NO;															//��¼�ǲ������з���Ŀռ�
	}
	else
	{
		start_ringbuffer_ptr = basic_malloc(size);									//�ڴ������ɹ������							
		if (start_ringbuffer_ptr == 0)
			return FAIL;
		malloc_flag = YES;															//��¼�����з���Ŀռ�
	}
	end_ringbuffer_ptr = start_ringbuffer_ptr + size;
	write_location_ptr = start_ringbuffer_ptr;										//��ʼ�����ָ��
	read_location_ptr = start_ringbuffer_ptr;
	ringbuffer_size = size;															//�������Ŀռ��С
	leading_flag = NO;
	return SUCCESS;
}



u8 deinitial_buffer(void)
{
	if (malloc_flag == YES)															//�ж��Ƿ������з���Ŀռ�
		basic_free(start_ringbuffer_ptr);											//�ͷſռ�
	ringbuffer_size = 0;
	start_ringbuffer_ptr = NULL_PTR;												//��ֹҰָ��
	end_ringbuffer_ptr = NULL_PTR;
	return SUCCESS;
}




void write_buffer_len(u32 datalen)
{
	u32 write_len;																	//д���ݴ�С															//������ָ��

	if (write_location_ptr + datalen < end_ringbuffer_ptr)							//��д���������� write �� end ֮��ʱ
	{
		write_location_ptr += datalen % ringbuffer_size;
		if (leading_flag == YES)
			read_location_ptr = write_location_ptr;
	}
	else if ((datalen - 1) / ringbuffer_size > 0)									//��д�����ݴ�������������ʱ
	{
		write_location_ptr = start_ringbuffer_ptr + (read_location_ptr - start_ringbuffer_ptr);
		leading_flag = YES;
	}
	else																			//��д���������ڻ�������С�� �� ����write �� end ֮��ʱ
	{
		write_len = datalen - (end_ringbuffer_ptr - write_location_ptr);
		write_location_ptr = start_ringbuffer_ptr;
		if (write_len + start_ringbuffer_ptr >= read_location_ptr)
		{
			leading_flag = YES;
			if (write_len == ringbuffer_size)
				read_location_ptr = start_ringbuffer_ptr;
			else
				read_location_ptr = write_location_ptr + write_len;
		}
		write_location_ptr += write_len;
		if (leading_flag == YES)
			read_location_ptr = write_location_ptr;
	}
}





void write_buffer_data(u8* data, u32 datalen)
{
	u32 write_len;																	//д���ݴ�С
	u8* read_ptr;																	//������ָ��
	u32 _len;																		//��ʱ���ڱ����ϴζ����ݵĴ�С

	if (write_location_ptr + datalen < end_ringbuffer_ptr)							//��д���������� write �� end ֮��ʱ
	{
		write_len = datalen;
		read_ptr = data;
		while (write_len--)
			*(write_location_ptr++) = *(read_ptr++);
		if (write_location_ptr == end_ringbuffer_ptr)
			write_location_ptr = start_ringbuffer_ptr;
		if (leading_flag == YES)
			read_location_ptr = write_location_ptr;
	}
	else if ((datalen - 1) / ringbuffer_size > 0)									//��д�����ݴ�������������ʱ
	{
		write_len = end_ringbuffer_ptr - read_location_ptr;
		read_ptr = data + datalen - ringbuffer_size;
		write_location_ptr = read_location_ptr;
		while (write_len--)
			*(write_location_ptr++) = *(read_ptr++);
		write_location_ptr = start_ringbuffer_ptr;
		write_len = read_location_ptr - start_ringbuffer_ptr;
		while (write_len--)
			*(write_location_ptr++) = *(read_ptr++);
		leading_flag = YES;
	}
	else																			//��д���������ڻ�������С�� �� ����write �� end ֮��ʱ
	{
		write_len = end_ringbuffer_ptr - write_location_ptr;
		_len = write_len;
		read_ptr = data;
		while (write_len--)
			*(write_location_ptr++) = *(read_ptr++);
		write_location_ptr = start_ringbuffer_ptr;
		write_len = datalen - _len;



		if (write_len + start_ringbuffer_ptr >= read_location_ptr)
		{
			leading_flag = YES;
			if (write_len == ringbuffer_size)
				read_location_ptr = start_ringbuffer_ptr;
			else
				read_location_ptr = write_location_ptr + write_len;
		}
		while (write_len--)
			*(write_location_ptr++) = *(read_ptr++);
		if (leading_flag == YES)
			read_location_ptr = write_location_ptr;
	}

}



u8* get_unread_data(u32 *len)
{
	if (return_data_buffer != NULL_PTR)
		basic_free(return_data_buffer);
	return_data_buffer = basic_malloc(SUR_SIZE);
	*len = SUR_SIZE;
	if(WR_SEL)
		basic_memcpy(return_data_buffer, read_location_ptr, write_location_ptr - read_location_ptr);
	else
	{
		basic_memcpy(return_data_buffer, read_location_ptr, end_ringbuffer_ptr - read_location_ptr);
		basic_memcpy(return_data_buffer + (end_ringbuffer_ptr - read_location_ptr), start_ringbuffer_ptr, write_location_ptr - start_ringbuffer_ptr);
	}
	read_location_ptr = write_location_ptr;
	return return_data_buffer;
}


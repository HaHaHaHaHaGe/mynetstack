#include "ringbuffer.h"

#define WR_SEL (read_location_ptr < write_location_ptr)
#define SUR_SIZE ((WR_SEL)?(write_location_ptr - read_location_ptr)\
						:(end_ringbuffer_ptr - read_location_ptr + write_location_ptr - start_ringbuffer_ptr))

u8* start_ringbuffer_ptr;															//缓冲区起始位置
u8* end_ringbuffer_ptr;																//缓冲区截止位置
u8* write_location_ptr;																//写数据位置
u8* read_location_ptr;																//读数据位置

u8* return_data_buffer;																//用于返回的数据组

u32 ringbuffer_size;																//缓冲区大小
u8 malloc_flag;																		//改缓冲区是否是自行创建的

u8 leading_flag;																	//当前写数据是否领先读数据一个周期

u8 initial_buffer(u8* ptr,u32 size)
{
	if (ptr != NULL_PTR)															//判断是否是提供好的空间
	{
		start_ringbuffer_ptr = ptr;													//记录提供的空间指针
		malloc_flag = NO;															//记录是不是自行分配的空间
	}
	else
	{
		start_ringbuffer_ptr = basic_malloc(size);									//内存分配与成功与否检测							
		if (start_ringbuffer_ptr == 0)
			return FAIL;
		malloc_flag = YES;															//记录是自行分配的空间
	}
	end_ringbuffer_ptr = start_ringbuffer_ptr + size;
	write_location_ptr = start_ringbuffer_ptr;										//初始化相关指针
	read_location_ptr = start_ringbuffer_ptr;
	ringbuffer_size = size;															//保存分配的空间大小
	leading_flag = NO;
	return SUCCESS;
}



u8 deinitial_buffer(void)
{
	if (malloc_flag == YES)															//判断是否是自行分配的空间
		basic_free(start_ringbuffer_ptr);											//释放空间
	ringbuffer_size = 0;
	start_ringbuffer_ptr = NULL_PTR;												//防止野指针
	end_ringbuffer_ptr = NULL_PTR;
	return SUCCESS;
}




void write_buffer_len(u32 datalen)
{
	u32 write_len;																	//写数据大小															//读数据指针

	if (write_location_ptr + datalen < end_ringbuffer_ptr)							//当写入数据量在 write 与 end 之间时
	{
		write_location_ptr += datalen % ringbuffer_size;
		if (leading_flag == YES)
			read_location_ptr = write_location_ptr;
	}
	else if ((datalen - 1) / ringbuffer_size > 0)									//当写入数据大于整个缓冲区时
	{
		write_location_ptr = start_ringbuffer_ptr + (read_location_ptr - start_ringbuffer_ptr);
		leading_flag = YES;
	}
	else																			//当写入数据量在缓冲区大小内 但 不在write 与 end 之间时
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
	u32 write_len;																	//写数据大小
	u8* read_ptr;																	//读数据指针
	u32 _len;																		//临时用于保存上次读数据的大小

	if (write_location_ptr + datalen < end_ringbuffer_ptr)							//当写入数据量在 write 与 end 之间时
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
	else if ((datalen - 1) / ringbuffer_size > 0)									//当写入数据大于整个缓冲区时
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
	else																			//当写入数据量在缓冲区大小内 但 不在write 与 end 之间时
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


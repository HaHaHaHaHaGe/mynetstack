#include "test_main.h"

extern LIST recv_data_list;
extern LIST send_data_list;
u32 ______UNIT_read_write_data______(u8* filepath)
{
	FILE *fp;   //  头文件#include <stdio.h>
	u8 rdata[896*2];
	u8 *l1, *l2, *stop;
	u32 e1, e2;
	LIST_DATA *recv;
	ringbuffer ring;
	initial_buffer(&ring, YES, 1024 * 50);
	fopen_s(&fp, filepath, "rb");
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp,0, SEEK_SET);
	if (fp == NULL)
	{
		return NO;
	}


	while (1)
	{
		u32 rlen = fread(rdata, sizeof(char), 896, fp);
		if (rlen == 0)
			break;
		//fseek(fp, rlen, SEEK_CUR);
		u8* dst = packing(rdata, 896);
		write_buffer_data(&ring, dst, 1024 + 12);

		if(rand() % 5 == 1)
		while(1)
		{
			get_unread_ptr(&ring, &l1, &l2, &e1, &e2, YES);												//以预览模式监视缓存数据
			stop = unpacking(l1, l2, e1, e2);															//对监视的数据进行数据包识别
			if (stop != NULL_PTR)
				update_readlocation_len(&ring, (stop > (l1 + e1)) ? (e1 + stop - l2) : (stop - l1));	//如果在监视的数据中检查到了数据包并被保存后，则干预被监视的数据
			else
				break;
		}
	}

	fseek(fp, 0, SEEK_SET);
	u8 *bigdata = basic_malloc(size);
	fread_s(bigdata, size, 1, size, fp);

	recv = recv_data_list.start;


	u32 sum = 0;
	while (recv != NULL_PTR)
	{

		u32 rlen = recv->len;

		for (int i = 0; i < rlen; i++)
		{
			if (bigdata[i + sum] != recv->data[i])
				return NO;
		}
		sum += rlen;
		recv = recv->next;
	}
	fclose(fp);
	return YES;
}
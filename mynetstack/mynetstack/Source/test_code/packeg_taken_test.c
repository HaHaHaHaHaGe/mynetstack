#include "test_main.h"

u32 ______search_packeg______(u32 loop)
{
	u8 send[20];
	u8 *src_1 = basic_malloc(48);
	u8 *src_2 = basic_malloc(48);

	u8 *rdata_1, *rdata_2;
	u32 len_1, len_2;
	u32 i;

	u8 success = NO;
	

	////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef Little_Endian
	send[0] = 0xff;
	send[1] = 0xff;
	send[2] = 0xff;
	send[3] = 0xff;

	send[4] = 0x00;
	send[5] = 0x00;
	send[6] = 0x00;
	send[7] = 0x08;
	//5B689F93
	send[8] = 0x5b;
	send[9] = 0x68;
	send[10] = 0x9f;
	send[11] = 0x93;

	send[12] = 0x12;
	send[13] = 0x23;
	send[14] = 0x34;
	send[15] = 0x45;
	send[16] = 0x56;
	send[17] = 0x67;
	send[18] = 0x78;
	send[19] = 0x89;
#else
	send[0] = 0xff;
	send[1] = 0xff;
	send[2] = 0xff;
	send[3] = 0xff;

	send[4] = 0x08;
	send[5] = 0x00;
	send[6] = 0x00;
	send[7] = 0x00;
	//5B689F93
	send[8] = 0x93;
	send[9] = 0x9f;
	send[10] = 0x68;
	send[11] = 0x5b;

	send[12] = 0x12;
	send[13] = 0x23;
	send[14] = 0x34;
	send[15] = 0x45;
	send[16] = 0x56;
	send[17] = 0x67;
	send[18] = 0x78;
	send[19] = 0x89;
#endif
	while (loop--)
	{
		u8 l = rand() % (48 * 2);
		u8 errordata = NO;
		u8 error = NO;
		u8 error_l = rand() % (19);
		u8 *stop;
		error = (rand() % 2) ? YES : NO;

		if (l >= 48)
		{
			for (i = 0; i < 20; i++) {
				if (l < 48 * 2)
					src_2[(l++) - 48] = send[i];
				else
					errordata = YES;
				if (error_l == i && error == YES)
				{
					errordata = YES;
					break;
				}
			}
		}
		else
		{
			for (i = 0; i < 20; i++) {
				if (l < 48)
					src_1[(l++)] = send[i];
				else
					if (l < 48 * 2)
						src_2[(l++) - 48] = send[i];
					else
						errordata = YES;
				if (error_l == i && error == YES)
				{
					errordata = YES;
					break;
				}
			}
		}

		success = search_packeg(src_1, src_2, 48, 48, &rdata_1, &rdata_2, &len_1, &len_2, &stop);
		if (success == NO && errordata == YES)
		{
#ifdef ____SHOW__DEBUG____
			printf("YES\r\n");
#endif
			if (i < 3 && stop != src_2 + 48 - 1)
				return NO;
			if (i >= 3 && *stop != 0xff)
				return NO;
			for (i = 0; i < 48; i++)
			{
				src_1[i] = 0;
				src_2[i] = 0;
			}
			continue;
		}
		if ((success == NO && errordata == NO) || (success == YES && errordata == YES))
		{
			return NO;
		}
		if (*stop != 0x89)
			return NO;
		l = 12;

		for (i = 0; i < len_1; i++)
		{
			if (rdata_1[i] != send[l++])
				return NO;
#ifdef ____SHOW__DEBUG____
			printf("0x%0X	", rdata_1[i]);
#endif
		}
		for (i = 0; i < len_2; i++)
		{
			if (rdata_2[i] != send[l++])
				return NO;
#ifdef ____SHOW__DEBUG____
			printf("0x%0X	", rdata_2[i]);
#endif
		}
#ifdef ____SHOW__DEBUG____
		printf("\r\n");
#endif

		for (i = 0; i < 48; i++)
		{
			src_1[i] = 0;
			src_2[i] = 0;
		}
	}
	return YES;
}




u8 ____trans_8to7b_7to8b____(u32 loop)
{
	u8 *src = basic_malloc(896 * loop);
	u8 *dst = basic_malloc(1024 * loop + 1);
	u8 *src_2 = basic_malloc(896 * loop);
	u32 i = 0;
	u8 flag = YES;
	for (i = 0; i < 896 * loop; i++)
		src[i] = rand();
	for (i = 0; i < 1024 * loop + 1; i++)
		dst[i] = 0;
	for (i = 0; i < 896 * loop; i++)
		src_2[i] = 0;

	trans_8to7b_64bytes_fast(src, dst, 896 * loop);
	trans_7to8b_64bytes_fast(dst, src_2, 1024 * loop);
	for (i = 0; i < (1024* loop *7)/8; i++)
		if (src[i] != src_2[i])
			flag = NO;
	return flag;
}


u8 ____trans_8to7b_7to8b____1(u32 loop)
{
	u8 src[56];
	u8 dst[64+1];
	u8 src_2[56];
	u32 i = 0;
	u8 flag = YES;
	for (i = 0; i < 56; i++)
		src[i] = i+0x80;
	for (i = 0; i < 65; i++)
		dst[i] = 0;
	for (i = 0; i < 56; i++)
		src_2[i] = 0;
	trans_8to7b_64bytes_fast(src, dst, 56);
	trans_7to8b_64bytes_fast(dst, src_2, 64);
	for (i = 0; i < (1024 * loop * 7) / 8; i++)
		if (src[i] != src_2[i])
			flag = NO;
	return flag;
}



extern LIST recv_data_list;
extern LIST send_data_list;
u8 ____packing_unpackeg___(u32 loop)
{
	u8 *src = basic_malloc(896);
	u8 *dst = basic_malloc(2048);
	u8 *l1, *l2, stop;
	u32 e1, e2;
	u32 i,j;
	LIST_DATA *recv;
	ringbuffer ring;

	u32 lop2 = 100;
	u32 lop3 = loop;

	u32 rrr;
	while (lop2--)
	{
		loop = lop3;
		rrr = (rand() % 1024*10) + 3108 ;
		initial_buffer(&ring, YES, 2072);
		while (loop--)
		{
			for (j = 0; j < 3; j++)
			{
				for (i = 0; i < 896; i++)
				{
					src[i] = rand() % 256;
				}
				dst = packing(src, 896);
				write_buffer_data(&ring, dst, 1024 + 12);
			}
			if (loop == 0x3d5)
				i = 0;

			get_unread_ptr(&ring, &l1, &l2, &e1, &e2, NO);
			stop = unpacking(l1, l2, e1, e2);
			recv = recv_data_list.end;
			for (i = 0; i < 896; i++)
			{
				if (src[i] != recv->data[i])
					return NO;
			}
		}
		recv = recv_data_list.start;
		while (recv)
		{
			basic_free(recv->data);
			Delete_List(&recv_data_list, recv);
			recv = recv_data_list.start;
		}

		recv = send_data_list.start;
		while (recv)
		{
			basic_free(recv->data);
			Delete_List(&send_data_list, recv);
			recv = send_data_list.start;
		}
		deinitial_buffer(&ring);

	}

	return YES;
}

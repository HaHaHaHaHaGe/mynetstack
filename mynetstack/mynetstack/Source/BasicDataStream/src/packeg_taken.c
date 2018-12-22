#include "../inc/packeg_taken.h"
//原始数据包包头
const u8 packet_header[4] = { 0xFF,0xFF,0xFF,0xFF };
unsigned char casual_buffer[__REDUCTION_DATA_LENGTH__];

LIST recv_data_list;
LIST send_data_list;

void packeg_taken_init(void)
{
	Init_List(&recv_data_list);
	Init_List(&send_data_list);
}



u8 search_packeg(u8*src1, u8*src2, u32 len1, u32 len2, u8**rdata_1,u8**rdata_2,u32*rlen_1,u32*rlen_2,u8** stop_ptr)
{
	u8 n = 0;
	u8* src_1 = src1;
	u8* src_2 = src2;
	u32 len_1 = len1;
	u32 len_2 = len2;
	u32 crc32_1 = 0;
	u32 crc32_2;
	u32 swap_len;
	u32 len = 0;
	while (len_1--)
		if (*(src_1++) == packet_header[n])
		{
			n++;
			if (n == sizeof(packet_header))
			{
				if (src_1 + 4 > src1 + len1)
				{
					if (len2 < 8)
					{
						*stop_ptr = src2 + len2 - 1;
						return NO;
					}
//#ifdef Little_Endian
//					if (src_1 + 1 == src1 + len1 && len2 >= 3)
//					{
//						((u8*)&len)[3] = *src_1;
//						((u8*)&len)[2] = *src2;
//						((u8*)&len)[1] = *(src2 + 1);
//						((u8*)&len)[0] = *(src2 + 2);
//					}
//					else if (src_1 + 2 == src1 + len1 && len2 >= 2)
//					{
//						((u8*)&len)[3] = *src_1;
//						((u8*)&len)[2] = *(src_1 + 1);
//						((u8*)&len)[1] = *(src2);
//						((u8*)&len)[0] = *(src2 + 1);
//					}
//					else if (src_1 + 3 == src1 + len1 && len2 >= 1)
//					{
//						((u8*)&len)[3] = *src_1;
//						((u8*)&len)[2] = *(src_1 + 1);
//						((u8*)&len)[1] = *(src_1 + 2);
//						((u8*)&len)[0] = *(src2);
//					}
//					else
//					{
//						len = *((u32*)src2);
//						len = basic_swap(len);
//					}
//#else
					if (src_1 + 1 == src1 + len1 && len2 >= 3)
					{
						((u8*)&len)[0] = *src_1;
						((u8*)&len)[1] = *src2;
						((u8*)&len)[2] = *(src2 + 1);
						((u8*)&len)[3] = *(src2 + 2);
					}
					else if (src_1 + 2 == src1 + len1 && len2 >= 2)
					{
						((u8*)&len)[0] = *src_1;
						((u8*)&len)[1] = *(src_1 + 1);
						((u8*)&len)[2] = *(src2);
						((u8*)&len)[3] = *(src2 + 1);
					}
					else if (src_1 + 3 == src1 + len1 && len2 >= 1)
					{
						((u8*)&len)[0] = *src_1;
						((u8*)&len)[1] = *(src_1 + 1);
						((u8*)&len)[2] = *(src_1 + 2);
						((u8*)&len)[3] = *(src2);
					}
					else
					{
						len = *((u32*)src2);
					}
//#endif
					*stop_ptr = src_1 - 1;
					if ((src_1 + 4 - src1 - len1) + 4 + len > len2)
						return NO;

					if (len > __REDUCTION_DATA_LENGTH__ || len == 0)
						return NO;

					crc32_1 = *(u32*)(src2 + (src_1 + 4 - src1 - len1));

#ifdef Little_Endian
					crc32_1 = basic_swap(crc32_1);
					swap_len = len;
					len = basic_swap(len);
#else
					swap_len = basic_swap(len);
#endif

					crc32_2 = crc32_16bytes(&swap_len, 4, 0xFFFFFFFF);


					crc32_2 = crc32_16bytes((u32*)(src2 + (src_1 + 4 - src1 - len1) + 4), len, crc32_2);
					if (crc32_2 == crc32_1)
					{
						*stop_ptr = (src2 + (src_1 + 4 - src1 - len1) + 4) + len - 1;
						*rlen_1 = len;
						*rdata_1 = (src2 + (src_1 + 4 - src1 - len1) + 4);
						*rlen_2 = NULL_PTR;
						*rdata_2 = 0;
						return YES;
					}
					return NO;
				}
				*stop_ptr = src_1 - 1;
				len = *(u32*)src_1;

#ifdef Little_Endian
				swap_len = len;
				len = basic_swap(len);
#else
				swap_len = basic_swap(len);
#endif

				crc32_2 = crc32_16bytes(&swap_len, 4, 0xFFFFFFFF);

				if (len > __REDUCTION_DATA_LENGTH__ || len == 0)
					return NO;
				if (src_1 + 4 + 4 > src1 + len1)
				{
					if (len2 < 8)
					{
						*stop_ptr = src2 + len2 - 1;
						return NO;
					}
#ifdef Little_Endian
					if (src_1 + 4 + 1 == src1 + len1 && len2 >= 3)
					{
						((u8*)&crc32_1)[3] = *(src_1 + 4);
						((u8*)&crc32_1)[2] = *src2;
						((u8*)&crc32_1)[1] = *(src2 + 1);
						((u8*)&crc32_1)[0] = *(src2 + 2);
					}
					else if (src_1 + 4 + 2 == src1 + len1 && len2 >= 2)
					{
						((u8*)&crc32_1)[3] = *(src_1 + 4);
						((u8*)&crc32_1)[2] = *(src_1 + 4 + 1);
						((u8*)&crc32_1)[1] = *(src2);
						((u8*)&crc32_1)[0] = *(src2 + 1);
					}
					else if (src_1 + 4 + 3 == src1 + len1 && len2 >= 1)
					{
						((u8*)&crc32_1)[3] = *(src_1 + 4);
						((u8*)&crc32_1)[2] = *(src_1 + 4 + 1);
						((u8*)&crc32_1)[1] = *(src_1 + 4 + 2);
						((u8*)&crc32_1)[0] = *(src2);
					}
					else
					{
						crc32_1 = *((u32*)src2);
						crc32_1 = basic_swap(crc32_1);
					}
#else
					if (src_1 + 4 + 1 == src1 + len1 && len2 >= 3)
					{
						((u8*)&crc32_1)[0] = *(src_1 + 4);
						((u8*)&crc32_1)[1] = *src2;
						((u8*)&crc32_1)[2] = *(src2 + 1);
						((u8*)&crc32_1)[3] = *(src2 + 2);
					}
					else if (src_1 + 4 + 2 == src1 + len1 && len2 >= 2)
					{
						((u8*)&crc32_1)[0] = *(src_1 + 4);
						((u8*)&crc32_1)[1] = *(src_1 + 4 + 1);
						((u8*)&crc32_1)[2] = *(src2);
						((u8*)&crc32_1)[3] = *(src2 + 1);
					}
					else if (src_1 + 4 + 3 == src1 + len1 && len2 >= 1)
					{
						((u8*)&crc32_1)[0] = *(src_1 + 4);
						((u8*)&crc32_1)[1] = *(src_1 + 4 + 1);
						((u8*)&crc32_1)[2] = *(src_1 + 4 + 2);
						((u8*)&crc32_1)[3] = *(src2);
					}
					else
					{
						crc32_1 = *((u32*)src2);
					}
#endif
					*stop_ptr = src_1 - 1;
					if ((src_1 + 4 + 4 - src1 - len1) + len > len2)
						return NO;

					//swap_len = basic_swap(len);
					

					crc32_2 = crc32_16bytes((u32*)(src2 + (src_1 + 4 + 4 - src1 - len1)), len, crc32_2);
					if (crc32_2 == crc32_1)
					{
						*stop_ptr = (src2 + (src_1 + 4 - src1 - len1) + 4) + len - 1;
						*rlen_1 = len;
						*rdata_1 = (src2 + (src_1 + 4 - src1 - len1) + 4);
						*rlen_2 = NULL_PTR;
						*rdata_2 = 0;
						return YES;
					}
					return NO;
				}
				crc32_1 = *(u32*)(src_1 + 4);
#ifdef Little_Endian
				crc32_1 = basic_swap(crc32_1);
				len = basic_swap(len);
#endif
				*stop_ptr = src_1 - 1;
				if ((src_1 + 4 + 4 + len) > src1 + len1)
					if(len - (src1 + len1 - (src_1 + 4 + 4)) > len2)
						return NO;
					else
					{

						
						//crc32_2 = crc32_16bytes((u32*)(&len), 4, 0xFFFFFFFF);

						crc32_2 = crc32_16bytes((u32*)(src_1 + 4 + 4), (src1 + len1 - (src_1 + 4 + 4)), crc32_2);
						crc32_2 = crc32_16bytes((u32*)src2, len - (src1 + len1 - (src_1 + 4 + 4)), crc32_2);
						if (crc32_2 == crc32_1)
						{
							*stop_ptr = src2 + len - (src1 + len1 - (src_1 + 4 + 4)) - 1;
							*rlen_1 = (src1 + len1 - (src_1 + 4 + 4));
							*rdata_1 = (src_1 + 4 + 4);
							*rlen_2 = len - (src1 + len1 - (src_1 + 4 + 4));
							*rdata_2 = src2;
							return YES;
						}
						return NO;
					}

				//swap_len = basic_swap(len);
				//crc32_2 = crc32_16bytes((u32*)(&len), 4, 0xFFFFFFFF);

				crc32_2 = crc32_16bytes((u32*)(src_1 + 4 + 4), len, crc32_2);
				if (crc32_2 == crc32_1)
				{
					*stop_ptr = (src_1 + 4 + 4) + len - 1;
					*rlen_1 = len;
					*rdata_1 = (src_1 + 4 + 4);
					*rlen_2 = NULL_PTR;
					*rdata_2 = 0;
					return YES;
				}
				return NO;
			}
		}
	
		
		
		
	if (len2 >= 3 + 8)
		if ((*(src1 + len1 - 1) == packet_header[0]) && (*(src2) == packet_header[1]) && (*(src2 + 1) == packet_header[2]) && (*(src2 + 2) == packet_header[3]))
			src_2 = src2 + 3;

	if (len2 >= 2 + 8)
		if ((*(src1 + len1 - 1) == packet_header[1]) && (*(src1 + len1 - 2) == packet_header[0]) && (*(src2) == packet_header[2]) && (*(src2 + 1) == packet_header[3]))
			src_2 = src2 + 2;

	if (len2 >= 1 + 8)
		if ((*(src1 + len1 - 1) == packet_header[2]) && (*(src1 + len1 - 2) == packet_header[1]) && (*(src1 + len1 - 3) == packet_header[0]) && (*(src2) == packet_header[3]))
			src_2 = src2 + 1;
	if (src_2 != src2)
	{
		*stop_ptr = src_2 - 1;
		if ((src_2 - src2) + 8 > len2)
			return NO;
		len = *(u32*)src_2;
		crc32_1 = *(u32*)(src_2 + 4);
#ifdef Little_Endian
		len = basic_swap(len);
		crc32_1 = basic_swap(crc32_1);
		swap_len = len;
#else
		swap_len = basic_swap(len);
#endif
		if (len > __REDUCTION_DATA_LENGTH__ || len == 0)
			return NO;
		if ((src_2 - src2) + 8 + len > len2)
			return NO;

		crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);

		crc32_2 = crc32_16bytes((u32*)(src_2 + 8), len, crc32_2);
		if (crc32_2 == crc32_1)
		{
			*stop_ptr = src_2 + 8 + len - 1;
			*rlen_1 = len;
			*rdata_1 = src_2 + 8;
			*rlen_2 = NULL_PTR;
			*rdata_2 = 0;
			return YES;
		}
		return NO;
	}

	n = 0;
	while (len_2--)
		if (*(src_2++) == packet_header[n])
		{
			n++;
			if (n == sizeof(packet_header))
			{
				*stop_ptr = src_2 - 1;
				if (src_2 + 8 > src2 + len2)
					return NO;
				len = *(u32*)src_2;
				crc32_1 = *(u32*)(src_2 + 4);
#ifdef Little_Endian
				len = basic_swap(len);
				crc32_1 = basic_swap(crc32_1);
				swap_len = len;
#else
				swap_len = basic_swap(len);
#endif
				if(len > __REDUCTION_DATA_LENGTH__ || len == 0)
					return NO;
				if (src_2 + 8 + len > src2 + len2)
					return NO;

				
				crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);

				crc32_2 = crc32_16bytes((u32*)(src_2 + 8), len, crc32_2);
				if (crc32_2 == crc32_1)
				{
					*stop_ptr = src_2 + 8 + len - 1;
					*rlen_1 = len;
					*rdata_1 = src_2 + 8;
					*rlen_2 = NULL_PTR;
					*rdata_2 = 0;
					return YES;
				}
				return NO;
			}
		}
	if(src2 != NULL_PTR)
		*stop_ptr = src2 + len2 - 1;
	else
		*stop_ptr = src1 + len1 - 1;
	return NO;
}




u8* unpacking(u8* src1,u8* src2,u32 len1,u32 len2)
{
	u8 Success;
	u8 *data_1 = src1, *data_2 = src2;
	u32 len_1 = len1, len_2 = len2;

	u8 *recvdata_1, *recvdata_2;
	u32 recvlen_1, recvlen_2;
	u8 *stop = NULL_PTR;

	u8 *recv = NULL_PTR;

	if (src1 == NULL_PTR)
		return NULL_PTR;

	while (1)
	{
		Success = search_packeg(data_1, data_2, len_1, len_2, &recvdata_1, &recvdata_2, &recvlen_1, &recvlen_2, &stop);

		if (stop <= data_1 + len_1 && stop > data_1)
		{
			len_1 -= stop - data_1 + 1;
			data_1 = stop + 1;
			if (len_1 == 0)
			{
				data_1 = data_2;
				len_1 = len_2;
				data_2 = NULL_PTR;
				len_2 = 0;
			}
		}
		if (stop <= data_2 + len_2 && stop >= data_2)
		{
			len_1 = len_2 - (stop - data_2 + 1);
			data_1 = stop + 1;
			data_2 = NULL_PTR;
			len_2 = 0;
		}

		if (Success == YES)
		{
			if (((recvlen_1 + recvlen_2) * 7) % 8 != 0)
				continue;
			basic_memcpy(casual_buffer, recvdata_1, recvlen_1);
			if(recvdata_2 != NULL_PTR)
				basic_memcpy(&casual_buffer[recvlen_1], recvdata_2, recvlen_2);
			recv = basic_calloc((recvlen_1 + recvlen_2) * 7 / 8 + 1, 1);
			trans_7to8b_64bytes_fast(casual_buffer, recv, recvlen_1 + recvlen_2);
			Add_List(&recv_data_list, recv, (recvlen_1 + recvlen_2) * 7 / 8);
		}
		else
			return (recv == NULL_PTR) ?  NULL_PTR : recv + recvlen_1 + recvlen_2;
	}
}


u8* packing(u8 *data,u32 len)
{
	u32 crc,lensw;
	u32 dlen = (len * 8) / 7;
	u8* sdata = basic_calloc(dlen + 12 + 1, 1);
	trans_8to7b_64bytes_fast(data,&sdata[12],len);
	sdata[0] = packet_header[0];
	sdata[1] = packet_header[1];
	sdata[2] = packet_header[2];
	sdata[3] = packet_header[3];
	sdata[4] = ((u8*)&dlen)[0];
	sdata[5] = ((u8*)&dlen)[1];
	sdata[6] = ((u8*)&dlen)[2];
	sdata[7] = ((u8*)&dlen)[3];
	lensw = basic_swap(dlen);
	crc = crc32_16bytes(&lensw, 4, 0xffffffff);
	crc = crc32_16bytes((u32*)&sdata[12], dlen, crc);
	sdata[8] = ((u8*)&crc)[0];
	sdata[9] = ((u8*)&crc)[1];
	sdata[10] = ((u8*)&crc)[2];
	sdata[11] = ((u8*)&crc)[3];
	Add_List(&send_data_list, sdata, dlen);
	return sdata;
}
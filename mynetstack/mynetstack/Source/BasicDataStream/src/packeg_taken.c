#include "../inc/packeg_taken.h"
//原始数据包包头
const u8 packet_header[4] = { 0xFF,0xFF,0xFF,0xFF };


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
#ifdef Little_Endian
					if (src_1 + 1 == src1 + len1 && len2 >= 3)
					{
						((u8*)&len)[3] = *src_1;
						((u8*)&len)[2] = *src2;
						((u8*)&len)[1] = *(src2 + 1);
						((u8*)&len)[0] = *(src2 + 2);
					}
					else if (src_1 + 2 == src1 + len1 && len2 >= 2)
					{
						((u8*)&len)[3] = *src_1;
						((u8*)&len)[2] = *(src_1 + 1);
						((u8*)&len)[1] = *(src2);
						((u8*)&len)[0] = *(src2 + 1);
					}
					else if (src_1 + 3 == src1 + len1 && len2 >= 1)
					{
						((u8*)&len)[3] = *src_1;
						((u8*)&len)[2] = *(src_1 + 1);
						((u8*)&len)[1] = *(src_1 + 2);
						((u8*)&len)[0] = *(src2);
					}
					else
					{
						len = *((u32*)src2);
						len = basic_swap(len);
					}
#else
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
#endif
					*stop_ptr = src_1 - 1;
					if ((src_1 + 4 - src1 - len1) + 4 + len > len2)
						return NO;

					if (len > __REDUCTION_DATA_LENGTH__ || len == 0)
						return NO;

					crc32_1 = *(u32*)(src2 + (src_1 + 4 - src1 - len1));
#ifdef Little_Endian
					crc32_1 = basic_swap(crc32_1);
#endif

					swap_len = basic_swap(len);
					crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);


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
				len = basic_swap(len);
#endif
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

					swap_len = basic_swap(len);
					crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);

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
#endif
				*stop_ptr = src_1 - 1;
				if ((src_1 + 4 + 4 + len) > src1 + len1)
					if(len - (src1 + len1 - (src_1 + 4 + 4)) > len2)
						return NO;
					else
					{

						swap_len = basic_swap(len);
						crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);

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

				swap_len = basic_swap(len);
				crc32_2 = crc32_16bytes((u32*)(&swap_len), 4, 0xFFFFFFFF);

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
#endif
		if (len > __REDUCTION_DATA_LENGTH__ || len == 0)
			return NO;
		if ((src_2 - src2) + 8 + len > len2)
			return NO;

		swap_len = basic_swap(len);
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
#endif
				if(len > __REDUCTION_DATA_LENGTH__ || len == 0)
					return NO;
				if (src_2 + 8 + len > src2 + len2)
					return NO;

				swap_len = basic_swap(len);
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
	*stop_ptr = src2 + len2 - 1;
	return NO;
}


void trans_8to7b(u8 *src, u8 *dst, u32 dst_len)
{
	u32 len = dst_len;
	u32 ss1;
	while(len--)
	{
		ss1 = (8 * len + 1) - (8 * len + 1) / 8 - 1;
		if (ss1 % 8)
		{
			dst[len] = (src[ss1 / 8] << (ss1 % 8 - 1)) & 0x7f;
			dst[len] |= src[(ss1 + 8 - ss1 % 8) / 8] >> (9 - ss1 % 8);
		}
		else
		{
			dst[len] = src[ss1 / 8] >> 1;
		}
	}
}

void trans_7to8b(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 ss1;
	for (len = 0; len < src_len; len++)
	{
		ss1 = (8 * len + 1) - (8 * len + 1) / 8 - 1;
		if (ss1 % 8)
		{
			dst[ss1 / 8] |= src[len] >> (ss1 % 8 - 1);
			dst[(ss1 + 8 - ss1 % 8) / 8] = src[len] << (9 - ss1 % 8);
		}
		else
		{
			dst[ss1 / 8] = src[len] << 1;
		}
	}
}

void trans_8to7b_64bytes(u8 *src, u8 *dst, u32 dst_len)
{
	u32 len = dst_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - (((len << 3) + 1) >> 6);

		dst[len] = src[ss1] >> 1;

		dst[len + 1] = ((src[ss1] << 6) & 0x7f) | src[ss1 + 1] >> 2;

		dst[len + 2] = ((src[ss1 + 1] << 5) & 0x7f) | src[ss1 + 2] >> 3;

		dst[len + 3] = ((src[ss1 + 2] << 4) & 0x7f) | src[ss1 + 3] >> 4;

		dst[len + 4] = ((src[ss1 + 3] << 3) & 0x7f) | src[ss1 + 4] >> 5;

		dst[len + 5] = ((src[ss1 + 4] << 2) & 0x7f) | src[ss1 + 5] >> 6;

		dst[len + 6] = ((src[ss1 + 5] << 1) & 0x7f) | src[ss1 + 6] >> 7;

		dst[len + 7] = src[ss1 + 6] & 0x7f;


	}
}

void trans_7to8b_64bytes(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - (((len << 3) + 1) >> 6);

		dst[ss1] = src[len] << 1 | src[len + 1] >> 6;

		dst[ss1 + 1] = src[len + 1] << 2 | src[len + 2] >> 5;

		dst[ss1 + 2] = src[len + 2] << 3 | src[len + 3] >> 4;

		dst[ss1 + 3] = src[len + 3] << 4 | src[len + 4] >> 3;

		dst[ss1 + 4] = src[len + 4] << 5 | src[len + 5] >> 2;

		dst[ss1 + 5] = src[len + 5] << 6 | src[len + 6] >> 1;

		dst[ss1 + 6] = src[len + 6] << 7 | src[len + 7];
	}
}


void trans_8to4b_64bytes(u8 *src, u8 *dst, u32 dst_len)
{
	u32 len = dst_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - ((8 * len + 1) / 64);

		dst[len] = src[ss1] >> 1;

		dst[len + 1] = ((src[ss1] << 6) & 0x7f) | src[ss1 + 1] >> 2;

		dst[len + 2] = ((src[ss1 + 1] << 5) & 0x7f) | src[ss1 + 2] >> 3;

		dst[len + 3] = ((src[ss1 + 2] << 4) & 0x7f) | src[ss1 + 3] >> 4;

		dst[len + 4] = ((src[ss1 + 3] << 3) & 0x7f) | src[ss1 + 4] >> 5;

		dst[len + 5] = ((src[ss1 + 4] << 2) & 0x7f) | src[ss1 + 5] >> 6;

		dst[len + 6] = ((src[ss1 + 5] << 1) & 0x7f) | src[ss1 + 6] >> 7;

		dst[len + 7] = src[ss1 + 6] & 0x7f;


	}
}

void trans_4to8b_64bytes(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - ((8 * len + 1) / 64);

		dst[ss1] = src[len] << 1 | src[len + 1] >> 6;

		dst[ss1 + 1] = src[len + 1] << 2 | src[len + 2] >> 5;

		dst[ss1 + 2] = src[len + 2] << 3 | src[len + 3] >> 4;

		dst[ss1 + 3] = src[len + 3] << 4 | src[len + 4] >> 3;

		dst[ss1 + 4] = src[len + 4] << 5 | src[len + 5] >> 2;

		dst[ss1 + 5] = src[len + 5] << 6 | src[len + 6] >> 1;

		dst[ss1 + 6] = src[len + 6] << 7 | src[len + 7];
	}
}



u8* unpacking(u8* src1,u8* src2,u32 len1,u32 len2)
{
	u8 Success;
	u8 *data_1 = src1, *data_2 = src2;
	u32 len_1 = len1, len_2 = len2;

	u8 *recvdata_1, *recvdata_2;
	u32 recvlen_1, recvlen_2;
	u8 *stop = NULL_PTR;

	u8 *recv;

	if (src1 == NULL_PTR)
		return FAIL;

	while (stop != data_2 + len2 - 1)
	{
		Success = search_packeg(data_1, data_2, len_1, len_2, &recvdata_1, &recvdata_2, &recvlen_1, &recvlen_2, &stop);

		if (stop <= data_1 + len_1 && stop > data_1)
		{
			len_1 -= stop - data_1 + 1;
			data_1 = stop + 1;
		}
		if (stop <= data_2 + len_2 && stop > data_2)
		{
			data_1 = NULL_PTR;
			len_1 = 0;
			len_2 -= stop - data_2 + 1;
			data_2 = stop + 1;
		}

		if (Success == YES)
		{
			if (((recvlen_1 + recvlen_2) * 7) % 8 != 0)
				return NULL_PTR;
			recv = basic_malloc((recvlen_1 + recvlen_2) * 7 / 8);
			return recv;
		}
	}
	return NULL_PTR;
}



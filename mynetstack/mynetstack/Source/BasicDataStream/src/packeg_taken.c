#include "../inc/packeg_taken.h"


u8* search_head(u8*src, u32 len)
{
	u8 n = 0;
	while (len--)
		if (*(src++) == packet_header[n])
		{
			n++;
			if (n == sizeof(packet_header))
				return src - sizeof(packet_header);
		}
	return NULL_PTR;
}

u8 unpacking(u8* src1,u8* src2,u32 len1,u32 len2, source_data** dispersed_data)
{
	u8* ptr_1 = NULL_PTR;
	u8* ptr_2 = NULL_PTR;
	if (src1 == NULL_PTR)
		return FAIL;
	ptr_1 = search_head(src1, len1);
	ptr_2 = search_head(src2, len2);
	if (ptr_1 != NULL_PTR)
	{
		*dispersed_data = (source_data*)ptr_1;
		if ((*dispersed_data)->packet_len + (u8*)&((*dispersed_data)->packet_data) > ptr_1)
		{
			
		}
	}
}



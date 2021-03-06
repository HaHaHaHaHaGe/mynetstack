#include "../inc/classifier.h"

//全局累加变量
u32 Cumulative = 0;

int get_basepackeg_len(packeg_base * pb)
{
	if(pb->ptype == COMMAND_PACKEG)
		return sizeof(packeg_command) + sizeof(packeg_base) - sizeof(u8*);
	if (pb->ptype == DATA_PACKEG)
		return sizeof(packeg_data) + sizeof(packeg_base) - sizeof(u8*) + ((packeg_data*)pb->data)->datalen;
	return 0;
}

void copy_basepackeg_to_memory(packeg_base * pb, u8 * data)
{
}

void separa_packeg_base(packeg_base* pb,u8 * data)
{
	basic_memcpy(pb, data, sizeof(packeg_base));
	pb->data = data + sizeof(packeg_base) - sizeof(u8*);
}

void separa_packeg_data(packeg_data* pd,packeg_base * data)
{
	if (data->ptype != DATA_PACKEG)
		return;
	basic_memcpy(pd, data, sizeof(packeg_data));
	pd->data = data + sizeof(packeg_data) - sizeof(u8*);
}

void separa_packeg_command(packeg_command* pc,packeg_base * data)
{
	if (data->ptype != COMMAND_PACKEG)
		return;
	basic_memcpy(pc, data, sizeof(packeg_command));
}

packeg_base mix_packeg_base(PACKEG_TYPE pdyte, u32 datalen, u8 * data)
{
	packeg_base recv = { pdyte,basic_time(),datalen ,data };
	return recv;
}

packeg_data mix_packeg_data(DATA_TYPE dtype, u32 datalen, u8 * data)
{
	packeg_data recv = { dtype,Cumulative++,datalen,data };
	return recv;
}

packeg_command mix_packeg_command(COMMAND_TYPE type, u32 count)
{
	packeg_command recv = {type,count};
	return recv;
}

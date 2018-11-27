///////////////////////////////////////////////////////////////////
//创建时间：2018-11-27
//修改时间：2018-11-27
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：从给定数据中(ringbufffer)提取有效数据包
//
//		
//日志：
//
//2018-11-27:创建该文件
//设定包头packet_header，
//确定原始数据结构source_data
//
///////////////////////////////////////////////////////////////////
#ifndef  __PACKEG_TAKEN_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"

#define __REDUCTION_DATA_LENGTH__ 1024


//原始数据包包头
const u8 packet_header[4] = {0xFF,0xFF,0xFF,0xFF};


//原始数据包结构
typedef struct source_data
{
	u8* packet_header;
	u32 packet_len;
	u32 packet_crc32;
	u8* packet_data;
}source_data;

#endif
///////////////////////////////////////////////////////////////////
//创建时间：2018-11-27
//修改时间：2018-12-1
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：从给定数据中(ringbufffer)提取有效数据包
//并进行第一次预处理（高位填充）/（高位预留）
//		
//日志：
//
//2018-11-27:创建该文件
//设定包头packet_header，
//确定原始数据结构source_data
//
//2018-11-30
//去除source_data
//
//2018-12-1
//增加函数search_packeg
///////////////////////////////////////////////////////////////////
#ifndef  __PACKEG_TAKEN_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_crc32.h"

#define __REDUCTION_DATA_LENGTH__ 1024


//原始数据包包头
const u8 packet_header[4] = {0xFF,0xFF,0xFF,0xFF};







/*
从拼接的两段数组中寻找正确的数据包
数据包格式：
-------------------------------------------------------
0-3		4-7		8-11	12-N
包头	数据长	CRC32	数据
-------------------------------------------------------
入口参数：
src1:第一个数组
src2:第二个数组
len1:第一个数组大小
len2:第二个数组大小
rdata_1:返回数据的第一指针
rdata_2:返回数据的第二指针
rlen_1:返回数据第一指针指向的数据段长度
rlen_2:返回数据第二指针指向的数据段长度
返回值：
是否找到数据包
*/
u8 search_packeg(u8*src1, u8*src2, u32 len1, u32 len2, u8**rdata_1, u8**rdata_2, u32*rlen_1, u32*rlen_2);

#endif
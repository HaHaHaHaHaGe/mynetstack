///////////////////////////////////////////////////////////////////
//创建时间：2018-11-27
//修改时间：2018-12-23
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
//
//2018-12-4
//修复search_packeg函数在获得取得错误包时的处理
//增加stop返回值，用于表示该函数停止查找的位置
//
//2018-12-8
//增加函数trans_8to7b与trans_7to8b
//用于将原始数据进行转化，为了进行封包/拆包操作
//未进行优化，100MB的数据进行一次拆\装 共需要5秒（4GHZ的CPU 2700X）
//更新算法trans_8to7b_64bytes、trans_7to8b_64bytes
//优化后的函数，100MB的数据进行一次拆\装 共需要0.28秒（4GHZ的CPU 2700X）
//
//2018-12-9
//将所有trans函数移动到专用文件sdata_trans.c中
//
//2018-12-15
//修改unpacking函数返回值
//增加packing用于封装数据包
//将接收到、准备发送的数据都使用链表进行存储（basic_list.h）
//
//2018-12-23
//修复一些可能导致警告的问题
///////////////////////////////////////////////////////////////////
#ifndef  __PACKEG_TAKEN_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_crc32.h"
#include "../inc/sdata_trans.h"
#include "../../Factory/inc/basic_list.h"

#define __REDUCTION_DATA_LENGTH__ 1024




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
stop_ptr:返回停止查找的位置（被阻断查找的原因包括：成功找到数据包，找到损坏数据包，找到截断数据包）
返回值：
是否找到数据包
*/
u8 search_packeg(u8*src1, u8*src2, u32 len1, u32 len2, u8**rdata_1, u8**rdata_2, u32*rlen_1, u32*rlen_2, u8** stop_ptr);


/*
从拼接的两段数组中寻找正确的数据包并进行7bit->8bit转化
重新分配内存并保存数据
src1:第一个数组
src2:第二个数组
len1:第一个数组大小
len2:第二个数组大小
返回值：
如果没有正确数据包返回NULL_PTR
否则返回查找最后的地址
*/
u8* unpacking(u8* src1, u8* src2, u32 len1, u32 len2);





/*
将输入的数据进行8->7的转化并增加crc与包头，并存储到发送队列
data:准备封包的数据
len:数据大小
返回值：
封装完毕的数据指针
*/
u8* packing(u8 *data, u32 len);
#endif
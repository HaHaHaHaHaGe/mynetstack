///////////////////////////////////////////////////////////////////
//创建时间：2018-11-16
//修改时间：2018-11-16
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：ringbuffer中主要实现数据缓冲功能。环形的读取可以有效
//降低数据被覆盖的可能性
//		
//日志：
//
//2018-11-16:
//创建此文件，增加
//void write_buffer(u8* data, u32 datalen);
//u8 deinitial_buffer(void);
//u8 initial_buffer(u8* ptr, u32 size);
//用于写缓冲区、释放缓冲区、初始化缓冲区
//////////////////////////////////////////////////////////////////
#ifndef  __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include "basic_header.h"

/*
写数据到缓冲区函数
入口参数：
data:写入的数据指针
datalen:写入的数据长度
*/
void write_buffer(u8* data, u32 datalen);


/*
释放缓冲区函数
注：如果在创建时指定了已经开辟好的内存，
那么该函数只会清理此模块内部的变量，
不会更改外部的数据
*/
u8 deinitial_buffer(void);




/*
创建缓冲区函数
注：可在创建时指定已经开辟好的内存，
入口参数：
ptr: 指定外部内存空间，无时需要填写NULL_PTR
size: 需要开辟空间的大小
*/
u8 initial_buffer(u8* ptr, u32 size);


#endif //  __RINGBUFFER_H_

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
//
//2018-11-20
//将void write_buffer(u8* data, u32 datalen);
//更改为void write_buffer_data(u8* data, u32 datalen)
//并修复在写入的数据刚好等于整个缓存大小、并且读指针为起始值时
//无法正确判断并设置当前状态为“超前态”
//增加读取函数
//u8* get_unread_data(u32 *len);
//用于一口气读出所有的未读数据
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
void write_buffer_data(u8* data, u32 datalen);


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


/*
外部写入数据后使用此函数更新内部参数
入口参数：
datalen:外部写入的数据长度
*/
void write_buffer_len(u32 datalen);


/*
获取全部未读数据
入口参数：
len: 读出数据的长度（字节）
*/
u8* get_unread_data(u32 *len);
#endif //  __RINGBUFFER_H_

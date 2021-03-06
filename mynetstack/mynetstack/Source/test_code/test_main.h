///////////////////////////////////////////////////////////////////
//创建时间：2018-11-23
//修改时间：2019-1-18
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：测试所有代码
//			
//		
//日志：
//
//2018-11-23:
//创建此文件，编写ringbuffer的测试代码ringbuffer_test.c
//______write_buffer_data____get_unread_ptr_____
//增加____SHOW__DEBUG____宏定义
//
//2018-11-27
//对______write_buffer_data____get_unread_ptr_____增加打印原始缓存
//数据功能，并
//增加测试函数
//______write_buffer_len____get_unread_ptr_____
//增加测试函数
//______write_buffer_len____get_unread_data_____
//修改来自stbrumme的crc32功能及测试代码
//并更名为______crc32_16bytes______
//
//2018-12-4
//增加测试函数______search_packeg______
//
//2018-12-8
//增加测试函数____trans_7to8b____
//
//208-12-22
//增加测试函数____packing_unpackeg___
//
//2018-12-23
//增加测试函数____update_readlocation_len____
//
//2019-1-18
//增加单元测试文件uint_test，用于各种单元结构测试
//
//2019-7-25
//增加数据包分类器测试文件classifier_test，测试原始数据分类
//////////////////////////////////////////////////////////////////


#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

//#define ____SHOW__DEBUG____

#include "../Factory/basic_header.h"
#include "../BasicDataStream/inc/ringbuffer.h"
#include "../Factory/inc/basic_crc32.h"
#include "../Factory/inc/basic_function.h"
#include "../BasicDataStream/inc/packeg_taken.h"
#include "../BasicDataStream/inc/sdata_trans.h"
#include "../Transport/inc/classifier.h"
/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ______write_buffer_data____get_unread_ptr_____(u32 loop);



/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ______write_buffer_len____get_unread_ptr_____(u32 loop);






/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ______write_buffer_len____get_unread_data_____(u32 loop);




/*
入口参数:
NumBytes: 生成测试数据的大小
返回值：CRC校验结果
*/
u32 ______crc32_16bytes______(u32 NumBytes);


/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u32 ______search_packeg______(u32 loop);


/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ____trans_8to7b_7to8b____(u32 loop);


/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ____packing_unpackeg___(u32 loop);





/*
入口参数:
loop: 测试次数
返回值：成功/失败
*/
u8 ____update_readlocation_len____(u32 loop);




u8 ______classifier____separa__mix_____(void);
#endif
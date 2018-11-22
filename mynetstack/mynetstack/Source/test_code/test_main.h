///////////////////////////////////////////////////////////////////
//创建时间：2018-11-23
//修改时间：2018-11-23
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
//////////////////////////////////////////////////////////////////


#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

//#define ____SHOW__DEBUG____

#include "../Factory/basic_header.h"
#include "../BasicDataStream/inc/ringbuffer.h"

/*
入口参数:
i: 测试次数
返回值：成功/失败
*/
u8 ______write_buffer_data____get_unread_ptr_____(u32 loop);

#endif
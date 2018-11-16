///////////////////////////////////////////////////////////////////
//创建时间：2018-11-16
//修改时间：2018-11-16
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：basic_function中定义了与本协议栈无关的工具类函数
//			如，内存的管理等
//		
//日志：
//
//2018-11-16:
//创建此文件，增加
//void* basic_malloc(u32 size)
//void basic_free(void* block)
//函数，用于内存的分配与释放
//////////////////////////////////////////////////////////////////
#ifndef __BASIC_FUNCTION_H__
#define __BASIC_FUNCTION_H__
#include <malloc.h>
#include "basic_type.h"

/*
分配内存
入口参数:
size:需要申请的空间大小，单位字节
*/
void* basic_malloc(u32 size);


/*
释放内存
入口参数:
block:释放空间的指针
*/
void basic_free(void* block);

#endif // !__BASIC_FUNCTION_H__

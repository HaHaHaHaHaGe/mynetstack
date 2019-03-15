///////////////////////////////////////////////////////////////////
//创建时间：2019-1-19
//修改时间：2018-3-16
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：对数据包进行包分类
//
//日志：
//
//2019-1-19:
//创建此文件
//
//2019-3-16:
//增加枚举PACKEG_TYPE、DATA_TYPE
//增加结构体packeg_base、packeg_data、packeg_command
///////////////////////////////////////////////////////////////////
#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"
#include "../../BasicDataStream/inc/ringbuffer.h"
#include "../../BasicDataStream/inc/packeg_taken.h"

/*
从unpacking中获取的源数据指定数据包类型
*/
typedef enum PACKEG_TYPE
{
	DATA_PACKEG,			//数据包
	COMMAND_PACKEG			//命令包
}PACKEG_TYPE;

/*
从unpacking中获取的源数据指定数据类型
*/
typedef enum DATA_TYPE
{
	NORMAL_DATA,			//正常数据
	REPAIR_DATA,			//修复数据
	REQUEST_DATA,			//请求数据
	RESPONSE_DATA			//应答数据
}DATA_TYPE;


/*
底层包：
包类型
数据类型
时间戳
数据长度
数据指针
*/
typedef struct packeg_base
{
	PACKEG_TYPE ptype;
	DATA_TYPE dtype;
	u32 timestamp;
	u32 datalen;
	u8* data;
}packeg_base;



/*
数据包：
累加编号
数据长度
数据指针
*/
typedef struct packeg_data
{
	u32 Cumulative;
	u32 datalen;
	u8* data;
};


/*
命令包：
包类型
请求包编号
*/
typedef struct packeg_command
{
	PACKEG_TYPE ptype;
	u32 requestpackeg;
};

#endif // !__CLASSIFIER_H__

///////////////////////////////////////////////////////////////////
//创建时间：2019-1-19
//修改时间：2019-7-14
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
//
//2019-7-14:
//增加枚举COMMAND_TYPE
//修改结构体packeg_base、packeg_data、packeg_command关于定义包类型部分
///////////////////////////////////////////////////////////////////
#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"
#include "../../BasicDataStream/inc/ringbuffer.h"
#include "../../BasicDataStream/inc/packeg_taken.h"

/*
从unpacking中获取的源数据指定数据包类型
原始数据首先要转化为packeg_base
*/
typedef enum PACKEG_TYPE
{
	DATA_PACKEG,			//数据包
	COMMAND_PACKEG			//命令包
}PACKEG_TYPE;

/*
从PACKEG_TYPE中获取的源数据指定数据类型
根据packeg_base中的PACKEG_TYPE决定其data的数据类型
（这是数据类型）
*/
typedef enum DATA_TYPE
{
	NORMAL_DATA,			//正常数据
	REPAIR_DATA,			//修复数据

}DATA_TYPE;

/*
从PACKEG_TYPE中获取的源数据指定数据类型
根据packeg_base中的PACKEG_TYPE决定其data的数据类型
（这是命令类型）
*/
typedef enum COMMAND_TYPE
{
	REQUEST_COMMAND,        //请求数据
	RESPONSE_COMMAND			//应答数据
}COMMAND_TYPE;



/*
无论是COMMAND_TYPE还是DATA_TYPE
可能都会需要定义一些消息类型（尤其是命令类型）
*/
typedef enum MESSAGE_TYPE
{
	SUCCESS_MESSAGE,		//成功的
	TIMEOUT_MESSAGE,		//超时的
	CLEAR_MESSAGE 			//由于超时或其他原因被清理的
}MESSAGE_TYPE;





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
	DATA_TYPE dtype;
	u32 Cumulative;
	u32 datalen;
	u8* data;
}packeg_data;


/*
命令包：
包类型
请求包编号
*/
typedef struct packeg_command
{
	COMMAND_TYPE ctype;
	u32 requestpackeg;
}packeg_command;




/*
检测packeg_base大小，方便为序列化分配内存
参数：
packeg_base:目标
返回值：字节
*/
int get_basepackeg_len(packeg_base* pb);




/*
将packeg_base序列化成二进制数据，方便传输
参数：
packeg_base:准备序列化的数据
data:保存位置
*/
void copy_basepackeg_to_memory(packeg_base* pb, u8 *data);





/*
从unpacking中的返回数据中分离出底层数据包
参数：
pb:要保存的空间地址
data:unpacking解析出来的原始数据
*/
void separa_packeg_base(packeg_base* pb,u8 *data);


/*
从separa_packeg_base中分离出数据包
参数：
pd:要保存的空间地址
data:packeg_base结构体指针
*/
void separa_packeg_data(packeg_data* pd,packeg_base *data);

/*
从separa_packeg_base中分离出命令包
参数：
pc:要保存的空间地址
data:packeg_base结构体指针
*/
void separa_packeg_command(packeg_command* pc,packeg_base *data);



/*
根据输入的参数生成数据包packeg_base
参数：
pdyte:生成的包类型（哪一种数据包）
datalen:数据长度
data:数据指针
*/
packeg_base mix_packeg_base(PACKEG_TYPE pdyte, u32 datalen, u8 *data);

/*
根据输入的参数生成数据包packeg_data
参数：
dtype:生成的数据包类型
datalen:数据长度
data:数据指针
*/
packeg_data mix_packeg_data(DATA_TYPE dtype,u32 datalen ,u8 *data);

/*
根据输入的参数生成数据包packeg_command
参数：
type:生成的数据包类型
count:一个编号（目前仅代表包编号）
*/
packeg_command mix_packeg_command(COMMAND_TYPE type,u32 count);
#endif // !__CLASSIFIER_H__

///////////////////////////////////////////////////////////////////
//创建时间：2018-12-15
//修改时间：2018-12-23
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：数据结构链表，用于存储数据
//			
//		
//日志：
//
//2018-12-15:
//创建文件，增加结构体 LIST
//
//2018-12-23
//修复Add_List缺少一个参数的问题
//增加函数与结构的注释说明
//////////////////////////////////////////////////////////////////
#ifndef __BASIC_LIST_H__
#define __BASIC_LIST_H__
#include "../basic_header.h"
#include "../inc/basic_function.h"

typedef struct LIST LIST;
typedef struct LIST_DATA LIST_DATA;

/*
链表的单位数据
存放着只想下一个结构的指针
存放的数据指针
存放的数据大小
*/
typedef struct LIST_DATA
{
	u8 *data;
	u32 len;
	LIST_DATA *next;
}LIST_DATA;

/*
链表的管理实体
存放着链表的头尾
链表的长度
*/
typedef struct LIST
{
	LIST_DATA *start;
	LIST_DATA *end;
	u32 Number;
}LIST;


/*
初始化链表
入口参数
list：被初始化的结构体
*/
void Init_List(LIST *list);



/*
对链表增加一个数据
入口参数
list：被添加的链表
data：数据
len：长度
*/
void Add_List(LIST *list, u8 *data, u32 len);



/*
对链表删除一个数据
入口参数
list：被删除的链表
data：删除的对象
*/
void Delete_List(LIST *list, LIST_DATA *data);

#endif // !__BASIC_LIST_H__

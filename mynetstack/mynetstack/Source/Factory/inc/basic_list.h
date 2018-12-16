///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-12-15
//�޸�ʱ�䣺2018-12-15
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ����ݽṹ���������ڴ洢����
//			
//		
//��־��
//
//2018-12-15:
//�����ļ������ӽṹ�� LIST
//
//////////////////////////////////////////////////////////////////
#ifndef __BASIC_LIST_H__
#define __BASIC_LIST_H__
#include "../basic_header.h"
#include "../inc/basic_function.h"

typedef struct LIST LIST;
typedef struct LIST_DATA LIST_DATA;


typedef struct LIST_DATA
{
	u8 *data;
	u32 len;
	LIST_DATA *next;
}LIST_DATA;


typedef struct LIST
{
	LIST_DATA *start;
	LIST_DATA *end;
	u32 Number;
}LIST;

void Init_List(LIST *list);
void Add_List(LIST *list, u8 *data);
void Delete_List(LIST *list, LIST_DATA *data);

#endif // !__BASIC_LIST_H__
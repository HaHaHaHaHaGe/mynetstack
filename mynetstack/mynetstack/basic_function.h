///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-16
//�޸�ʱ�䣺2018-11-16
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ�basic_function�ж������뱾Э��ջ�޹صĹ����ຯ��
//			�磬�ڴ�Ĺ����
//		
//��־��
//
//2018-11-16:
//�������ļ�������
//void* basic_malloc(u32 size)
//void basic_free(void* block)
//�����������ڴ�ķ������ͷ�
//////////////////////////////////////////////////////////////////
#ifndef __BASIC_FUNCTION_H__
#define __BASIC_FUNCTION_H__
#include <malloc.h>
#include "basic_type.h"

/*
�����ڴ�
��ڲ���:
size:��Ҫ����Ŀռ��С����λ�ֽ�
*/
void* basic_malloc(u32 size);


/*
�ͷ��ڴ�
��ڲ���:
block:�ͷſռ��ָ��
*/
void basic_free(void* block);

#endif // !__BASIC_FUNCTION_H__

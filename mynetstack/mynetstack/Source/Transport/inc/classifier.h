///////////////////////////////////////////////////////////////////
//����ʱ�䣺2019-1-19
//�޸�ʱ�䣺2018-3-16
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ������ݰ����а�����
//
//��־��
//
//2019-1-19:
//�������ļ�
//
//2019-3-16:
//����ö��PACKEG_TYPE��DATA_TYPE
//���ӽṹ��packeg_base��packeg_data��packeg_command
///////////////////////////////////////////////////////////////////
#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"
#include "../../BasicDataStream/inc/ringbuffer.h"
#include "../../BasicDataStream/inc/packeg_taken.h"

/*
��unpacking�л�ȡ��Դ����ָ�����ݰ�����
*/
typedef enum PACKEG_TYPE
{
	DATA_PACKEG,			//���ݰ�
	COMMAND_PACKEG			//�����
}PACKEG_TYPE;

/*
��unpacking�л�ȡ��Դ����ָ����������
*/
typedef enum DATA_TYPE
{
	NORMAL_DATA,			//��������
	REPAIR_DATA,			//�޸�����
	REQUEST_DATA,			//��������
	RESPONSE_DATA			//Ӧ������
}DATA_TYPE;


/*
�ײ����
������
��������
ʱ���
���ݳ���
����ָ��
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
���ݰ���
�ۼӱ��
���ݳ���
����ָ��
*/
typedef struct packeg_data
{
	u32 Cumulative;
	u32 datalen;
	u8* data;
};


/*
�������
������
��������
*/
typedef struct packeg_command
{
	PACKEG_TYPE ptype;
	u32 requestpackeg;
};

#endif // !__CLASSIFIER_H__

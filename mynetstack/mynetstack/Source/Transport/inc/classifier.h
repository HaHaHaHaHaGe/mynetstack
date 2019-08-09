///////////////////////////////////////////////////////////////////
//����ʱ�䣺2019-1-19
//�޸�ʱ�䣺2019-7-14
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
//
//2019-7-14:
//����ö��COMMAND_TYPE
//�޸Ľṹ��packeg_base��packeg_data��packeg_command���ڶ�������Ͳ���
///////////////////////////////////////////////////////////////////
#ifndef __CLASSIFIER_H__
#define __CLASSIFIER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"
#include "../../BasicDataStream/inc/ringbuffer.h"
#include "../../BasicDataStream/inc/packeg_taken.h"

/*
��unpacking�л�ȡ��Դ����ָ�����ݰ�����
ԭʼ��������Ҫת��Ϊpackeg_base
*/
typedef enum PACKEG_TYPE
{
	DATA_PACKEG,			//���ݰ�
	COMMAND_PACKEG			//�����
}PACKEG_TYPE;

/*
��PACKEG_TYPE�л�ȡ��Դ����ָ����������
����packeg_base�е�PACKEG_TYPE������data����������
�������������ͣ�
*/
typedef enum DATA_TYPE
{
	NORMAL_DATA,			//��������
	REPAIR_DATA,			//�޸�����

}DATA_TYPE;

/*
��PACKEG_TYPE�л�ȡ��Դ����ָ����������
����packeg_base�е�PACKEG_TYPE������data����������
�������������ͣ�
*/
typedef enum COMMAND_TYPE
{
	REQUEST_COMMAND,        //��������
	RESPONSE_COMMAND			//Ӧ������
}COMMAND_TYPE;



/*
������COMMAND_TYPE����DATA_TYPE
���ܶ�����Ҫ����һЩ��Ϣ���ͣ��������������ͣ�
*/
typedef enum MESSAGE_TYPE
{
	SUCCESS_MESSAGE,		//�ɹ���
	TIMEOUT_MESSAGE,		//��ʱ��
	CLEAR_MESSAGE 			//���ڳ�ʱ������ԭ�������
}MESSAGE_TYPE;





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
	DATA_TYPE dtype;
	u32 Cumulative;
	u32 datalen;
	u8* data;
}packeg_data;


/*
�������
������
��������
*/
typedef struct packeg_command
{
	COMMAND_TYPE ctype;
	u32 requestpackeg;
}packeg_command;




/*
���packeg_base��С������Ϊ���л������ڴ�
������
packeg_base:Ŀ��
����ֵ���ֽ�
*/
int get_basepackeg_len(packeg_base* pb);




/*
��packeg_base���л��ɶ��������ݣ����㴫��
������
packeg_base:׼�����л�������
data:����λ��
*/
void copy_basepackeg_to_memory(packeg_base* pb, u8 *data);





/*
��unpacking�еķ��������з�����ײ����ݰ�
������
pb:Ҫ����Ŀռ��ַ
data:unpacking����������ԭʼ����
*/
void separa_packeg_base(packeg_base* pb,u8 *data);


/*
��separa_packeg_base�з�������ݰ�
������
pd:Ҫ����Ŀռ��ַ
data:packeg_base�ṹ��ָ��
*/
void separa_packeg_data(packeg_data* pd,packeg_base *data);

/*
��separa_packeg_base�з���������
������
pc:Ҫ����Ŀռ��ַ
data:packeg_base�ṹ��ָ��
*/
void separa_packeg_command(packeg_command* pc,packeg_base *data);



/*
��������Ĳ����������ݰ�packeg_base
������
pdyte:���ɵİ����ͣ���һ�����ݰ���
datalen:���ݳ���
data:����ָ��
*/
packeg_base mix_packeg_base(PACKEG_TYPE pdyte, u32 datalen, u8 *data);

/*
��������Ĳ����������ݰ�packeg_data
������
dtype:���ɵ����ݰ�����
datalen:���ݳ���
data:����ָ��
*/
packeg_data mix_packeg_data(DATA_TYPE dtype,u32 datalen ,u8 *data);

/*
��������Ĳ����������ݰ�packeg_command
������
type:���ɵ����ݰ�����
count:һ����ţ�Ŀǰ���������ţ�
*/
packeg_command mix_packeg_command(COMMAND_TYPE type,u32 count);
#endif // !__CLASSIFIER_H__

///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-16
//�޸�ʱ�䣺2018-11-22
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ�ringbuffer����Ҫʵ�����ݻ��幦�ܡ����εĶ�ȡ������Ч
//�������ݱ����ǵĿ�����
//		
//��־��
//
//2018-11-16:
//�������ļ�������
//void write_buffer(u8* data, u32 datalen);
//u8 deinitial_buffer(void);
//u8 initial_buffer(u8* ptr, u32 size);
//����д���������ͷŻ���������ʼ��������
//
//2018-11-20
//��void write_buffer(u8* data, u32 datalen);
//����Ϊvoid write_buffer_data(u8* data, u32 datalen)
//���޸���д������ݸպõ������������С�����Ҷ�ָ��Ϊ��ʼֵʱ
//�޷���ȷ�жϲ����õ�ǰ״̬Ϊ����ǰ̬��
//���Ӷ�ȡ����
//u8* get_unread_data(u32 *len);
//����һ�����������е�δ������
//
//2018-11-22
//��u8* get_unread_data(u32 *len,u8 preview);
//������ڲ���preview
//���Ӻ���
//void get_unread_ptr(u8** ptr_1, u8** ptr_2, u32* len_1, u32* len_2, u8 preview);
//����ֱ�ӷ���δ�����ݵ�ָ�루Ч����ߣ����ǻ�Ϊ�����֣�
//�޸�get_unread_data�������ڵ�bug��δ���ǳ�ǰ̬��
//////////////////////////////////////////////////////////////////
#ifndef  __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"
/*
д���ݵ�����������
��ڲ�����
data:д�������ָ��
datalen:д������ݳ���
*/
void write_buffer_data(u8* data, u32 datalen);


/*
�ͷŻ���������
ע������ڴ���ʱָ�����Ѿ����ٺõ��ڴ棬
��ô�ú���ֻ�������ģ���ڲ��ı�����
��������ⲿ������
*/
u8 deinitial_buffer(void);




/*
��������������
ע�����ڴ���ʱָ���Ѿ����ٺõ��ڴ棬
��ڲ�����
ptr: ָ���ⲿ�ڴ�ռ䣬��ʱ��Ҫ��дNULL_PTR
size: ��Ҫ���ٿռ�Ĵ�С
*/
u8 initial_buffer(u8* ptr, u32 size);


/*
�ⲿд�����ݺ�ʹ�ô˺��������ڲ�����
��ڲ�����
datalen:�ⲿд������ݳ���
*/
void write_buffer_len(u32 datalen);


/*
��ȡȫ��δ������
��ڲ�����
len: �������ݵĳ��ȣ��ֽڣ�
preview����ΪYES��˴ζ�ȡ�����޸�ringbuff��ָ��״̬
*/
u8* get_unread_data(u32 *len,u8 preview);





/*
��ȡȫ��δ�����ݵ�ָ�루�������֣�
��ڲ�����
ptr_1: �����һ��ָ��
ptr_2: ����ڶ���ָ��
len_1: ��һ��ָ�����ݵĴ�С���ֽڣ�
len_2: �ڶ���ָ�����ݵĴ�С���ֽڣ�
preview����ΪYES��˴ζ�ȡ�����޸�ringbuff��ָ��״̬
*/
void get_unread_ptr(u8** ptr_1, u8** ptr_2, u32* len_1, u32* len_2, u8 preview);
#endif //  __RINGBUFFER_H_

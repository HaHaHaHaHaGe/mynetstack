///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-16
//�޸�ʱ�䣺2018-11-16
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
//////////////////////////////////////////////////////////////////
#ifndef  __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include "basic_header.h"

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
*/
u8* get_unread_data(u32 *len);
#endif //  __RINGBUFFER_H_

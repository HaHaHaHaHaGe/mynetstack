///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-16
//�޸�ʱ�䣺2018-12-1
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
//
//2018-11-27
//�޸�get_unread_data����û�ж������*len���и�ֵ���Ұָ���bug
//�޸�ȫ�������������ӽṹ��ringbuffer��ʹ�ô˽ṹ�ɳ�ʼ����ͬ��ʵ��
//�޸�initial_buffer���Ӳ���u8 self_mem�����ڱ�־�Ƿ����з����ڴ�
//����void update_readlocation(ringbuffer *ptr)����
//�����ֶ�����readָ��
//
//2018-12-1
//ɾ������Ӱ��Ч�ʵ��жϿ�ָ����루�������ܷɷ��գ�
//////////////////////////////////////////////////////////////////
#ifndef  __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"




/*
���ڴ洢ringbuffer�еĹؼ�ȫ�ֱ���
ʹ�ô˽ṹ�ɹ�����ͬ��ringbuffer
*/
typedef struct ringbuffer
{
	u8* start_ringbuffer_ptr;															//��������ʼλ��
	u8* end_ringbuffer_ptr;																//��������ֹλ��
	u8* write_location_ptr;																//д����λ��
	u8* read_location_ptr;																//������λ��

	u8* return_data_buffer;																//���ڷ��ص�������

	u32 ringbuffer_size;																//��������С
	u8 malloc_flag;																		//�Ļ������Ƿ������д�����

	u8 leading_flag;																	//��ǰд�����Ƿ����ȶ�����һ������

}ringbuffer;








/*
д���ݵ�����������
��ڲ�����
ptr:��������
data:д�������ָ��
datalen:д������ݳ���
*/
void write_buffer_data(ringbuffer *ptr, u8* data, u32 datalen);


/*
�ͷŻ���������
ע������ڴ���ʱָ�����Ѿ����ٺõ��ڴ棬
��ô�ú���ֻ�������ģ���ڲ��ı�����
��������ⲿ������
��ڲ�����
ptr:��������
*/
u8 deinitial_buffer(ringbuffer *ptr);




/*
��������������
ע�����ڴ���ʱָ���Ѿ����ٺõ��ڴ棬
��ڲ�����
ptr:��������
self_mem: �Ƿ��ɱ��������з���ռ䣬�������Ҫ��
Ӧ����NO���ڲ��������start ptr�з������Ӧ�Ŀռ�
size: ��Ҫ���ٿռ�Ĵ�С
*/
u8 initial_buffer(ringbuffer *ptr, u8 self_mem, u32 size);


/*
�ⲿд�����ݺ�ʹ�ô˺��������ڲ�����
��ڲ�����
ptr:��������
datalen:�ⲿд������ݳ���
*/
void write_buffer_len(ringbuffer *ptr, u32 datalen);


/*
��ȡȫ��δ������
��ڲ�����
ptr:��������
len: �������ݵĳ��ȣ��ֽڣ�
preview����ΪYES��˴ζ�ȡ�����޸�ringbuff��ָ��״̬
*/
u8* get_unread_data(ringbuffer *ptr, u32 *len,u8 preview);





/*
��ȡȫ��δ�����ݵ�ָ�루�������֣�
��ڲ�����
ptr:��������
ptr_1: �����һ��ָ��
ptr_2: ����ڶ���ָ��
len_1: ��һ��ָ�����ݵĴ�С���ֽڣ�
len_2: �ڶ���ָ�����ݵĴ�С���ֽڣ�
preview����ΪYES��˴ζ�ȡ�����޸�ringbuff��ָ��״̬
*/
void get_unread_ptr(ringbuffer *ptr, u8** ptr_1, u8** ptr_2, u32* len_1, u32* len_2, u8 preview);








/*
�ֶ�����readָ��
ע:һ����get_unread_ptr������������ʹ��
��ڲ�����
ptr:��������
*/
void update_readlocation(ringbuffer *ptr);
#endif //  __RINGBUFFER_H_

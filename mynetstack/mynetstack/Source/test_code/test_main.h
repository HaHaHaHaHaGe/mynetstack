///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-23
//�޸�ʱ�䣺2018-11-27
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ��������д���
//			
//		
//��־��
//
//2018-11-23:
//�������ļ�����дringbuffer�Ĳ��Դ���ringbuffer_test.c
//______write_buffer_data____get_unread_ptr_____
//����____SHOW__DEBUG____�궨��
//
//2018-11-27
//��______write_buffer_data____get_unread_ptr_____���Ӵ�ӡԭʼ����
//���ݹ��ܣ���
//���Ӳ��Ժ���
//______write_buffer_len____get_unread_ptr_____
//���Ӳ��Ժ���
//______write_buffer_len____get_unread_data_____
//�޸�����stbrumme��crc32���ܼ����Դ���
//������Ϊ______crc32_16bytes______
//////////////////////////////////////////////////////////////////


#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

//#define ____SHOW__DEBUG____

#include "../Factory/basic_header.h"
#include "../BasicDataStream/inc/ringbuffer.h"
#include "../Factory/inc/basic_crc32.h"
#include "../Factory/inc/basic_function.h"
/*
��ڲ���:
i: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_data____get_unread_ptr_____(u32 loop);



/*
��ڲ���:
i: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_len____get_unread_ptr_____(u32 loop);






/*
��ڲ���:
i: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_len____get_unread_data_____(u32 loop);




/*
��ڲ���:
NumBytes: ���ɲ������ݵĴ�С
����ֵ��CRCУ����
*/
u32 ______crc32_16bytes______(u32 NumBytes);
#endif
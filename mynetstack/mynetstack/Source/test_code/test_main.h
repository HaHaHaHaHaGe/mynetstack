///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-23
//�޸�ʱ�䣺2018-12-8
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
//
//2018-12-4
//���Ӳ��Ժ���______search_packeg______
//
//2018-12-8
//���Ӳ��Ժ���____trans_7to8b____
//////////////////////////////////////////////////////////////////


#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

//#define ____SHOW__DEBUG____

#include "../Factory/basic_header.h"
#include "../BasicDataStream/inc/ringbuffer.h"
#include "../Factory/inc/basic_crc32.h"
#include "../Factory/inc/basic_function.h"
#include "../BasicDataStream/inc/packeg_taken.h"
#include "../BasicDataStream/inc/sdata_trans.h"
/*
��ڲ���:
loop: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_data____get_unread_ptr_____(u32 loop);



/*
��ڲ���:
loop: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_len____get_unread_ptr_____(u32 loop);






/*
��ڲ���:
loop: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ______write_buffer_len____get_unread_data_____(u32 loop);




/*
��ڲ���:
NumBytes: ���ɲ������ݵĴ�С
����ֵ��CRCУ����
*/
u32 ______crc32_16bytes______(u32 NumBytes);


/*
��ڲ���:
loop: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u32 ______search_packeg______(u32 loop);


/*
��ڲ���:
loop: ���Դ���
����ֵ���ɹ�/ʧ��
*/
u8 ____trans_8to7b_7to8b____(u32 loop);
#endif
///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-11-27
//�޸�ʱ�䣺2018-11-27
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ��Ӹ���������(ringbufffer)��ȡ��Ч���ݰ�
//
//		
//��־��
//
//2018-11-27:�������ļ�
//�趨��ͷpacket_header��
//ȷ��ԭʼ���ݽṹsource_data
//
///////////////////////////////////////////////////////////////////
#ifndef  __PACKEG_TAKEN_H__
#define __RINGBUFFER_H__
#include "../../Factory/basic_header.h"

#define __REDUCTION_DATA_LENGTH__ 1024


//ԭʼ���ݰ���ͷ
const u8 packet_header[4] = {0xFF,0xFF,0xFF,0xFF};


//ԭʼ���ݰ��ṹ
typedef struct source_data
{
	u8* packet_header;
	u32 packet_len;
	u32 packet_crc32;
	u8* packet_data;
}source_data;

#endif
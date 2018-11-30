///////////////////////////////////////////////////////////////////
//����ʱ�䣺2011-11-13
//�޸�ʱ�䣺2018-11-30
//������Ա��stbrumme
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ�fork������޸ģ���Ҫ�������ݰ���crcУ��
//		
//��־��
//
//2018-11-27:
//��stbrumme��git��fork�Ĵ������ɾ���޸ĺ�Ĵ���
//Դgithub��https://github.com/stbrumme/crc32
//��ʼ��web��https://create.stephan-brumme.com/crc32/
//����crc32_16bytes����������ɾ��
//����Little_Endian�궨�壬�����л���С��
//
//2018-11-30
//�Ƴ�swap������basic_function�У�������Ϊbasic_swap
//�Ƴ�Little_Endian�궨�嵽basic_function��
//////////////////////////////////////////////////////////////////
#ifndef __BASIC_CRC32_H__
#define __BASIC_CRC32_H__

#include "../basic_header.h"
#include "../inc/basic_function.h"





/*
crcУ��
��ڲ�����
data:����ָ��
length:���ݳ���
previousCrc32:֮ǰ��crc32У���������ڷֲ�ʽУ�飩
����ֵ��
crcУ����
*/
u32 crc32_16bytes(u32* data, u32 length, u32 previousCrc32);

#endif // !__BASIC_CRC32_H__
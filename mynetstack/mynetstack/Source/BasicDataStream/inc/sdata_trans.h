///////////////////////////////////////////////////////////////////
//����ʱ�䣺2018-12-9
//�޸�ʱ�䣺2018-12-23
//������Ա��HaHaHaHaHaGe
//�޸���Ա��HaHaHaHaHaGe
//��Ҫ���ܣ���ԭʼ���ݽ���ת����7bit->8bit��
//������ת��Ϊ�ɹ�Ӳ���ײ㷢�͵�����(8bit->7bit)
//
//��־��
//
//2018-12-9
//����packeg_taken���й�������ʵ�޸����ڣ�2018-12-8��
//���Ӻ���trans_8to7b��trans_7to8b
//���ڽ�ԭʼ���ݽ���ת����Ϊ�˽��з��/�������
//δ�����Ż���100MB�����ݽ���һ�β�\װ ����Ҫ5�루4GHZ��CPU 2700X��
//�����㷨trans_8to7b_64bytes��trans_7to8b_64bytes
//�Ż���ĺ�����100MB�����ݽ���һ�β�\װ ����Ҫ0.28�루4GHZ��CPU 2700X��
//
//�Ż���ĺ���trans_8to7b_64bytes_fast��trans_7to8b_64bytes_fast
//100MB�����ݽ���һ�β�\װ ����Ҫ0.167�루4GHZ��CPU 2700X��
//
//2018-12-23
//�޸�trans_8to7b_64bytes_fast��trans_7to8b_64bytes_fast��Ҫ����1byte�ռ������
///////////////////////////////////////////////////////////////////


#ifndef __SDATA_TRANS_H__
#define __SDATA_TRANS_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"

/*
��8bit����ת����7bit����
src�������8bit����
dst������7bit���ݵ�λ��
dst_len������������С
*/
void trans_8to7b(u8 *src, u8 *dst, u32 dst_len);

/*
��7bit����ת����8bit����
src�������7bit����
dst������8bit���ݵ�λ��
src_len�������7bit���ݴ�С
*/
void trans_7to8b(u8 *src, u8 *dst, u32 src_len);


/*
��8bit����ת����7bit���ݣ������㷨��
src�������8bit����
dst������7bit���ݵ�λ��
dst_len�������7bit���ݴ�С
*/
void trans_8to7b_64bytes(u8 *src, u8 *dst, u32 dst_len);


/*
��7bit����ת����8bit���ݣ������㷨��
src�������7bit����
dst������8bit���ݵ�λ��
src_len�������7bit���ݴ�С
*/
void trans_7to8b_64bytes(u8 *src, u8 *dst, u32 src_len);


/*
��8bit����ת����7bit���ݣ��������㷨��
dst��Ҫ����1bit�ռ�
src�ռ���Ҫ����ʼ��Ϊ0

src�������7bit����
dst������8bit���ݵ�λ��
src_len�������7bit���ݴ�С
*/
void trans_8to7b_64bytes_fast(u8 *src, u8 *dst, u32 src_len);



/*
��7bit����ת����8bit���ݣ��������㷨��
dst��Ҫ����1bit�ռ�
src�ռ���Ҫ����ʼ��Ϊ0

src�������7bit����
dst������8bit���ݵ�λ��
src_len�������7bit���ݴ�С
*/
void trans_7to8b_64bytes_fast(u8 *src, u8 *dst, u32 src_len);
#endif // !__SDATA_TRANS_H__


///////////////////////////////////////////////////////////////////
//创建时间：2018-12-9
//修改时间：2018-12-23
//创建人员：HaHaHaHaHaGe
//修改人员：HaHaHaHaHaGe
//主要功能：将原始数据进行转化（7bit->8bit）
//或将数据转化为可供硬件底层发送的数据(8bit->7bit)
//
//日志：
//
//2018-12-9
//（从packeg_taken剪切过来，真实修改日期：2018-12-8）
//增加函数trans_8to7b与trans_7to8b
//用于将原始数据进行转化，为了进行封包/拆包操作
//未进行优化，100MB的数据进行一次拆\装 共需要5秒（4GHZ的CPU 2700X）
//更新算法trans_8to7b_64bytes、trans_7to8b_64bytes
//优化后的函数，100MB的数据进行一次拆\装 共需要0.28秒（4GHZ的CPU 2700X）
//
//优化后的函数trans_8to7b_64bytes_fast、trans_7to8b_64bytes_fast
//100MB的数据进行一次拆\装 共需要0.167秒（4GHZ的CPU 2700X）
//
//2018-12-23
//修复trans_8to7b_64bytes_fast、trans_7to8b_64bytes_fast需要额外1byte空间的问题
///////////////////////////////////////////////////////////////////


#ifndef __SDATA_TRANS_H__
#define __SDATA_TRANS_H__
#include "../../Factory/basic_header.h"
#include "../../Factory/inc/basic_function.h"

/*
将8bit数据转化成7bit数据
src：输入的8bit数据
dst：保存7bit数据的位置
dst_len：保存的数组大小
*/
void trans_8to7b(u8 *src, u8 *dst, u32 dst_len);

/*
将7bit数据转化成8bit数据
src：输入的7bit数据
dst：保存8bit数据的位置
src_len：输入的7bit数据大小
*/
void trans_7to8b(u8 *src, u8 *dst, u32 src_len);


/*
将8bit数据转化成7bit数据（快速算法）
src：输入的8bit数据
dst：保存7bit数据的位置
dst_len：输出的7bit数据大小
*/
void trans_8to7b_64bytes(u8 *src, u8 *dst, u32 dst_len);


/*
将7bit数据转化成8bit数据（快速算法）
src：输入的7bit数据
dst：保存8bit数据的位置
src_len：输入的7bit数据大小
*/
void trans_7to8b_64bytes(u8 *src, u8 *dst, u32 src_len);


/*
将8bit数据转化成7bit数据（超快速算法）
dst需要额外1bit空间
src空间需要被初始化为0

src：输入的7bit数据
dst：保存8bit数据的位置
src_len：输入的7bit数据大小
*/
void trans_8to7b_64bytes_fast(u8 *src, u8 *dst, u32 src_len);



/*
将7bit数据转化成8bit数据（超快速算法）
dst需要额外1bit空间
src空间需要被初始化为0

src：输入的7bit数据
dst：保存8bit数据的位置
src_len：输入的7bit数据大小
*/
void trans_7to8b_64bytes_fast(u8 *src, u8 *dst, u32 src_len);
#endif // !__SDATA_TRANS_H__


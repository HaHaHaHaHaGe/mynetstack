#include "../inc/basic_function.h"

void* basic_malloc(u32 size)
{
	return malloc(size);
}

void basic_free(void* block)
{
	free(block);
}

void basic_memcpy(u8* dst,u8* src,u32 size)
{
	memcpy(dst,src,size);
}
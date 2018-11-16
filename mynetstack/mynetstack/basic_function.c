#include "basic_function.h"

void* basic_malloc(u32 size)
{
	return malloc(size);
}

void basic_free(void* block)
{
	free(block);
}
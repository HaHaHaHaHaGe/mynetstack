#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"
extern u8* start_ringbuffer_ptr;
extern u8* read_location_ptr;
int main()
{
	unsigned long long i = 100000000;
	initial_buffer(NULL_PTR,15);

	
	write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", 6);
	printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", 12);
	printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	while (i--)
	{
		write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", rand()%36);
		//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	}
	printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	//printf("%c", read_location_ptr++);
	//printf("%c", read_location_ptr++);
	//printf("%c", read_location_ptr++);
	//while (i--)
	//	write_buffer((u8*)"1234567890", rand() % 10);
	write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", 8);
	printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);

	while (1)
	{

	}
}
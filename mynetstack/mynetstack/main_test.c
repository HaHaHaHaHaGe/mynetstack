#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"
extern u8* start_ringbuffer_ptr;
extern u8* read_location_ptr;
int main()
{
	u32 i;
	u8* s;
	initial_buffer(NULL_PTR,10);

	
	write_buffer_data((u8*)"12345678", 8);
	
	s = get_unread_data(&i);
	printf("%s      %d\r\n", s, i);

	write_buffer_data((u8*)"12345678", 4);
	write_buffer_data((u8*)"12345678", 1);
	s = get_unread_data(&i);
	printf("%s      %d\r\n", s, i);
	//write_buffer_data((u8*)"a2345678", 1);
	//write_buffer_len(1);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	//read_location_ptr += 5;

	//write_buffer_len(5);
	////write_buffer_data((u8*)"efgh", 4);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);

	//write_buffer_len(7);
	////write_buffer_data((u8*)"efgh", 4);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);


	//write_buffer_len(97524);
	////write_buffer_data((u8*)"1234567890", 9);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);

	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	//write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", 12);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	//while (i--)
	//{
	//	write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", rand()%36);
	//	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	//}
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);
	////printf("%c", read_location_ptr++);
	////printf("%c", read_location_ptr++);
	////printf("%c", read_location_ptr++);
	////while (i--)
	////	write_buffer((u8*)"1234567890", rand() % 10);
	//write_buffer((u8*)"1234567890abcdefghijklmnopqrstuvwxyz", 8);
	//printf("%s      %c\r\n", start_ringbuffer_ptr, *read_location_ptr);

	while (1)
	{
		write_buffer_data((u8*)"12345678", 3);
		s = get_unread_data(&i);
		while (i--)
			printf("%c",s[i]);
		printf("\r\n");
	}
}
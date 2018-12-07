#include "test_main.h"

int main(void)
{
	u8 s;
	u32 crc;



	s = ____trans_8to7b_7to8b____(1024*100);
	if (s == YES)
		printf("____trans_8to7b_7to8b____:					YES\r\n");
	else
		printf("____trans_8to7b_7to8b____:					NO\r\n");


	s = ______search_packeg______(1000000);
	if (s == YES)
		printf("______search_packeg______:					YES\r\n");
	else
		printf("______search_packeg______:					NO\r\n");




	s = ______write_buffer_len____get_unread_data_____(1000000);
	if (s == YES)
		printf("______write_buffer_data____get_unread_ptr_____:					YES\r\n");
	else
		printf("______write_buffer_data____get_unread_ptr_____:					NO\r\n");


	s = ______write_buffer_len____get_unread_ptr_____(1000000);
	if (s == YES)
		printf("______write_buffer_len____get_unread_ptr_____:					YES\r\n");
	else
		printf("______write_buffer_len____get_unread_ptr_____:					NO\r\n");


	s = ______write_buffer_data____get_unread_ptr_____(1000000);
	if (s == YES)
		printf("______write_buffer_data____get_unread_ptr_____:					YES\r\n");
	else
		printf("______write_buffer_data____get_unread_ptr_____:					NO\r\n");


	crc = ______crc32_16bytes______(1024*1024);
	printf("______crc32_16bytes______:							0x%X\r\n", crc);
	while (1);
}
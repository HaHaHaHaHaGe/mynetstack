#include "test_main.h"

int main(void)
{
	u8 s;
	u32 crc;

	______classifier____separa__mix_____();





	s = ______UNIT_read_write_data______("D:/2019.03.12-23.24.50/Left_00000.png");
	if (s == YES)
		printf("______UNIT_read_write_data______:					YES\r\n");
	else
		printf("______UNIT_read_write_data______:					NO\r\n");



	s = ____update_readlocation_len____(10000);
	if (s == YES)
		printf("____update_readlocation_len____:					YES\r\n");
	else
		printf("____update_readlocation_len____:					NO\r\n");



	s = ____packing_unpackeg___(128);
	if (s == YES)
		printf("____packing_unpackeg___:					YES\r\n");
	else
		printf("____packing_unpackeg___:					NO\r\n");



	s = ____trans_8to7b_7to8b____(1024*10);
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
		printf("______write_buffer_len____get_unread_data_____:					YES\r\n");
	else
		printf("______write_buffer_len____get_unread_data_____:					NO\r\n");


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
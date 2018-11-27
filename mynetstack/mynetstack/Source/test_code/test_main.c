#include "test_main.h"

int main(void)
{
	u8 s;
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
	while (1);
}